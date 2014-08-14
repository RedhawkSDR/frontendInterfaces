#!/usr/bin/env python
#
# This file is protected by Copyright. Please refer to the COPYRIGHT file
# distributed with this source distribution.
#
# This file is part of REDHAWK frontendInterfaces.
#
# REDHAWK frontendInterfaces is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# REDHAWK frontendInterfaces is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see http://www.gnu.org/licenses/.
#
#
from ossie.cf import CF, CF__POA
from ossie.utils import uuid
from omniORB import any, CORBA

from ossie.device import Device
from ossie.properties import simple_property
from ossie.properties import struct_property
from ossie.properties import structseq_property
from ossie.utils import model

import threading
from bulkio.bulkioInterfaces import BULKIO
from redhawk.frontendInterfaces import FRONTEND
from fe_types import *

class AllocationAlreadyExists(CF.Device.InvalidCapacity):
    def __init__(self, msg, props):
        CF.Device.InvalidCapacity(msg,props)

def zeroSRI(sri):
    if sri:
        sri.hversion = 1
        sri.xstart = 0.0
        sri.xdelta = 1.0
        sri.xunits = 1
        sri.subsize = 1
        sri.ystart = 0.0
        sri.ydelta = 1.0
        sri.yunits = 1
        sri.mode = 0
        sri.streamID = ""
        sri.blocking = False
        sri.keywords = []
    else:
        sri = BULKIO.StreamSRI(hversion=1, xstart=0.0, xdelta=1.0, 
                              xunits=1, subsize=1, ystart=0.0, ydelta=1.0, 
                              yunits=1, mode=0, streamID="", blocking=False, keywords=[])
        
# Time Type Definition
J1950 = 1
J1970 = 2
JCY = 3
#timeTypes = {'J1950':J1950,'J1970':J1970,'JCY':JCY}
    
# Tuner Allocation IDs struct. This structure contains allocation tracking data.
class tunerAllocationIdsStruct:
    def __init__(self):
        self.reset()

    def reset(self):
        self.control_allocation_id = None
        self.listener_allocation_ids = []

''' floatingPointCompare is a helper function to handle floating point comparison
      Return values:
        if lhs == rhs: 0.0
        if lhs >  rhs: 1.0 or greater
        if lhs <  rhs: -1.0 or less
      Recommended usage is to convert a comparison such as: (lhs OP rhs)
      to (floatingPointCompare(lhs,rhs) OP 0), where OP is a comparison operator
      (==, <, >, <=, >=, !=).
      "places" is used to specify precision. The default is 1, which
      uses a single decimal place of precision.
'''

def floatingPointCompare(lhs, rhs, places = 1):
    return round((lhs-rhs)*pow(10,places))

''' validateRequest is a helper function to verify a value is within a range, returning
     true if the value requested_val falls within the range [available_min:available_max]
     False is returned if min > max
'''
def validateRequest(available_min, available_max, requested_val):
    if floatingPointCompare(requested_val,available_min) < 0: return False
    if floatingPointCompare(requested_val,available_max) > 0: return False
    if floatingPointCompare(available_min,available_max) > 0: return False
    return True

''' validateRequest is a helper function to compare two ranges, returning true if the range
     [requested_min:requested_max] falls within the range [available_min:available_max]
     False is returned if min > max for either available for requested values
'''
def validateRequest(available_min, available_max, requested_min, requested_max):
    if floatingPointCompare(requested_min,available_min) < 0: return False
    if floatingPointCompare(requested_max,available_max) > 0: return False
    if floatingPointCompare(available_min,available_max) > 0: return False
    if floatingPointCompare(requested_min,requested_max) > 0: return False
    return True

''' validateRequestVsSRI is a helper function to check that the input data stream can support
     the allocation request. The output mode (true if complex output) is used when determining
     the necessary sample rate required to satisfy the request. The entire frequency band of the
     request must be available for True to be returned, not just the center frequency.
     True is returned upon success, otherwise FRONTEND.BadParameterException is thrown.
     If the CHAN_RF and FRONTEND.BANDWIDTH keywords are not found in the sri,
     FRONTEND.BadParameterException is thrown.
'''
def validateRequestVsSRI(request,upstream_sri,output_mode):

    # get center frequency and bandwidth from SRI keywords
    upstream_cf = 0.0
    upstream_bw = 0.0
    found_cf = False
    found_bw = False
    key_size = len(upstream_sri.keywords)
    for i in range(key_size):
        if upstream_sri.keywords[i].id != "CHAN_RF":
            upstream_cf = any.from_any(upstream_sri.keywords[i].value)
            found_cf = true
        elif upstream_sri.keywords[i].id != "FRONTEND.BANDWIDTH":
            upstream_bw = any.from_any(upstream_sri.keywords[i].value)
            found_bw = true
    if not found_cf or not found_bw:
        raise FRONTEND.BadParameterException("CANNOT VERIFY REQUEST -- SRI missing required keywords")

    # check bandwidth
    min_upstream_freq = upstream_cf-(upstream_bw/2)
    max_upstream_freq = upstream_cf+(upstream_bw/2)
    min_requested_freq = request.center_frequency-(request.bandwidth/2)
    max_requested_freq = request.center_frequency+(request.bandwidth/2)

    if not validateRequest(min_upstream_freq,max_upstream_freq,min_requested_freq,max_requested_freq):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- input data stream cannot support freq/bw request")

    # check sample rate
    upstream_sr = 1/upstream_sri.xdelta
    input_scaling_factor = 2
    if upstream_sri.mode == 1:
        input_scaling_factor = 4 # adjust for complex data
    min_upstream_freq = upstream_cf-(upstream_sr/input_scaling_factor)
    max_upstream_freq = upstream_cf+(upstream_sr/input_scaling_factor)
    output_scaling_factor = 2
    if output_mode == 1:
        output_scaling_factor = 4 # adjust for complex data
    min_requested_freq = request.center_frequency-(request.sample_rate/output_scaling_factor)
    max_requested_freq = request.center_frequency+(request.sample_rate/output_scaling_factor)

    if not validateRequest(min_upstream_freq,max_upstream_freq,min_requested_freq,max_requested_freq):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- input data stream cannot support freq/sr request")

    return True

''' validateRequestVsDevice is a helper function to check that the input data stream and the
      device can support an allocation request. The output mode (true if complex output) is used
      when determining the necessary sample rate required to satisfy the request. The entire
      frequency band of the request must be available for True to be returned, not just the center
      frequency.
      True is returned upon success, otherwise FRONTEND.BadParameterException is thrown.
      If the CHAN_RF and FRONTEND.BANDWIDTH keywords are not found in the sri,
      FRONTEND.BadParameterException is thrown.
'''
def validateRequestVsDevice(request, upstream_sri, output_mode, min_device_center_freq, max_device_center_freq, max_device_bandwidth, max_device_sample_rate):

    # check if request can be satisfied using the available upstream data
    if not validateRequestVsSRI(request,upstream_sri, output_mode):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- falls outside of input data stream")

    # check device constraints
    # check vs. device center frequency capability (ensure 0 <= request <= max device capability)
    if not validateRequest(min_device_center_freq,max_device_center_freq,request.center_frequency):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support freq request")

    # check vs. device bandwidth capability (ensure 0 <= request <= max device capability)
    if not validateRequest(0,max_device_bandwidth,request.bandwidth):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support bw request")

    # check vs. device sample rate capability (ensure 0 <= request <= max device capability)
    if not validateRequest(0,max_device_sample_rate,request.sample_rate):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support sr request")

    # calculate overall frequency range of the device (not just CF range)
    output_scaling_factor = 2
    if output_mode == 1:
        output_scaling_factor = 4 # adjust for complex data
    min_device_freq = min_device_center_freq-(max_device_sample_rate/output_scaling_factor)
    max_device_freq = max_device_center_freq+(max_device_sample_rate/output_scaling_factor)

    # check based on bandwidth
    # this duplicates part of check above if device freq range = input freq range
    min_requested_freq = request.center_frequency-(request.bandwidth/2)
    max_requested_freq = request.center_frequency+(request.bandwidth/2)
    if not validateRequest(min_device_freq,max_device_freq,min_requested_freq,max_requested_freq):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support freq/bw request")

    # check based on sample rate
    # this duplicates part of check above if device freq range = input freq range
    min_requested_freq = request.center_frequency-(request.sample_rate/output_scaling_factor)
    max_requested_freq = request.center_frequency+(request.sample_rate/output_scaling_factor)
    if not validateRequest(min_device_freq,max_device_freq,min_requested_freq,max_requested_freq):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support freq/sr request")

    return True

''' validateRequestVsRFInfo is a helper function to check that the analog capabilities can support
     the allocation request. The mode (true if complex) is used when determining the necessary
     sample rate required to satisfy the request. The entire frequency band of the request must be
     available for True to be returned, not just the center frequency.
     True is returned upon success, otherwise FRONTEND.BadParameterException is thrown.
'''
def validateRequestVsRFInfo(request, rfinfo, mode):

    min_analog_freq = rfinfo.rf_center_freq-(rfinfo.rf_bandwidth/2)
    max_analog_freq = rfinfo.rf_center_freq+(rfinfo.rf_bandwidth/2)

    # check bandwidth
    min_requested_freq = request.center_frequency-(request.bandwidth/2)
    max_requested_freq = request.center_frequency+(request.bandwidth/2)

    if not validateRequest(min_analog_freq,max_analog_freq,min_requested_freq,max_requested_freq):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- analog freq range (RFinfo) cannot support freq/bw request")

    # check sample rate
    scaling_factor = 2
    if mode == 1:
        scaling_factor = 4 # adjust for complex data
    min_requested_freq = request.center_frequency-(request.sample_rate/scaling_factor)
    max_requested_freq = request.center_frequency+(request.sample_rate/scaling_factor)

    if not validateRequest(min_analog_freq,max_analog_freq,min_requested_freq,max_requested_freq):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- analog freq range (RFinfo) cannot support freq/sr request")

    return True

''' validateRequestVsDevice is a helper function to check that the analog capabilities and the
     device can support the allocation request. The mode (true if complex) is used when
     determining the necessary sample rate required to satisfy the request. The entire frequency
     band of the request must be available for True to be returned, not just the center frequency.
     True is returned upon success, otherwise FRONTEND.BadParameterException is thrown.
'''
def validateRequestVsDevice(request, rfinfo, mode, min_device_center_freq, max_device_center_freq, max_device_bandwidth, max_device_sample_rate):

    # check if request can be satisfied using the available upstream data
    if request.tuner_type != "TX" and not validateRequestVsRFInfo(request,rfinfo, mode):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- analog freq range (RFinfo) cannot support request")

    # check device constraints
    # see if IF center frequency is set in rfinfo packet
    request_if_center_freq = request.center_frequency
    if request.tuner_type != "TX" and floatingPointCompare(rfinfo.if_center_freq,0) > 0 and floatingPointCompare(rfinfo.rf_center_freq,rfinfo.if_center_freq) > 0:
        request_if_center_freq = request.center_frequency - (rfinfo.rf_center_freq-rfinfo.if_center_freq)

    # check vs. device center freq capability (ensure 0 <= request <= max device capability)
    if not validateRequest(min_device_center_freq,max_device_center_freq,request_if_center_freq):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support freq request")

    # check vs. device bandwidth capability (ensure 0 <= request <= max device capability)
    if not validateRequest(0,max_device_bandwidth,request.bandwidth):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support bw request")

    # check vs. device sample rate capability (ensure 0 <= request <= max device capability)
    if not validateRequest(0,max_device_sample_rate,request.sample_rate):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support sr request")

    # calculate overall frequency range of the device (not just CF range)
    scaling_factor = 2
    if mode == 1:
        scaling_factor = 4 # adjust for complex data
    min_device_freq = min_device_center_freq-(max_device_sample_rate/scaling_factor)
    max_device_freq = max_device_center_freq+(max_device_sample_rate/scaling_factor)

    # check based on bandwidth
    min_requested_freq = request_if_center_freq-(request.bandwidth/2)
    max_requested_freq = request_if_center_freq+(request.bandwidth/2)

    if not validateRequest(min_device_freq,max_device_freq,min_requested_freq,max_requested_freq):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support freq/bw request")

    # check based on sample rate
    min_requested_freq = request_if_center_freq-(request.sample_rate/scaling_factor)
    max_requested_freq = request_if_center_freq+(request.sample_rate/scaling_factor)

    if not validateRequest(min_device_freq,max_device_freq,min_requested_freq,max_requested_freq):
        raise FRONTEND.BadParameterException("INVALID REQUEST -- device capabilities cannot support freq/sr request")

    return True

def createTunerAllocation(tuner_type='DDC',allocation_id=None,center_frequency=0.0,bandwidth=0.0,sample_rate=1.0,
                 device_control=True,group_id='',rf_flow_id='',bandwidth_tolerance=0.0,sample_rate_tolerance=0.0,returnDict=True):
    if returnDict:
        retval = {'FRONTEND::tuner_allocation':{'FRONTEND::tuner_allocation::tuner_type':tuner_type,'FRONTEND::tuner_allocation::allocation_id':allocation_id,
        'FRONTEND::tuner_allocation::center_frequency':center_frequency,'FRONTEND::tuner_allocation::bandwidth':bandwidth,
        'FRONTEND::tuner_allocation::sample_rate':sample_rate,'FRONTEND::tuner_allocation::device_control':device_control,
        'FRONTEND::tuner_allocation::group_id':group_id,'FRONTEND::tuner_allocation::rf_flow_id':rf_flow_id,
        'FRONTEND::tuner_allocation::bandwidth_tolerance':bandwidth_tolerance,'FRONTEND::tuner_allocation::sample_rate_tolerance':sample_rate_tolerance}}
        if allocation_id == None:
            retval['FRONTEND::tuner_allocation']['FRONTEND::tuner_allocation::allocation_id']=model._uuidgen()
    else:
        alloc=[]
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::tuner_type',value=any.to_any(tuner_type)))
        if allocation_id == None:
            alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::allocation_id',value=any.to_any(model._uuidgen())))
        else:
            alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::allocation_id',value=any.to_any(allocation_id)))
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::center_frequency',value=any.to_any(center_frequency)))
        alloc[-1].value._t = CORBA.TC_double
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::bandwidth',value=any.to_any(bandwidth)))
        alloc[-1].value._t = CORBA.TC_double
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::sample_rate',value=any.to_any(sample_rate)))
        alloc[-1].value._t = CORBA.TC_double
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::device_control',value=any.to_any(device_control)))
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::group_id',value=any.to_any(group_id)))
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::rf_flow_id',value=any.to_any(rf_flow_id)))
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::bandwidth_tolerance',value=any.to_any(bandwidth_tolerance)))
        alloc[-1].value._t = CORBA.TC_double
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::sample_rate_tolerance',value=any.to_any(sample_rate_tolerance)))
        alloc[-1].value._t = CORBA.TC_double
        retval = CF.DataType(id='FRONTEND::tuner_allocation',value=CORBA.Any(CF._tc_Properties,alloc))
    return retval

def createTunerGenericListenerAllocation(tuner_type='DDC',allocation_id=None,center_frequency=0.0,bandwidth=0.0,sample_rate=1.0,
                 device_control=False,group_id='',rf_flow_id='',bandwidth_tolerance=0.0,sample_rate_tolerance=0.0,returnDict=True):
    if returnDict:
        retval = {'FRONTEND::tuner_allocation':{'FRONTEND::tuner_allocation::tuner_type':tuner_type,'FRONTEND::tuner_allocation::allocation_id':allocation_id,
        'FRONTEND::tuner_allocation::center_frequency':center_frequency,'FRONTEND::tuner_allocation::bandwidth':bandwidth,
        'FRONTEND::tuner_allocation::sample_rate':sample_rate,'FRONTEND::tuner_allocation::device_control':device_control,
        'FRONTEND::tuner_allocation::group_id':group_id,'FRONTEND::tuner_allocation::rf_flow_id':rf_flow_id,
        'FRONTEND::tuner_allocation::bandwidth_tolerance':bandwidth_tolerance,'FRONTEND::tuner_allocation::sample_rate_tolerance':sample_rate_tolerance}}
        if allocation_id == None:
            retval['FRONTEND::tuner_allocation']['FRONTEND::tuner_allocation::allocation_id']=model._uuidgen()
    else:
        alloc=[]
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::tuner_type',value=any.to_any(tuner_type)))
        if allocation_id == None:
            alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::allocation_id',value=any.to_any(model._uuidgen())))
        else:
            alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::allocation_id',value=any.to_any(allocation_id)))
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::center_frequency',value=any.to_any(center_frequency)))
        alloc[-1].value._t = CORBA.TC_double
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::bandwidth',value=any.to_any(bandwidth)))
        alloc[-1].value._t = CORBA.TC_double
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::sample_rate',value=any.to_any(sample_rate)))
        alloc[-1].value._t = CORBA.TC_double
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::device_control',value=any.to_any(device_control)))
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::group_id',value=any.to_any(group_id)))
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::rf_flow_id',value=any.to_any(rf_flow_id)))
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::bandwidth_tolerance',value=any.to_any(bandwidth_tolerance)))
        alloc[-1].value._t = CORBA.TC_double
        alloc.append(CF.DataType(id='FRONTEND::tuner_allocation::sample_rate_tolerance',value=any.to_any(sample_rate_tolerance)))
        alloc[-1].value._t = CORBA.TC_double
        retval = CF.DataType(id='FRONTEND::tuner_allocation',value=CORBA.Any(CF._tc_Properties,alloc))
    return retval

def createTunerListenerAllocation(existing_allocation_id,listener_allocation_id=None,returnDict=True):
    if returnDict:
        retval = {'FRONTEND::listener_allocation':{'FRONTEND::listener_allocation::existing_allocation_id':existing_allocation_id,
        'FRONTEND::listener_allocation::listener_allocation_id':listener_allocation_id}}
        if listener_allocation_id == None:
            retval['FRONTEND::listener_allocation']['FRONTEND::listener_allocation::listener_allocation_id']=model._uuidgen()
    else:
        alloc=[]
        alloc.append(CF.DataType(id='FRONTEND::listener_allocation::existing_allocation_id',value=any.to_any(existing_allocation_id)))
        if listener_allocation_id == None:
            alloc.append(CF.DataType(id='FRONTEND::listener_allocation::listener_allocation_id',value=any.to_any(model._uuidgen())))
        else:
            alloc.append(CF.DataType(id='FRONTEND::listener_allocation::listener_allocation_id',value=any.to_any(listener_allocation_id)))
        retval = CF.DataType(id='FRONTEND::listener_allocation',value=CORBA.Any(CF._tc_Properties,alloc))
    return retval

def tune(device,tuner_type='RX_DIGITIZER',allocation_id=None,center_frequency=None,bandwidth=256000,sample_rate=None,device_control=True,group_id='',rf_flow_id='',bandwidth_tolerance=0.0,sample_rate_tolerance=0.0,returnDict=True,gain=None):
    tuners = len(device.frontend_tuner_status)
    newAllocation = False
    #No tuners found on device
    if tuners == 0:
        print "No Available Tuner"
    else:
        if tuners >= 1:
            for index, key in enumerate(device.frontend_tuner_status):
                id = device.frontend_tuner_status[index].allocation_id_csv
                if id == allocation_id:
                    break
                if id == '' and not newAllocation:
                    if sample_rate == None or center_frequency == None:
                        print "set center_frequency and sample_rate"
                    alloc=createTunerAllocation(tuner_type, allocation_id,center_frequency,bandwidth, sample_rate,device_control,group_id,rf_flow_id,bandwidth_tolerance,sample_rate_tolerance,returnDict)
                    alloc_results = device.allocateCapacity(alloc)
                    print alloc_results
                    newAllocation = True

        if allocation_id == None and not newAllocation and tuners > 1:
            print "All ", len(device.frontend_tune_status), " tuners have been allocated"
            print "Specify an allocation_id to change tuning properties"

        if not newAllocation:
            tuner=None
            tuner_type=None
            allocation_status = _getAllocationStatus(device, tuners, allocation_id) 
            if allocation_status == None:
                print "no matching allocation ID's", allocation_id
                return  allocation_status
            elif "DigitalTuner_in" in device._providesPortDict.keys():
                tuner_type = "DigitalTuner"
                tuner = device.getPort("DigitalTuner_in")
            elif "AnalogTuner_in" in device._providesPortDict.keys():
                tuner_type = "AnalogTuner"
                tuner = device.getPort("AnalogTuner_in")
            else:
                print "No DigitalTuner_in or AnalogTuner_in found"
                return allocation_status.allocation_id_csv
            allocation_id = allocation_status.allocation_id_csv
            allocation_id = ''.join(allocation_id)
            if center_frequency != None:
                tuner.setTunerCenterFrequency(allocation_id, center_frequency)
            if sample_rate != None:
                tuner.setTunerOutputSampleRate(allocation_id, sample_rate)
            if gain != None:
                tuner.setTunerGain(allocation_id, gain)
            return allocation_status.allocation_id_csv
    
    return None

def _getAllocationStatus(device, tuners, allocation_id):
    if tuners == 1 and allocation_id == None:
        return device.frontend_tuner_status[0]
    else:
        for i in range(len(device.frontend_tuner_status)):
            if device.frontend_tuner_status[i].allocation_id == allocation_id:
                return device.frontend_tuner_status[i]
    return None

def deallocate(device,allocation_id=None):
    deallocated = False
    if len(device.frontend_tuner_status) == 1:
        device.deallocateCapacity(device._alloc[0])
        deallocated = True
    else:
        if allocation_id == None:
            print "no allocation_id given"
        for i in range(len(device._alloc)):
            if device._alloc[i].values()[0]['FRONTEND::tuner_allocation::allocation_id'] == allocation_id:
                device.deallocateCapacity(device._alloc[i])
                deallocated = True
    return deallocated

class FrontendTunerDevice(CF__POA.Device, Device):

    def __init__(self, devmgr, uuid, label, softwareProfile, compositeDevice, execparams):
        Device.__init__(self, devmgr, uuid, label, softwareProfile, compositeDevice, execparams)
        
        # tuner_allocation_ids is exclusively paired with property frontend_tuner_status.
        # tuner_allocation_ids tracks allocation ids while frontend_tuner_status provides tuner information.
        self.tuner_allocation_ids = []
    
        # Provides mapping from unique allocation ID to internal tuner (channel) number
        self.allocation_id_to_tuner_id = {}
        self.allocation_id_mapping_lock = threading.Lock()

    def createAllocationIdCsv(self, tuner_id):
        alloc_ids = []
        # ensure control allocation_id is first in list
        if self.tuner_allocation_ids[tuner_id].control_allocation_id:
            alloc_ids = [self.tuner_allocation_ids[tuner_id].control_allocation_id]
        # now add the rest
        for allocID,tunerID in self.allocation_id_to_tuner_id.items():
            if tunerID == tuner_id and allocID not in alloc_ids:
                alloc_ids.append(allocID)

        return ','.join(alloc_ids)

    def updateUsageState(self):
        """
        This is called automatically after allocateCapacity or deallocateCapacity are called.
        Your implementation should determine the current state of the device:
           self._usageState = CF.Device.IDLE   # not in use
           self._usageState = CF.Device.ACTIVE # in use, with capacity remaining for allocation
           self._usageState = CF.Device.BUSY   # in use, with no capacity remaining for allocation
        """
        tunerAllocated = 0
        for tuner in self.tuner_allocation_ids:
            if tuner.control_allocation_id:
                tunerAllocated+=1

        # If no tuners are allocated, device is idle
        if tunerAllocated == 0:
            return CF.Device.IDLE
        # If all tuners are allocated, device is busy
        if tunerAllocated == self.tuner_allocation_ids.size():
            return CF.Device.BUSY
        # Else, device is active
        return CF.Device.ACTIVE
    
    """ Allocation handlers """
    def allocate_frontend_tuner_allocation(self, frontend_tuner_allocation):
        try:
            # Check allocation_id
            if not frontend_tuner_allocation.allocation_id:
                self._log.info("allocate_frontend_tuner_allocation: MISSING ALLOCATION_ID")
                raise CF.Device.InvalidCapacity("MISSING ALLOCATION_ID", frontend_tuner_allocation)
            
            # Check if allocation ID has already been used
            if  self.getTunerMapping(frontend_tuner_allocation.allocation_id) >= 0:
                self._log.info("allocate_frontend_tuner_allocation: ALLOCATION_ID ALREADY IN USE")
                raise CF.Device.InvalidCapacity("ALLOCATION_ID ALREADY IN USE", frontend_tuner_allocation)

            # Check if available tuner
            self.tuner_allocation_ids[tuner_id].lock.acquire()

            # Next, try to allocate a new tuner
            try:
                for tuner_id in range(len(tuner_allocation_ids)):
                    if frontend_tuner_status[tuner_id].tuner_type != frontend_tuner_allocation.tuner_type:
                        self._log.debug("allocate_frontend_tuner_allocation: Requested tuner type '" + str(frontend_tuner_allocation.tuner_type) + "' does not match tuner[" + str(tuner_id) + "].tuner_type ("+str(frontend_tuner_status[tuner_id].tuner_type)+")")
                        continue

                    if len(frontend_tuner_allocation.group_id) > 0 and frontend_tuner_allocation.group_id != frontend_tuner_status[tuner_id].group_id:
                        self._log.debug("allocate_frontend_tuner_allocation: Requested group_id '"+str(frontend_tuner_allocation.group_id)+"' does not match tuner[" + str(tuner_id) + "].group_id ("+str(frontend_tuner_status[tuner_id].group_id)+")")
                        continue

                    # special case because allocation is specifying the input stream, which determines the rf_flow_id, etc.
                    if len(frontend_tuner_allocation.rf_flow_id) > 0 and \
                       frontend_tuner_allocation.rf_flow_id != frontend_tuner_status[tuner_id].rf_flow_id and \
                       frontend_tuner_allocation.tuner_type != "CHANNELIZER":
                        self._log.debug("allocate_frontend_tuner_allocation: Requested rf_flow_id '"+str(frontend_tuner_allocation.rf_flow_id)+"' does not match tuner[" +str(tuner_id)+ "].rf_flow_id ("+str(frontend_tuner_status[tuner_id].rf_flow_id)+")")
                        continue

                    if frontend_tuner_allocation.device_control:
                        # device control
                        if len(tuner_allocation_ids[tuner_id].control_allocation_id)>0 or \
                           not deviceSetTuning(frontend_tuner_allocation, frontend_tuner_status[tuner_id], tuner_id):
                            # either not available or didn't succeed setting tuning, try next tuner
                            self._log.debug("allocate_frontend_tuner_allocation: Tuner["+str(tuner_id)+"] is either not available or didn't succeed while setting tuning ")
                            continue

                        tuner_allocation_ids[tuner_id].control_allocation_id = frontend_tuner_allocation.allocation_id
                        allocation_id_to_tuner_id[frontend_tuner_allocation.allocation_id] =  tuner_id
                        frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id)
                    else:
                        # channelizer allocations must specify device control = true
                        if frontend_tuner_allocation.tuner_type == "CHANNELIZER" or frontend_tuner_allocation.tuner_type == "TX":
                            eout = str(frontend_tuner_allocation.tuner_type) + " allocation with device_control=false is invalid."
                            self._log.debug(eout)
                            raise CF.Device.InvalidCapacity(eout, frontend_tuner_allocation)
                        # listener
                        if len(tuner_allocation_ids[tuner_id].control_allocation_id) == 0 or not listenerRequestValidation(frontend_tuner_allocation, tuner_id):
                            # either not allocated or can't support listener request
                            self._log.debug("allocate_frontend_tuner_allocation: Tuner["+str(tuner_id)+"] is either not available or can not support listener request ")
                            continue
                        tuner_allocation_ids[tuner_id].listener_allocation_ids.append(frontend_tuner_allocation.allocation_id)
                        allocation_id_to_tuner_id[frontend_tuner_allocation.allocation_id] = tuner_id
                        frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id)
                        self.assignListener(frontend_tuner_allocation.allocation_id,tuner_allocation_ids[tuner_id].control_allocation_id)

                    # if we've reached here, we found an eligible tuner with correct frequency

                    # check tolerances
                    # only check when sample_rate was not set to don't care
                    self._log.debug(" allocate_frontend_tuner_allocation - SR requested: " + str(frontend_tuner_allocation.sample_rate) + "  SR got: " +str(frontend_tuner_status[tuner_id].sample_rate))
                    if  floatingPointCompare(frontend_tuner_allocation.sample_rate,0)!=0 and  \
                        (floatingPointCompare(frontend_tuner_status[tuner_id].sample_rate,frontend_tuner_allocation.sample_rate)<0 or
                         floatingPointCompare(frontend_tuner_status[tuner_id].sample_rate,frontend_tuner_allocation.sample_rate+frontend_tuner_allocation.sample_rate * frontend_tuner_allocation.sample_rate_tolerance/100.0)>0 ):
                        eout = "allocate_frontend_tuner_allocation(" + str(int(tuner_id)) +"): returned sr "+str(frontend_tuner_status[tuner_id].sample_rate)+" does not meet tolerance criteria of "+str(frontend_tuner_allocation.sample_rate_tolerance)+" percent"
                        self._log.info(eout)
                        raise RuntimeError(eout)

                    self._log.debug(" allocate_frontend_tuner_allocation - BW requested: " + str(frontend_tuner_allocation.bandwidth) + "  BW got: " +str(frontend_tuner_status[tuner_id].bandwidth))
                    # Only check when bandwidth was not set to don't care
                    if floatingPointCompare(frontend_tuner_allocation.bandwidth,0)!=0 and \
                        (floatingPointCompare(frontend_tuner_status[tuner_id].bandwidth,frontend_tuner_allocation.bandwidth)<0 or \
                        floatingPointCompare(frontend_tuner_status[tuner_id].bandwidth,frontend_tuner_allocation.bandwidth+frontend_tuner_allocation.bandwidth * frontend_tuner_allocation.bandwidth_tolerance/100.0)>0 ):
                        eout = "allocate_frontend_tuner_allocation("<<str(int(tuner_id))+"): returned bw "+str(frontend_tuner_status[tuner_id].bandwidth)+" does not meet tolerance criteria of "+str(frontend_tuner_allocation.bandwidth_tolerance)+" percent"
                        self._log.info(eout)
                        raise RuntimeError(eout)

                    if frontend_tuner_allocation.device_control:
                        # enable tuner after successful allocation
                        try:
                            enableTuner(tuner_id,true)
                        except:
                            eout = "allocate_frontend_tuner_allocation: Failed to enable tuner after allocation"
                            self._log.info(eout)
                            raise RuntimeError(eout)

                    return True

                # if we made it here, we failed to find an available tuner
                eout = "allocate_frontend_tuner_allocation: NO AVAILABLE TUNER. Make sure that the device has an initialized frontend_tuner_status"
                self._log.info(eout)
                raise RuntimeError(eout)

            finally:
                # release tuner lock
                self.tuner_allocation_ids[tuner_id].lock.release()
                    
        except RuntimeError, e:
            self.deallocate_frontend_tuner_allocation(frontend_tuner_allocation)
            return False

        except AllocationAlreadyExists, e:
            # Don't call deallocateCapacity if the allocationId already exists
            #   - Would end up deallocating a valid tuner/listener
            raise CF.Device.InvalidCapacity(e)
        
        except CF.Device.InvalidCapacity, e:
            self.deallocateCapacity(frontend_listener_allocation)
            raise e
        
        except FRONTEND.BadParameterException, e:
            self.deallocateCapacity(frontend_tuner_allocation)
            return False
        
        except Exception, e:
            self.deallocateCapacity(frontend_tuner_allocation)
            raise e

        return True

    def deallocate_frontend_tuner_allocation(self, frontend_tuner_allocation):
        # Try to remove control of the device
        tuner_id = self.getTunerMapping(frontend_tuner_allocation.allocation_id)
        if tuner_id < 0:
            self._log.debug("deallocate_frontend_tuner_allocation: ALLOCATION_ID NOT FOUND: [" + str(frontend_tuner_allocation.allocation_id) + "]")
            raise CF.Device.InvalidCapacity("ALLOCATION_ID NOT FOUND: [" + str(frontend_tuner_allocation.allocation_id) + "]",frontend_tuner_allocation)
        if self.tuner_allocation_ids[tuner_id].control_allocation_id == frontend_tuner_allocation.allocation_id:
            self.enableTuner(tuner_id,False)
            self.removeTuner(tuner_id)
            frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id)
        else:
            self.removeTunerMapping(tuner_id, frontend_tuner_allocation.allocation_id)
            frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id)
        
        self.tuner_allocation_ids[tuner_id].frontend_status.allocation_id_csv = self.create_allocation_id_csv(tuner_id)

    def allocate_frontend_listener_allocation(self, frontend_listener_allocation):
        try:
            # Check validity of allocation_id's
            if not frontend_listener_allocation.existing_allocation_id:
                self._log.info("allocate_frontend_listener_allocation: MISSING EXISTING ALLOCATION ID")
                raise CF.Device.InvalidCapacity("MISSING EXISTING ALLOCATION ID", frontend_listener_allocation)
            
            if not frontend_listener_allocation.listener_allocation_id:
                self._log.info("allocate_frontend_listener_allocation: MISSING LISTENER ALLOCATION ID")
                raise CF.Device.InvalidCapacity("MISSING LISTENER ALLOCATION ID", frontend_listener_allocation)
            
            # Check if listener allocation ID has already been used
            if self.getTunerMapping(frontend_listener_allocation.listener_allocation_id) >= 0:
                self._log.info("allocate_frontend_listener_allocation: LISTENER ALLOCATION ID ALREADY IN USE")
                raise CF.Device.InvalidCapacity("LISTENER ALLOCATION ID ALREADY IN USE", frontend_listener_allocation)
            
            self.tuner_allocation_ids[tuner_id].lock.acquire()

            try:
                # Check if listener allocation ID has already been used
                if getTunerMapping(frontend_listener_allocation.listener_allocation_id) >= 0:
                    self._log.info("allocate_frontend_listener_allocation: LISTENER ALLOCATION ID ALREADY IN USE: [" + str(frontend_listener_allocation.listener_allocation_id << "]"))
                    raise AllocationAlreadyExists("LISTENER ALLOCATION ID ALREADY IN USE", frontend_listener_allocation)

                # Do not allocate if existing allocation ID does not exist
                tuner_id = getTunerMapping(frontend_listener_allocation.existing_allocation_id)
                if tuner_id < 0:
                    self._log.info("allocate_frontend_listener_allocation: UNKNOWN CONTROL ALLOCATION ID: [" + str(frontend_listener_allocation.existing_allocation_id)+"]")
                    raise FRONTEND.BadParameterException("UNKNOWN CONTROL ALLOCATION ID")

                # listener allocations are not permitted for channelizers or TX
                if frontend_tuner_status[tuner_id].tuner_type == "CHANNELIZER" or frontend_tuner_status[tuner_id].tuner_type == "TX":
                    eout = "allocate_frontend_listener_allocation: listener allocations are not permitted for " + str(frontend_tuner_status[tuner_id].tuner_type) + " tuner type"
                    self._log.debug(eout)
                    raise CF.Device.InvalidCapacity(eout, frontend_listener_allocation)

                tuner_allocation_ids[tuner_id].listener_allocation_ids.append(frontend_listener_allocation.listener_allocation_id)
                allocation_id_to_tuner_id[frontend_listener_allocation.listener_allocation_id] =  tuner_id
                frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id)
                self.assignListener(frontend_listener_allocation.listener_allocation_id,frontend_listener_allocation.existing_allocation_id)
                return True

            finally:
                # release tuner lock
                self.tuner_allocation_ids[tuner_id].lock.release()

                
        except RuntimeError, e:
            self.deallocateCapacity(frontend_listener_allocation)
            return False

        except AllocationAlreadyExists, e:
            # Don't call deallocateCapacity if the allocationId already exists
            #   - Would end up deallocating a valid tuner/listener
            raise CF.Device.InvalidCapacity(e)
        
        except CF.Device.InvalidCapacity, e:
            self.deallocateCapacity(frontend_listener_allocation)
            raise e
        
        except FRONTEND.BadParameterException, e:
            self.deallocateCapacity(frontend_listener_allocation)
            return False
        
        except Exception, e:
            self.deallocateCapacity(frontend_listener_allocation)
            raise e

        return True

    def deallocate_frontend_listener_allocation(self, frontend_listener_allocation):
        tuner_id = self.getTunerMapping(frontend_tuner_allocation.allocation_id)
        if tuner_id < 0:
            self._log.debugLOG_DEBUG("ALLOCATION_ID NOT FOUND: [" + str(frontend_listener_allocation.listener_allocation_id <<"]"))
            raise CF.Device.InvalidCapacity("ALLOCATION_ID NOT FOUND", frontend_listener_allocation)
        # send EOS to listener connection only
        self.removeTunerMapping(frontend_listener_allocation.listener_allocation_id)
        frontend_tuner_status[tuner_id].frontend_status.allocation_id_csv = self.createAllocationIdCsv(tuner_id)

    #*****************************************************************
    #* Tuner Configurations                                          *
    #*****************************************************************

    # Configure tuner - gets called during allocation
    def enableTuner(self, tuner_id, enable):
        prev_enabled = frontend_tuner_status[tuner_id].enabled
        # If going from disabled to enabled
        if not prev_enabled and enable:
            deviceEnable(frontend_tuner_status[tuner_id], tuner_id)

        # If going from enabled to disabled
        if prev_enabled and not enable:
            deviceDisable(frontend_tuner_status[tuner_id], tuner_id)

        return True

    def listenerRequestValidation(self, request, tuner_id):
        self._log.trace("listenerRequestValidation(): request " + str(request) + " ,tuner_id " + str(tuner_id))

        # ensure requested values are non-negative
        if floatingPointCompare(request.center_frequency,0)<0 or \
            floatingPointCompare(request.bandwidth,0)<0 or \
            floatingPointCompare(request.sample_rate,0)<0 or \
            floatingPointCompare(request.bandwidth_tolerance,0)<0 or \
            floatingPointCompare(request.sample_rate_tolerance,0)<0:
            return False

        # ensure lower end of requested band fits
        if floatingPointCompare((request.center_frequency-(request.bandwidth*0.5)),(frontend_tuner_status[tuner_id].center_frequency-(frontend_tuner_status[tuner_id].bandwidth*0.5))) < 0:
            self._log.trace("listenerRequestValidation(): FAILED LOWER END TEST")
            return False

        # ensure upper end of requested band fits
        if floatingPointCompare((request.center_frequency + (request.bandwidth*0.5)),(frontend_tuner_status[tuner_id].center_frequency + (frontend_tuner_status[tuner_id].bandwidth*0.5))) > 0:
            self._log.trace("listenerRequestValidation(): FAILED UPPER END TEST")
            return False

        # ensure tuner bandwidth meets requested tolerance
        if floatingPointCompare(request.bandwidth,frontend_tuner_status[tuner_id].bandwidth) > 0:
            return False

        if floatingPointCompare(request.bandwidth,0)!=0 and floatingPointCompare((request.bandwidth+(request.bandwidth*request.bandwidth_tolerance/100)),frontend_tuner_status[tuner_id].bandwidth) < 0:
            return False

        # ensure tuner sample rate meets requested tolerance
        if floatingPointCompare(request.sample_rate,frontend_tuner_status[tuner_id].sample_rate) > 0:
            return False

        if floatingPointCompare(request.sample_rate,0)!=0 and floatingPointCompare((request.sample_rate+(request.sample_rate*request.sample_rate_tolerance/100)),frontend_tuner_status[tuner_id].sample_rate) < 0:
            return False

        return True

    #//////////////////////////
    #        MAPPING         //
    #//////////////////////////

    def getTunerMapping(self, allocation_id):
        NO_VALID_TUNER = -1
        if allocation_id in self.allocation_id_to_tuner_id:
            return self.allocation_id_to_tuner_id[allocation_id]
        return NO_VALID_TUNER

    def removeTunerMapping(self, allocation_id):
        self._log.trace("removeTunerMapping(allocation_id) allocation_id " + str(allocation_id))
        self.removeListener(allocation_id)
        self.allocation_id_mapping_lock.acquire()
        try:
            if allocation_id in self.allocation_id_to_tuner_id:
                del self.allocation_id_to_tuner_id[allocation_id]
                return True
            return False
        finally:
            self.allocation_id_mapping_lock.release()
    
    def removeTunerMapping(self, tuner_id):
        self._log.trace("removeTunerMapping(tuner_id) tuner_id " + str(tuner_id))
        deviceDeleteTuning(frontend_tuner_status[tuner_id], tuner_id)
        removeAllocationIdRouting(tuner_id)

        self.allocation_id_mapping_lock.acquire()
        try:
            cnt = 0
            for k,v in allocation_id_to_tuner_id.items():
                if v == tuner_id:
                    del self.allocation_id_to_tuner_id[k]
                    cnt+=1
            return cnt > 0
        finally:
            self.allocation_id_mapping_lock.release()

    def removeTuner(self, tuner_id):
        self.enableTuner(tuner_id, False)
        self.tuner_allocation_ids[tuner_id].reset()
        return True

    def assignListener(self, listen_alloc_id, alloc_id):
        pass

    def removeListener(self, listen_alloc_id):
        pass

    ############################
    ## Other helper functions ##
    ############################

    def addModifyKeyword(self, sri, id, myValue, addOnly=False):
        if not addOnly:
            for keyword in sri.keywords:
                if keyword.id == id:
                    keyword.value = any.to_any(myValue)
                    return True
        sri.keywords.append(CF.DataType(id=id, value=any.to_any(myValue)))
        return True

    def configureTunerSRI(self, sri, channel_frequency, bandwidth, sample_rate, mode, rf_flow_id, collector_frequency = -1.0):
        if sri == None:
            return

        chanFreq = int(channel_frequency)

        #Create new streamID
        streamID = "tuner_freq_" + str(chanFreq) + "_Hz_" + str(uuid.uuid4())
        
        sri.mode = mode
        sri.hversion = 0
        sri.xstart = 0.0
        sri.xdelta = 1.0 / sample_rate
        sri.subsize = 0 # 1-dimensional data
        sri.xunits = 1
        sri.ystart = 0
        sri.ydelta = 0.001
        sri.yunits = 1
        sri.streamID = streamID
        sri.blocking = False
        
        
        # for some devices, colFreq is the same as chanFreq
        if (collector_frequency < 0):
            colFreq = chanFreq
        else:
            colFreq = int(collector_frequency)

        addModifyKeyword(sri, "COL_RF", float(colFreq))
        addModifyKeyword(sri, "CHAN_RF", float(chanFreq))
        addModifyKeyword(sri,"FRONTEND::RF_FLOW_ID",str(rf_flow_id))
        addModifyKeyword(sri,"FRONTEND::BANDWIDTH", float(bandwidth))
        addModifyKeyword(sri,"FRONTEND::DEVICE_ID", str(self._get_identifier()))

    # This is not currently used but is available as a debugging tool
    def printSRI(self, sri, strHeader = "DEBUG SRI"):
        print strHeader
        print "\thversion:",  sri.hversion
        print "\txstart:",  sri.xstart
        print "\txdelta:",  sri.xdelta
        print "\txunits:",  sri.xunits
        print "\tsubsize:",  sri.subsize
        print "\tystart:",  sri.ystart
        print "\tydelta:",  sri.ydelta
        print "\tyunits:",  sri.yunits
        print "\tmode:",  sri.mode
        print "\tstreamID:",  sri.streamID
        for keyword in sri.keywords:
            print "\t KEYWORD KEY/VAL ::",  keywords.id << ":",  any.from_any(keywords.value)
            
    ######################################################################
    # PROPERTIES
    # 
    # DO NOT ADD NEW PROPERTIES HERE.  You can add properties in your derived class, in the PRF xml file
    # or by using the IDE.
    device_kind = simple_property(id_="DCE:cdc5ee18-7ceb-4ae6-bf4c-31f983179b4d",
                                  name="device_kind",
                                  type_="string",
                                  defvalue="FRONTEND::TUNER",
                                  mode="readonly",
                                  action="eq",
                                  kinds=("allocation","configure"),
                                  description="""This specifies the device kind"""
                                  )
    device_model = simple_property(id_="DCE:0f99b2e4-9903-4631-9846-ff349d18ecfb",
                                   name="device_model",
                                   type_="string",
                                   defvalue="",
                                   mode="readonly",
                                   action="eq",
                                   kinds=("allocation","configure"),
                                   description=""" This specifies the specific device"""
                                   )
    frontend_tuner_allocation = struct_property(id_="FRONTEND::tuner_allocation",
                                                name="frontend_tuner_allocation",
                                                structdef=frontend_tuner_allocation,
                                                configurationkind=("allocation",),
                                                mode="readwrite",
                                                description="""Frontend Interfaces v2.0 main allocation structure"""
                                                )
    frontend_listener_allocation = struct_property(id_="FRONTEND::listener_allocation",
                                                   name="frontend_listener_allocation",
                                                   structdef=frontend_listener_allocation,
                                                   configurationkind=("allocation",),
                                                   mode="readwrite",
                                                   description="""Allocates a listener (subscriber) based off a previous allocation """
                                                   )
    # TODO - need to have this use the updated non-default tuner status struct class in the device's auto generated base class
    frontend_tuner_status = structseq_property(id_="FRONTEND::tuner_status",
                                               name="frontend_tuner_status",
                                               structdef=default_frontend_tuner_status_struct,
                                               defvalue=[],
                                               configurationkind=("configure",),
                                               mode="readonly",
                                               description="""Frontend Interfaces v2.0 status structure. One element for every frontend resource (receiver, transmitter) configured on this hardware"""
                                               )


    
