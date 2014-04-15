#include "fe_tuner_device.h"
#include <exception>

namespace frontend {
    template < typename TunerStatusStructType >
    log4cxx::LoggerPtr FrontendTunerDevice<TunerStatusStructType>::__logger(log4cxx::Logger::getLogger("FrontendTunerDevice"));

    template < typename TunerStatusStructType >
    FrontendTunerDevice<TunerStatusStructType>::FrontendTunerDevice(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl) :
        Device_impl(devMgr_ior, id, lbl, sftwrPrfl)
    {
        construct();
    }

    template < typename TunerStatusStructType >
    FrontendTunerDevice<TunerStatusStructType>::FrontendTunerDevice(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev) :
        Device_impl(devMgr_ior, id, lbl, sftwrPrfl, compDev)
    {
        construct();
    }

    template < typename TunerStatusStructType >
    FrontendTunerDevice<TunerStatusStructType>::FrontendTunerDevice(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities) :
        Device_impl(devMgr_ior, id, lbl, sftwrPrfl, capacities)
    {
        construct();
    }

    template < typename TunerStatusStructType >
    FrontendTunerDevice<TunerStatusStructType>::FrontendTunerDevice(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev) :
        Device_impl(devMgr_ior, id, lbl, sftwrPrfl, capacities, compDev)
    {
        construct();
    }

    template < typename TunerStatusStructType >
    void FrontendTunerDevice<TunerStatusStructType>::construct()
    {
        Resource_impl::_started = false;
        loadProperties();
    }

    template < typename TunerStatusStructType >
    FrontendTunerDevice<TunerStatusStructType>::~FrontendTunerDevice()
    {
        tuner_allocation_ids.clear();
    }

    /*******************************************************************************************
        Framework-level functions
        These functions are generally called by the framework to perform housekeeping.
    *******************************************************************************************/

    template < typename TunerStatusStructType >
    void FrontendTunerDevice<TunerStatusStructType>::loadProperties()
    {
        addProperty(device_kind,
                    "FRONTEND::TUNER",
                    "DCE:cdc5ee18-7ceb-4ae6-bf4c-31f983179b4d",
                    "device_kind",
                    "readonly",
                    "",
                    "eq",
                    "allocation,configure");

        addProperty(device_model,
                    "",
                    "DCE:0f99b2e4-9903-4631-9846-ff349d18ecfb",
                    "device_model",
                    "readonly",
                    "",
                    "eq",
                    "allocation,configure");

        addProperty(frontend_tuner_allocation,
                    frontend::frontend_tuner_allocation_struct(),
                    "FRONTEND::tuner_allocation",
                    "frontend_tuner_allocation",
                    "readwrite",
                    "",
                    "external",
                    "allocation");

        addProperty(frontend_listener_allocation,
                    frontend::frontend_listener_allocation_struct(),
                    "FRONTEND::listener_allocation",
                    "frontend_listener_allocation",
                    "readwrite",
                    "",
                    "external",
                    "allocation");

        addProperty(frontend_tuner_status,
                    "FRONTEND::tuner_status",
                    "frontend_tuner_status",
                    "readonly",
                    "",
                    "external",
                    "configure");

    }

    template < typename TunerStatusStructType >
    std::string FrontendTunerDevice<TunerStatusStructType>::createAllocationIdCsv(size_t tuner_id){
        //LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__);
        std::string alloc_id_csv = "";
        // ensure control allocation_id is first in list
        if (!tuner_allocation_ids[tuner_id].control_allocation_id.empty())
            alloc_id_csv = tuner_allocation_ids[tuner_id].control_allocation_id + ",";
        std::vector<std::string>::iterator it = tuner_allocation_ids[tuner_id].listener_allocation_ids.begin();
        for(; it != tuner_allocation_ids[tuner_id].listener_allocation_ids.end(); it++)
            alloc_id_csv += *it + ",";
        if(!alloc_id_csv.empty())
            alloc_id_csv.erase(alloc_id_csv.size()-1);
        return alloc_id_csv;
    }

    template < typename TunerStatusStructType >
    std::string FrontendTunerDevice<TunerStatusStructType>::getControlAllocationId(size_t tuner_id){
    	return tuner_allocation_ids[tuner_id].control_allocation_id;
    }
    template < typename TunerStatusStructType >
    std::vector<std::string> FrontendTunerDevice<TunerStatusStructType>::getListenerAllocationIds(size_t tuner_id){
    	return tuner_allocation_ids[tuner_id].listener_allocation_ids;
    }

    /*****************************************************************/
    /* Allocation/Deallocation of Capacity                           */
    /*****************************************************************/
    template < typename TunerStatusStructType >
    CF::Device::UsageType FrontendTunerDevice<TunerStatusStructType>::updateUsageState() {
        //LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__);
        size_t tunerAllocated = 0;
        for (size_t tuner_id = 0; tuner_id < tuner_allocation_ids.size(); tuner_id++) {
            if (!tuner_allocation_ids[tuner_id].control_allocation_id.empty())
                tunerAllocated++;
        }
        // If no tuners are allocated, device is idle
        if (tunerAllocated == 0)
            return CF::Device::IDLE;
        // If all tuners are allocated, device is busy
        if (tunerAllocated == tuner_allocation_ids.size())
            return CF::Device::BUSY;
        // Else, device is active
        return CF::Device::ACTIVE;
    }

    template < typename TunerStatusStructType >
    CORBA::Boolean FrontendTunerDevice<TunerStatusStructType>::allocateCapacity(const CF::Properties & capacities)
    throw (CORBA::SystemException, CF::Device::InvalidCapacity, CF::Device::InvalidState) {
        //LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__);
        CORBA::ULong ii;
        try{
            for (ii = 0; ii < capacities.length(); ++ii) {
                const std::string id = (const char*) capacities[ii].id;
                if (id != "FRONTEND::tuner_allocation" && id != "FRONTEND::listener_allocation"){
                    LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>, "UNKNOWN ALLOCATION PROPERTY1");
                    throw CF::Device::InvalidCapacity("UNKNOWN ALLOCATION PROPERTY1", capacities);
                }
                PropertyInterface* property = getPropertyFromId(id);
                if(!property){
                    LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>, "UNKNOWN PROPERTY");
                    throw CF::Device::InvalidCapacity("UNKNOWN PROPERTY", capacities);
                }
                try{
                    property->setValue(capacities[ii].value);
                }
                catch(const std::logic_error &e){
                    LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>, "COULD NOT PARSE CAPACITY: " << e.what());
                    throw CF::Device::InvalidCapacity("COULD NOT PARSE CAPACITY", capacities);
                };
                if (id == "FRONTEND::tuner_allocation"){

                    // Check allocation_id
                    if (frontend_tuner_allocation.allocation_id.empty()) {
                        LOG_INFO(FrontendTunerDevice<TunerStatusStructType>,"allocateCapacity: MISSING ALLOCATION_ID");
                        throw CF::Device::InvalidCapacity("MISSING ALLOCATION_ID", capacities);
                    }
                    // Check if allocation ID has already been used
                    if(getTunerMapping(frontend_tuner_allocation.allocation_id) >= 0){
                        LOG_INFO(FrontendTunerDevice<TunerStatusStructType>,"allocateCapacity: ALLOCATION_ID ALREADY IN USE: [" << frontend_tuner_allocation.allocation_id << "]");
                        throw CF::Device::InvalidCapacity("ALLOCATION_ID ALREADY IN USE", capacities);
                    }

                    // Check if available tuner
                    exclusive_lock lock(allocation_id_mapping_lock);

                    // Next, try to allocate a new tuner
                    for (size_t tuner_id = 0; tuner_id < tuner_allocation_ids.size(); tuner_id++) {
                        if(frontend_tuner_status[tuner_id].tuner_type != frontend_tuner_allocation.tuner_type) {
                            continue;
                        }

                        if(!frontend_tuner_allocation.group_id.empty() && frontend_tuner_allocation.group_id != frontend_tuner_status[tuner_id].group_id ){
                            continue;
                        }

                        // special case because allocation is specifying the input stream, which determines the rf_flow_id, etc.
                        if(!frontend_tuner_allocation.rf_flow_id.empty()
                            && frontend_tuner_allocation.rf_flow_id != frontend_tuner_status[tuner_id].rf_flow_id
                            && frontend_tuner_allocation.tuner_type != "CHANNELIZER"){
                            continue;
                        }

                        if(frontend_tuner_allocation.device_control){
                            // device control
                            if(!tuner_allocation_ids[tuner_id].control_allocation_id.empty() || !deviceSetTuning(frontend_tuner_allocation, frontend_tuner_status[tuner_id], tuner_id)){
                                // either not available or didn't succeed setting tuning, try next tuner
                                continue;
                            }
                            tuner_allocation_ids[tuner_id].control_allocation_id = frontend_tuner_allocation.allocation_id;
                            allocation_id_to_tuner_id.insert(std::pair<std::string, size_t > (frontend_tuner_allocation.allocation_id, tuner_id));
                            frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id);
                        } else {
                            // channelizer allocations must specify device control = true
                            if(frontend_tuner_allocation.tuner_type == "CHANNELIZER" || frontend_tuner_allocation.tuner_type == "TX"){
                                std::ostringstream eout;
                                eout<<frontend_tuner_allocation.tuner_type<<" allocation with device_control=false is invalid.";
                                LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>, eout.str());
                                throw CF::Device::InvalidCapacity(eout.str().c_str(), capacities);
                            }
                            // listener
                            if(tuner_allocation_ids[tuner_id].control_allocation_id.empty() || !listenerRequestValidation(frontend_tuner_allocation, tuner_id)){
                                // either not allocated or can't support listener request
                                continue;
                            }
                            tuner_allocation_ids[tuner_id].listener_allocation_ids.push_back(frontend_tuner_allocation.allocation_id);
                            allocation_id_to_tuner_id.insert(std::pair<std::string, size_t > (frontend_tuner_allocation.allocation_id, tuner_id));
                            frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id);
                            this->assignListener(frontend_tuner_allocation.allocation_id,tuner_allocation_ids[tuner_id].control_allocation_id);
                        }
                        // if we've reached here, we found an eligible tuner with correct frequency

                        // check tolerances
                        // only check when sample_rate was not set to don't care)
                        if( (frontend_tuner_allocation.sample_rate != 0.0) &&
                            (frontend_tuner_status[tuner_id].sample_rate < frontend_tuner_allocation.sample_rate ||
                            frontend_tuner_status[tuner_id].sample_rate > frontend_tuner_allocation.sample_rate+frontend_tuner_allocation.sample_rate * frontend_tuner_allocation.sample_rate_tolerance/100.0 )){
                            std::ostringstream eout;
                            eout<<"allocateCapacity("<<int(tuner_id)<<"): returned bw "<<frontend_tuner_status[tuner_id].sample_rate<<" does not meet tolerance criteria of "<<frontend_tuner_allocation.sample_rate_tolerance<<" percent";
                            LOG_INFO(FrontendTunerDevice<TunerStatusStructType>, eout.str());
                            throw std::logic_error(eout.str().c_str());
                        }
                        // Only check when bandwidth was not set to don't care
                        if( (frontend_tuner_allocation.bandwidth != 0.0) &&
                            (frontend_tuner_status[tuner_id].bandwidth < frontend_tuner_allocation.bandwidth ||
                            frontend_tuner_status[tuner_id].bandwidth > frontend_tuner_allocation.bandwidth+frontend_tuner_allocation.bandwidth * frontend_tuner_allocation.bandwidth_tolerance/100.0 )){
                            std::ostringstream eout;
                            eout<<"allocateCapacity("<<int(tuner_id)<<"): returned bw "<<frontend_tuner_status[tuner_id].bandwidth<<" does not meet tolerance criteria of "<<frontend_tuner_allocation.bandwidth_tolerance<<" percent";
                            LOG_INFO(FrontendTunerDevice<TunerStatusStructType>, eout.str());
                            throw std::logic_error(eout.str().c_str());
                        }

                        if(frontend_tuner_allocation.device_control){
                            // enable tuner after successful allocation
                            try {
                                enableTuner(tuner_id,true);
                            } catch(...){
                                std::ostringstream eout;
                                eout<<"allocateCapacity: Failed to enable tuner after allocation";
                                LOG_INFO(FrontendTunerDevice<TunerStatusStructType>, eout.str());
                                throw std::logic_error(eout.str().c_str());
                            }
                        }
                        return true;
                    }
                    // if we made it here, we failed to find an available tuner
                    std::ostringstream eout;
                    eout<<"allocateCapacity: NO AVAILABLE TUNER. Make sure that the device has an initialized frontend_tuner_status";
                    LOG_INFO(FrontendTunerDevice<TunerStatusStructType>, eout.str());
                    throw std::logic_error(eout.str().c_str());
                    
                } else if (id == "FRONTEND::listener_allocation") {
                    // Check validity of allocation_id's
                    if (frontend_listener_allocation.existing_allocation_id.empty()){
                        LOG_INFO(FrontendTunerDevice<TunerStatusStructType>,"allocateCapacity: MISSING EXISTING ALLOCATION ID");
                        throw CF::Device::InvalidCapacity("MISSING EXISTING ALLOCATION ID", capacities);
                    }
                    if (frontend_listener_allocation.listener_allocation_id.empty()){
                        LOG_INFO(FrontendTunerDevice<TunerStatusStructType>,"allocateCapacity: MISSING LISTENER ALLOCATION ID");
                        throw CF::Device::InvalidCapacity("MISSING LISTENER ALLOCATION ID", capacities);
                    }

                    exclusive_lock lock(allocation_id_mapping_lock);

                    // Check if listener allocation ID has already been used
                    if(getTunerMapping(frontend_listener_allocation.listener_allocation_id) >= 0){
                        LOG_INFO(FrontendTunerDevice<TunerStatusStructType>,"allocateCapacity: LISTENER ALLOCATION ID ALREADY IN USE: [" << frontend_listener_allocation.listener_allocation_id << "]");
                        throw CF::Device::InvalidCapacity("LISTENER ALLOCATION ID ALREADY IN USE", capacities);
                    }
                    // Do not allocate if existing allocation ID does not exist
                    long tuner_id = getTunerMapping(frontend_listener_allocation.existing_allocation_id);
                    if (tuner_id < 0){
                        LOG_INFO(FrontendTunerDevice<TunerStatusStructType>,"allocateCapacity: UNKNOWN CONTROL ALLOCATION ID: ["<< frontend_listener_allocation.existing_allocation_id <<"]");
                        throw FRONTEND::BadParameterException("UNKNOWN CONTROL ALLOCATION ID");
                    }

                    // listener allocations are not permitted for channelizers or TX
                    if(frontend_tuner_status[tuner_id].tuner_type == "CHANNELIZER" || frontend_tuner_status[tuner_id].tuner_type == "TX"){
                        std::ostringstream eout;
                        eout<<"allocateCapacity: listener allocations are not permitted for " << std::string(frontend_tuner_status[tuner_id].tuner_type) << " tuner type";
                        LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>, eout.str());
                        throw CF::Device::InvalidCapacity(eout.str().c_str(), capacities);
                    }

                    tuner_allocation_ids[tuner_id].listener_allocation_ids.push_back(frontend_listener_allocation.listener_allocation_id);
                    allocation_id_to_tuner_id.insert(std::pair<std::string, size_t > (frontend_listener_allocation.listener_allocation_id, tuner_id));
                    frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id);
                    this->assignListener(frontend_listener_allocation.listener_allocation_id,frontend_listener_allocation.existing_allocation_id);
                    return true;
                }
                else {
                    LOG_INFO(FrontendTunerDevice<TunerStatusStructType>,"allocateCapacity: UNKNOWN ALLOCATION PROPERTY2");
                    throw CF::Device::InvalidCapacity("UNKNOWN ALLOCATION PROPERTY2", capacities);
                }
            }
        }
        catch(const std::logic_error &e) {
            deallocateCapacity(capacities);
            return false;
        }
        catch(CF::Device::InvalidCapacity &e) {
            // without the following check, a valid allocation could be deallocated due to an attempt to alloc w/ an existing alloc id
            std::stringstream ss;
            ss << e.msg;
            if (ss.str() != "ALLOCATION_ID ALREADY IN USE") {
                deallocateCapacity(capacities);
            }
            //else {
            //}
            throw e;
        }
        catch(FRONTEND::BadParameterException &e) {
            deallocateCapacity(capacities);
            return false;
        }
        catch(...){
            deallocateCapacity(capacities);
            throw;
        };
        
        return true;
    }

    template < typename TunerStatusStructType >
    void FrontendTunerDevice<TunerStatusStructType>::deallocateCapacity(const CF::Properties & capacities)
    throw (CORBA::SystemException, CF::Device::InvalidCapacity, CF::Device::InvalidState) {
        LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__);
        for (CORBA::ULong ii = 0; ii < capacities.length(); ++ii) {
            try{
                const std::string id = (const char*) capacities[ii].id;
                if (id != "FRONTEND::tuner_allocation" && id != "FRONTEND::listener_allocation"){
                    LOG_INFO(FrontendTunerDevice<TunerStatusStructType>,"deallocateCapacity: UNKNOWN ALLOCATION PROPERTY");
                    throw CF::Device::InvalidCapacity("UNKNOWN ALLOCATION PROPERTY", capacities);
                }
                PropertyInterface* property = getPropertyFromId(id);
                if(!property){
                    LOG_INFO(FrontendTunerDevice<TunerStatusStructType>,"deallocateCapacity: UNKNOWN PROPERTY");
                    throw CF::Device::InvalidCapacity("UNKNOWN PROPERTY", capacities);
                }
                try{
                    property->setValue(capacities[ii].value);
                }
                catch(const std::logic_error &e){
                    LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>, "COULD NOT PARSE CAPACITY: " << e.what());
                    throw CF::Device::InvalidCapacity("COULD NOT PARSE CAPACITY", capacities);
                };
                if (id == "FRONTEND::tuner_allocation"){
                    //LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>,std::string(__PRETTY_FUNCTION__)+" tuner_allocation");
                    // Try to remove control of the device
                    long tuner_id = getTunerMapping(frontend_tuner_allocation.allocation_id);
                    if (tuner_id < 0){
                        LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>, "ALLOCATION_ID NOT FOUND: [" << frontend_tuner_allocation.allocation_id <<"]");
                        throw CF::Device::InvalidCapacity("ALLOCATION_ID NOT FOUND", capacities);
                    }
                    //LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>,std::string(__PRETTY_FUNCTION__)+" tuner_id = " << tuner_id);
                    if(tuner_allocation_ids[tuner_id].control_allocation_id == frontend_tuner_allocation.allocation_id){
                        //LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>,std::string(__PRETTY_FUNCTION__)+" deallocating control for tuner_id = " << tuner_id);
                        enableTuner(tuner_id, false);
                        removeTunerMapping(tuner_id);
                        frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id);
                    }
                    else {
                        //LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>,std::string(__PRETTY_FUNCTION__)+" deallocating listener for tuner_id = " << tuner_id);
                        // send EOS to listener connection only
                        removeTunerMapping(tuner_id,frontend_tuner_allocation.allocation_id);
                        frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id);
                    }
                }
                else if (id == "FRONTEND::listener_allocation") {
                    //LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>,std::string(__PRETTY_FUNCTION__)+" listener_allocation");
                    long tuner_id = getTunerMapping(frontend_listener_allocation.listener_allocation_id);
                    if (tuner_id < 0){
                        LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>, "ALLOCATION_ID NOT FOUND: [" << frontend_listener_allocation.listener_allocation_id <<"]");
                        throw CF::Device::InvalidCapacity("ALLOCATION_ID NOT FOUND", capacities);
                    }
                    //LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>,std::string(__PRETTY_FUNCTION__)+" tuner_id = " << tuner_id);
                    // send EOS to listener connection only
                    removeTunerMapping(tuner_id,frontend_listener_allocation.listener_allocation_id);
                    frontend_tuner_status[tuner_id].allocation_id_csv = createAllocationIdCsv(tuner_id);
                }
                else {
                    LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,"WARNING: UNKNOWN ALLOCATION PROPERTY \""+ std::string(property->name) + "\". IGNORING!");
                }
            }
            catch(...){
                LOG_DEBUG(FrontendTunerDevice<TunerStatusStructType>,"ERROR WHEN DEALLOCATING. SKIPPING...");
            }
        }
    }

    /*****************************************************************/
    /* Tuner Configurations                                          */
    /*****************************************************************/

    template < typename TunerStatusStructType >
    bool FrontendTunerDevice<TunerStatusStructType>::enableTuner(size_t tuner_id, bool enable) {
        //LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__);
        
        bool prev_enabled = frontend_tuner_status[tuner_id].enabled;
        
        // If going from disabled to enabled
        if (!prev_enabled && enable) {
            deviceEnable(frontend_tuner_status[tuner_id], tuner_id);
        }
        
        // If going from enabled to disabled
        if (prev_enabled && !enable) {

            deviceDisable(frontend_tuner_status[tuner_id], tuner_id);
        }

        return true;
    }

    template < typename TunerStatusStructType >
    bool FrontendTunerDevice<TunerStatusStructType>::listenerRequestValidation(frontend_tuner_allocation_struct &request, size_t tuner_id){
        LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__);

        // ensure requested values are non-negative
        if(request.center_frequency < 0 || request.bandwidth < 0 || request.sample_rate < 0 || request.bandwidth_tolerance < 0 || request.sample_rate_tolerance < 0)
        	return false;

    	// ensure lower end of requested band fits
    	//if((request.center_frequency - (request.bandwidth*0.5)) < (frontend_tuner_status[tuner_id].center_frequency - (frontend_tuner_status[tuner_id].bandwidth*0.5))){
        if( compareHz((request.center_frequency-(request.bandwidth*0.5)),(frontend_tuner_status[tuner_id].center_frequency-(frontend_tuner_status[tuner_id].bandwidth*0.5))) < 0 ){
    		LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__ << " FAILED LOWER END TEST");
    		return false;
    	}

    	// ensure upper end of requested band fits
    	//if((request.center_frequency + (request.bandwidth*0.5)) > (frontend_tuner_status[tuner_id].center_frequency + (frontend_tuner_status[tuner_id].bandwidth*0.5))){
    	if( compareHz((request.center_frequency + (request.bandwidth*0.5)),(frontend_tuner_status[tuner_id].center_frequency + (frontend_tuner_status[tuner_id].bandwidth*0.5))) > 0 ){
    		LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__ << " FAILED UPPER END TEST");
    		return false;
    	}

    	// ensure tuner bandwidth meets requested tolerance
    	//if(request.bandwidth > frontend_tuner_status[tuner_id].bandwidth)
    	if( compareHz(request.bandwidth,frontend_tuner_status[tuner_id].bandwidth) > 0 )
    		return false;

    	//if(request.bandwidth != 0 && (request.bandwidth+(request.bandwidth*request.bandwidth_tolerance/100)) < frontend_tuner_status[tuner_id].bandwidth)
        if( request.bandwidth != 0 && compareHz((request.bandwidth+(request.bandwidth*request.bandwidth_tolerance/100)),frontend_tuner_status[tuner_id].bandwidth) < 0 )
    		return false;

    	// ensure tuner sample rate meets requested tolerance
    	//if(request.sample_rate > frontend_tuner_status[tuner_id].sample_rate)
    	if( compareHz(request.sample_rate,frontend_tuner_status[tuner_id].sample_rate) > 0 )
    		return false;

    	//if(request.sample_rate != 0 && (request.sample_rate+(request.sample_rate*request.sample_rate_tolerance/100)) < frontend_tuner_status[tuner_id].sample_rate)
    	if(request.sample_rate != 0 && compareHz((request.sample_rate+(request.sample_rate*request.sample_rate_tolerance/100)),frontend_tuner_status[tuner_id].sample_rate) < 0 )
    		return false;

    	return true;
    };

    ////////////////////////////
    //        MAPPING         //
    ////////////////////////////

    template < typename TunerStatusStructType >
    long FrontendTunerDevice<TunerStatusStructType>::getTunerMapping(std::string allocation_id) {
        //LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__);
        long NO_VALID_TUNER = -1;

        string_number_mapping::iterator iter = allocation_id_to_tuner_id.find(allocation_id);
        if (iter != allocation_id_to_tuner_id.end())
            return iter->second;

        return NO_VALID_TUNER;
    }


    template < typename TunerStatusStructType >
    bool FrontendTunerDevice<TunerStatusStructType>::removeTunerMapping(size_t tuner_id, std::string allocation_id) {
        LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__);
        removeListener(allocation_id);
        std::vector<std::string>::iterator it = tuner_allocation_ids[tuner_id].listener_allocation_ids.begin();
        while(it != tuner_allocation_ids[tuner_id].listener_allocation_ids.end()){
            if(*it == allocation_id){
                tuner_allocation_ids[tuner_id].listener_allocation_ids.erase(it);
            } else {
                ++it;
            }
        }
        exclusive_lock lock(allocation_id_mapping_lock);
        if(allocation_id_to_tuner_id.erase(allocation_id) > 0)
            return true;
        return false;
    }

    template < typename TunerStatusStructType >
    bool FrontendTunerDevice<TunerStatusStructType>::removeTunerMapping(size_t tuner_id) {
        LOG_TRACE(FrontendTunerDevice<TunerStatusStructType>,__PRETTY_FUNCTION__);
        deviceDeleteTuning(frontend_tuner_status[tuner_id], tuner_id);
        removeAllocationIdRouting(tuner_id);

        long cnt = 0;
        exclusive_lock lock(allocation_id_mapping_lock);
        string_number_mapping::iterator it = allocation_id_to_tuner_id.begin();
        while(it != allocation_id_to_tuner_id.end()){
            if(it->second == tuner_id){
                std::string allocation_id = it->first;
                removeListener(allocation_id);
                allocation_id_to_tuner_id.erase(it++);
                cnt++;
            } else {
                ++it;
            }
        }
        /*
        for(std::vector<std::string>::iterator it = tuner_allocation_ids[tuner_id].listener_allocation_ids.begin(); it != tuner_allocation_ids[tuner_id].listener_allocation_ids.end();it++){
            removeListener(*it);
            allocation_id_to_tuner_id.erase(*it);
            cnt++;
        }
        removeListener(tuner_allocation_ids[tuner_id].control_allocation_id);
        allocation_id_to_tuner_id.erase(tuner_allocation_ids[tuner_id].control_allocation_id);
        */
        tuner_allocation_ids[tuner_id].reset();
        return cnt > 0;
    }

    template < typename TunerStatusStructType >
    void FrontendTunerDevice<TunerStatusStructType>::assignListener(const std::string& listen_alloc_id, const std::string& alloc_id) {
    };

    template < typename TunerStatusStructType >
    void FrontendTunerDevice<TunerStatusStructType>::removeListener(const std::string& listen_alloc_id) {
    };

}; // end frontend namespace
