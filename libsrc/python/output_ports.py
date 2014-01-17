
from ossie.cf import CF, CF__POA, ExtendedCF
from ossie.cf.CF import Port
from ossie.utils import uuid

#import copy, time
import threading
#from ossie.resource import usesport, providesport
#import bulkio
#from redhawk.frontendInterfaces import FRONTEND__POA
from redhawk.frontendInterfaces import FRONTEND


class OutPort (CF__POA.Port ):
    def __init__(self, name, PortTypeClass, logger=None ):
        self.name = name
        self.PortType = PortTypeClass
        self.logger = logger
        self.outConnections = {} # key=connectionId,  value=port
        self.port_lock = threading.Lock()

        if self.logger:
            self.logger.debug('frontend::OutPort CTOR port:' + str(self.name))
            

    def connectPort(self, connection, connectionId):

        if self.logger:
            self.logger.trace('frontend::OutPort  connectPort ENTER ')

        self.port_lock.acquire()
        try:
           try:
              port = connection._narrow(self.PortType)
              self.outConnections[str(connectionId)] = port
              self.refreshSRI = True

              if self.logger:
                  self.logger.debug('frontend::OutPort  CONNECT PORT:' + str(self.name) + ' CONNECTION:' + str(connectionId) )
              
           except:
              if self.logger:
                  self.logger.error('frontend::OutPort  CONNECT PORT:' + str(self.name) + ' PORT FAILED NARROW')
              raise Port.InvalidPort(1, "Invalid Port for Connection ID:" + str(connectionId) )
        finally:
            self.port_lock.release()

        if self.logger:
            self.logger.trace('frontend::OutPort  connectPort EXIT ')
            
    def disconnectPort(self, connectionId):
        if self.logger:
            self.logger.trace('frontend::OutPort  disconnectPort ENTER ')
        self.port_lock.acquire()
        try:
            self.outConnections.pop(str(connectionId), None)
            if self.logger:
                self.logger.debug( "frontend::OutPort DISCONNECT PORT:" + str(self.name) + " CONNECTION:" + str(connectionId ) )
        finally:
            self.port_lock.release()

        if self.logger:
            self.logger.trace('frontend::OutPort  disconnectPort EXIT ')
        
    def _get_connections(self):
        currentConnections = []
        self.port_lock.acquire()
        for id_, port in self.outConnections.items():
            currentConnections.append(ExtendedCF.UsesConnection(id_, port))
        self.port_lock.release()
        return currentConnections


class OutFrontendTunerPort(OutPort):
    def __init__(self, name, logger=None ):
        OutPort.__init__(self, name, FRONTEND.FrontendTuner, logger )

    def getTunerType(self, id):
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort getTunerType ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerType(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerType failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort  getTunerType EXIT ')

        return retVal

    def getTunerDeviceControl(self, id):
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort getTunerDeviceControl ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerDeviceControl(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerDeviceControl failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort  getTunerDeviceControl EXIT ')

        return retVal

    def getTunerGroupId(self, id):
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort getTunerGroupId ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerGroupId(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerGroupId failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort  getTunerGroupId EXIT ')

        return retVal

    def getTunerRfFlowId(self, id):
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort getTunerRfFlowId ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerRfFlowId(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerRfFlowId failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort  getTunerRfFlowId EXIT ')

        return retVal

    def getTunerStatus(self, id):
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort getTunerStatus ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerStatus(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerStatus failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutFrontendTunerPort  getTunerStatus EXIT ')

        return retVal

class OutAnalogTunerPort(OutPort):
    def __init__(self, name, logger=None ):
        OutPort.__init__(self, name, FRONTEND.AnalogTuner, logger )

    def getTunerType(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerType ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerType(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerType failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerType EXIT ')

        return retVal

    def getTunerDeviceControl(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerDeviceControl ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerDeviceControl(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerDeviceControl failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerDeviceControl EXIT ')

        return retVal

    def getTunerGroupId(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerGroupId ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerGroupId(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerGroupId failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerGroupId EXIT ')

        return retVal

    def getTunerRfFlowId(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerRfFlowId ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerRfFlowId(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerRfFlowId failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerRfFlowId EXIT ')

        return retVal

    def getTunerStatus(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerStatus ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerStatus(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerStatus failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerStatus EXIT ')

        return retVal

    def setTunerCenterFrequency(self, id, freq):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort setTunerCenterFrequency ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerCenterFrequency(id, freq)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerCenterFrequency failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  setTunerCenterFrequency EXIT ')

    def getTunerCenterFrequency(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerCenterFrequency ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerCenterFrequency(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerCenterFrequency failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerCenterFrequency EXIT ')

        return retVal

    def setTunerBandwidth(self, id, bw):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort setTunerBandwidth ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerBandwidth(id, bw)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerBandwidth failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  setTunerBandwidth EXIT ')

    def getTunerBandwidth(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerBandwidth ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerBandwidth(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerBandwidth failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerBandwidth EXIT ')

        return retVal

    def setTunerAgcEnable(self, id, enable):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort setTunerAgcEnable ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerAgcEnable(id, enable)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerAgcEnable failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  setTunerAgcEnable EXIT ')

    def getTunerAgcEnable(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerAgcEnable ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerAgcEnable(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerAgcEnable failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerAgcEnable EXIT ')

        return retVal

    def setTunerGain(self, id, gain):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort setTunerGain ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerGain(id, gain)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerGain failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  setTunerGain EXIT ')

    def getTunerGain(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerGain ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerGain(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerGain failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerGain EXIT ')

        return retVal

    def setTunerReferenceSource(self, id, source):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort setTunerReferenceSource ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerReferenceSource(id, source)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerReferenceSource failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  setTunerReferenceSource EXIT ')

    def getTunerReferenceSource(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerReferenceSource ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerReferenceSource(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerReferenceSource failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerReferenceSource EXIT ')

        return retVal

    def setTunerEnable(self, id, enable):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort setTunerEnable ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerEnable(id, enable)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerEnable failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  setTunerEnable EXIT ')

    def getTunerEnable(self, id):
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort getTunerEnable ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerEnable(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerEnable failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutAnalogTunerPort  getTunerEnable EXIT ')

        return retVal

class OutDigitalTunerPort(OutPort):
    def __init__(self, name, logger=None ):
        OutPort.__init__(self, name, FRONTEND.DigitalTuner, logger )

    def getTunerType(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerType ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerType(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerType failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerType EXIT ')

        return retVal

    def getTunerDeviceControl(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerDeviceControl ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerDeviceControl(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerDeviceControl failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerDeviceControl EXIT ')

        return retVal

    def getTunerGroupId(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerGroupId ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerGroupId(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerGroupId failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerGroupId EXIT ')

        return retVal

    def getTunerRfFlowId(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerRfFlowId ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerRfFlowId(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerRfFlowId failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerRfFlowId EXIT ')

        return retVal

    def getTunerStatus(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerStatus ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerStatus(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerStatus failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerStatus EXIT ')

        return retVal

    def setTunerCenterFrequency(self, id, freq):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort setTunerCenterFrequency ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerCenterFrequency(id, freq)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerCenterFrequency failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  setTunerCenterFrequency EXIT ')

    def getTunerCenterFrequency(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerCenterFrequency ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerCenterFrequency(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerCenterFrequency failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerCenterFrequency EXIT ')

        return retVal

    def setTunerBandwidth(self, id, bw):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort setTunerBandwidth ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerBandwidth(id, bw)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerBandwidth failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  setTunerBandwidth EXIT ')

    def getTunerBandwidth(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerBandwidth ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerBandwidth(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerBandwidth failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerBandwidth EXIT ')

        return retVal

    def setTunerAgcEnable(self, id, enable):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort setTunerAgcEnable ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerAgcEnable(id, enable)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerAgcEnable failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  setTunerAgcEnable EXIT ')

    def getTunerAgcEnable(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerAgcEnable ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerAgcEnable(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerAgcEnable failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerAgcEnable EXIT ')

        return retVal

    def setTunerGain(self, id, gain):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort setTunerGain ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerGain(id, gain)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerGain failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  setTunerGain EXIT ')

    def getTunerGain(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerGain ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerGain(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerGain failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerGain EXIT ')

        return retVal

    def setTunerReferenceSource(self, id, source):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort setTunerReferenceSource ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerReferenceSource(id, source)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerReferenceSource failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  setTunerReferenceSource EXIT ')

    def getTunerReferenceSource(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerReferenceSource ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerReferenceSource(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerReferenceSource failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerReferenceSource EXIT ')

        return retVal

    def setTunerEnable(self, id, enable):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort setTunerEnable ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerEnable(id, enable)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerEnable failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  setTunerEnable EXIT ')

    def getTunerEnable(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerEnable ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerEnable(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerEnable failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerEnable EXIT ')

        return retVal

    def setTunerOutputSampleRate(self, id, sr):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort setTunerOutputSampleRate ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port.setTunerOutputSampleRate(id, sr)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to setTunerOutputSampleRate failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  setTunerOutputSampleRate EXIT ')

    def getTunerOutputSampleRate(self, id):
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort getTunerOutputSampleRate ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port.getTunerOutputSampleRate(id)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to getTunerOutputSampleRate failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutDigitalTunerPort  getTunerOutputSampleRate EXIT ')

        return retVal

class OutGPSPort(OutPort):
    def __init__(self, name, logger=None ):
        OutPort.__init__(self, name, FRONTEND.GPS, logger )

    def _get_gps_info(self):
        if self.logger:
            self.logger.trace('frontend::OutGPSPort _get_gps_info ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port._get_gps_info()
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _get_gps_info failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutGPSPort  _get_gps_info EXIT ')

        return retVal

    def _set_gps_info(self, data):
        if self.logger:
            self.logger.trace('frontend::OutGPSPort _set_gps_info ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port._set_gps_info(data)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _set_gps_info failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutGPSPort  _set_gps_info EXIT ')

    def _get_gps_time_pos(self):
        if self.logger:
            self.logger.trace('frontend::OutGPSPort _get_gps_time_pos ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port._get_gps_time_pos()
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _get_gps_time_pos failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutGPSPort  _get_gps_time_pos EXIT ')

        return retVal

    def _set_gps_time_pos(self, data):
        if self.logger:
            self.logger.trace('frontend::OutGPSPort _set_gps_time_pos ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port._set_gps_time_pos(data)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _set_gps_time_pos failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutGPSPort  _set_gps_time_pos EXIT ')

class OutRFInfoPort(OutPort):
    def __init__(self, name, logger=None ):
        OutPort.__init__(self, name, FRONTEND.RFInfo, logger )

    def _get_rf_flow_id(self):
        if self.logger:
            self.logger.trace('frontend::OutRFInfoPort _get_rf_flow_id ENTER ')
        retVal = ""
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port._get_rf_flow_id()
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _get_rf_flow_id failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutRFInfoPort  _get_rf_flow_id EXIT ')

        return retVal

    def _set_rf_flow_id(self, data):
        if self.logger:
            self.logger.trace('frontend::OutRFInfoPort _set_rf_flow_id ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port._set_rf_flow_id(data)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _set_rf_flow_id failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutRFInfoPort  _set_rf_flow_id EXIT ')

    def _get_rfinfo_pkt(self):
        if self.logger:
            self.logger.trace('frontend::OutRFInfoPort _get_rfinfo_pkt ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port._get_rfinfo_pkt()
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _get_rfinfo_pkt failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutRFInfoPort  _get_rfinfo_pkt EXIT ')

        return retVal

    def _set_rfinfo_pkt(self, data):
        if self.logger:
            self.logger.trace('frontend::OutRFInfoPort _set_rfinfo_pkt ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port._set_rfinfo_pkt(data)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _set_rfinfo_pkt failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutRFInfoPort  _set_rfinfo_pkt EXIT ')

class OutRFSourcePort(OutPort):
    def __init__(self, name, logger=None ):
        OutPort.__init__(self, name, FRONTEND.RFSource, logger )

    def _get_available_rf_inputs(self):
        if self.logger:
            self.logger.trace('frontend::OutRFSourcePort _get_available_rf_inputs ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port._get_available_rf_inputs()
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _get_available_rf_inputs failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutRFSourcePort  _get_available_rf_inputs EXIT ')

        return retVal

    def _set_available_rf_inputs(self, data):
        if self.logger:
            self.logger.trace('frontend::OutRFSourcePort _set_available_rf_inputs ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port._set_available_rf_inputs(data)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _set_available_rf_inputs failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutRFSourcePort  _set_available_rf_inputs EXIT ')

    def _get_current_rf_input(self):
        if self.logger:
            self.logger.trace('frontend::OutRFSourcePort _get_current_rf_input ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port._get_current_rf_input()
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _get_current_rf_input failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutRFSourcePort  _get_current_rf_input EXIT ')

        return retVal

    def _set_current_rf_input(self, data):
        if self.logger:
            self.logger.trace('frontend::OutRFSourcePort _set_current_rf_input ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port._set_current_rf_input(data)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _set_current_rf_input failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutRFSourcePort  _set_current_rf_input EXIT ')

class OutNavDataPort(OutPort):
    def __init__(self, name, logger=None ):
        OutPort.__init__(self, name, FRONTEND.NavData, logger )

    def _get_nav_packet(self):
        if self.logger:
            self.logger.trace('frontend::OutNavDataPort _get_nav_packet ENTER ')
        retVal = None
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        retVal = port._get_nav_packet()
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _get_nav_packet failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutNavDataPort  _get_nav_packet EXIT ')

        return retVal

    def _set_nav_packet(self, data):
        if self.logger:
            self.logger.trace('frontend::OutNavDataPort _set_nav_packet ENTER ')
        self.port_lock.acquire()

        try:
            for connId, port in self.outConnections.items():
                if port != None:
                    try:
                        port._set_nav_packet(data)
                    except Exception:
                        if self.logger:
                            self.logger.exception("The call to _set_nav_packet failed on port %s connection %s instance %s", self.name, connId, port)
        finally:
            self.port_lock.release()
            
        if self.logger:
            self.logger.trace('frontend::OutNavDataPort  _set_nav_packet EXIT ')
            
            