#include "fe_tuner_impl.h"

namespace frontend {

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
		for (size_t tuner_id = 0; tuner_id < tunerChannels.size(); tuner_id++) {
			if (tunerChannels[tuner_id].lock != NULL)
				delete tunerChannels[tuner_id].lock;
		}
		tunerChannels.clear();
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
                    "USRP",
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
	std::string FrontendTunerDevice<TunerStatusStructType>::create_allocation_id_csv(size_t tuner_id){
		std::string alloc_id_csv = "";
		// ensure control allocation_id is first in list
		if (!tunerChannels[tuner_id].control_allocation_id.empty())
			alloc_id_csv = tunerChannels[tuner_id].control_allocation_id + ",";
		// now add the rest
		for(string_number_mapping::iterator it = allocationID_to_tunerID.begin(); it != allocationID_to_tunerID.end(); it++){
			if(it->second == tuner_id && it->first != tunerChannels[tuner_id].control_allocation_id)
				alloc_id_csv += it->first + ",";
		}
		// and get rid of the trailing comma
		if(!alloc_id_csv.empty())
			alloc_id_csv.erase(alloc_id_csv.size()-1);
		return alloc_id_csv;
	}

	/*****************************************************************/
	/* Allocation/Deallocation of Capacity                           */
	/*****************************************************************/
	template < typename TunerStatusStructType >
	CF::Device::UsageType FrontendTunerDevice<TunerStatusStructType>::updateUsageState() {
		size_t tunerAllocated = 0;
		for (size_t tuner_id = 0; tuner_id < tunerChannels.size(); tuner_id++) {
			if (!tunerChannels[tuner_id].control_allocation_id.empty())
				tunerAllocated++;
		}
		// If no tuners are allocated, device is idle
		if (tunerAllocated == 0)
			return CF::Device::IDLE;
		// If all tuners are allocated, device is busy
		if (tunerAllocated == tunerChannels.size())
			return CF::Device::BUSY;
		// Else, device is active
		return CF::Device::ACTIVE;
	}

	template < typename TunerStatusStructType >
	CORBA::Boolean FrontendTunerDevice<TunerStatusStructType>::allocateCapacity(const CF::Properties & capacities)
	throw (CORBA::SystemException, CF::Device::InvalidCapacity, CF::Device::InvalidState) {
		CORBA::ULong ii;
		try{
			for (ii = 0; ii < capacities.length(); ++ii) {
				const std::string id = (const char*) capacities[ii].id;
				if (id != "FRONTEND::tuner_allocation" && id != "FRONTEND::listener_allocation"){
					//TODO: add back log messages
					std::cout<<"allocateCapacity: UNKNOWN ALLOCATION PROPERTY1: "<<id<<std::endl;
					throw CF::Device::InvalidCapacity("UNKNOWN ALLOCATION PROPERTY1", capacities);
				}
				PropertyInterface* property = getPropertyFromId(id);
				if(!property){
					//TODO: add back log messages
					std::cout<<"allocateCapacity: UNKNOWN PROPERTY"<<std::endl;
					throw CF::Device::InvalidCapacity("UNKNOWN PROPERTY", capacities);
				}
				try{
					property->setValue(capacities[ii].value);
				}
				catch(const std::logic_error &e){
					//TODO: add back log messages
					std::cout<<"allocateCapacity: COULD NOT PARSE CAPACITY"<<std::endl;
					throw CF::Device::InvalidCapacity("COULD NOT PARSE CAPACITY", capacities);
				};
				if (id == "FRONTEND::tuner_allocation"){

					if(!_valid_tuner_type(frontend_tuner_allocation.tuner_type)){
						//TODO: add back log messages
						std::cout<<"allocateCapacity: UNKNOWN FRONTEND TUNER TYPE"<<std::endl;
						throw CF::Device::InvalidCapacity("UNKNOWN FRONTEND TUNER TYPE", capacities);
					}

					// Check allocation_id
					if (frontend_tuner_allocation.allocation_id.empty()) {
						//TODO: add back log messages
						std::cout<<"allocateCapacity: MISSING ALLOCATION_ID"<<std::endl;
						throw CF::Device::InvalidCapacity("MISSING ALLOCATION_ID", capacities);
					}
					// Check if allocation ID has already been used
					if(getTunerMapping(frontend_tuner_allocation.allocation_id) >= 0){
						//TODO: add back log messages
						std::cout<<"allocateCapacity: ALLOCATION_ID ALREADY IN USE"<<std::endl;
						throw CF::Device::InvalidCapacity("ALLOCATION_ID ALREADY IN USE", capacities);
					}

					// Check if available tuner (if not requesting device control, this is all that's needed to add listener)
					long tuner_id = addTunerMapping(frontend_tuner_allocation);
					if (tuner_id < 0) {
						char msg[512];
						sprintf(msg,"NO AVAILABLE TUNER");
						//TODO: add back log messages
						std::cout<<"allocateCapacity: NO AVAILABLE TUNER"<<std::endl;
						throw std::logic_error(msg);
					}

					// Initialize the tuner (only if requesting device control)
					if (frontend_tuner_allocation.device_control){

						{
							exclusive_lock lock(* (tunerChannels[tuner_id].lock));
							if(!frontend_tuner_allocation.group_id.empty() && frontend_tuner_allocation.group_id != tunerChannels[tuner_id].frontend_status->group_id ){
								//TODO: add back log messages
								std::cout<<"allocateCapacity: CANNOT ALLOCATE A TUNER WITH THAT GROUP ID"<<std::endl;
								throw FRONTEND::BadParameterException("CAN NOT ALLOCATE A TUNER WITH THAT GROUP ID!");
							}

							if(!frontend_tuner_allocation.rf_flow_id.empty() && frontend_tuner_allocation.rf_flow_id != tunerChannels[tuner_id].frontend_status->rf_flow_id ){
								//TODO: add back log messages
								std::cout<<"allocateCapacity: CANNOT ALLOCATE A TUNER WITH THAT RF FLOW ID"<<std::endl;
								throw FRONTEND::BadParameterException(("CAN NOT ALLOCATE A TUNER WITH RF FLOW ID = " + frontend_tuner_allocation.rf_flow_id + " !").c_str());
							}

							//Check Validity
							if (!_valid_center_frequency(frontend_tuner_allocation.center_frequency,tuner_id)){
								//TODO: add back log messages
								std::cout<<"allocateCapacity: INVALID FREQUENCY"<<std::endl;
								throw FRONTEND::BadParameterException("allocateCapacity(): INVALID FREQUENCY");
							}
							if (!_valid_bandwidth(frontend_tuner_allocation.bandwidth,tuner_id)){
								//TODO: add back log messages
								std::cout<<"allocateCapacity: INVALID BANDWIDTH"<<std::endl;
								throw FRONTEND::BadParameterException("allocateCapacity(): INVALID BANDWIDTH");
							}
							if (!_valid_sample_rate(frontend_tuner_allocation.sample_rate,tuner_id)){
								//TODO: add back log messages
								std::cout<<"allocateCapacity: INVALID RATE"<<std::endl;
								throw FRONTEND::BadParameterException("allocateCapacity(): INVALID RATE");
							}

							try {
								_dev_set_all(frontend_tuner_allocation.center_frequency,
											 frontend_tuner_allocation.bandwidth,
											 frontend_tuner_allocation.sample_rate,
											 tuner_id);
								//_dev_set_center_frequency(frontend_tuner_allocation.center_frequency,tuner_id);
								//_dev_set_bandwidth(frontend_tuner_allocation.bandwidth,tuner_id);
								//_dev_set_sample_rate(frontend_tuner_allocation.sample_rate,tuner_id);
							}
							catch(...){
								char msg[512];
								sprintf(msg,"allocateCapacity(%d): failed when configuring device hardware",int(tuner_id));
								//TODO: add back log messages
								std::cout<<"allocateCapacity: failed when configuring device hardware"<<std::endl;
								throw std::logic_error(msg);
							};

							try {
								_dev_get_all(tunerChannels[tuner_id].frontend_status->center_frequency,
											 tunerChannels[tuner_id].frontend_status->bandwidth,
											 tunerChannels[tuner_id].frontend_status->sample_rate,
											 tuner_id);
								//tunerChannels[tuner_id].frontend_status->center_frequency = _dev_get_center_frequency(tuner_id);
								//tunerChannels[tuner_id].frontend_status->bandwidth = _dev_get_bandwidth(tuner_id);
								//tunerChannels[tuner_id].frontend_status->sample_rate = _dev_get_sample_rate(tuner_id);
							}
							catch(...){
								char msg[512];
								sprintf(msg,"allocateCapacity(%d): failed when querying device hardware",int(tuner_id));
								//TODO: add back log messages
								std::cout<<"allocateCapacity: failed when querying device hardware"<<std::endl;
								throw std::logic_error(msg);
							};

							// Only check non-TX when bandwidth was not set to don't care
							if( (tunerChannels[tuner_id].frontend_status->tuner_type != "TX" && frontend_tuner_allocation.bandwidth != 0.0) &&
								(tunerChannels[tuner_id].frontend_status->bandwidth < frontend_tuner_allocation.bandwidth ||
								tunerChannels[tuner_id].frontend_status->bandwidth > frontend_tuner_allocation.bandwidth+frontend_tuner_allocation.bandwidth * frontend_tuner_allocation.bandwidth_tolerance/100.0 )){
								char msg[512];
								sprintf(msg,"allocateCapacity(%d): returned bw \"%f\" does not meet tolerance criteria of \"%f + %f percent\". ",int(tuner_id),
										tunerChannels[tuner_id].frontend_status->bandwidth,frontend_tuner_allocation.bandwidth,frontend_tuner_allocation.bandwidth_tolerance);
								//TODO: add back log messages
								std::cout<<"allocateCapacity: did not meet BW tolerance"<<std::endl;
								throw std::logic_error(msg);
							}
							// always check TX, but only check non-TX when sample_rate was not set to don't care)
							if( (tunerChannels[tuner_id].frontend_status->tuner_type == "TX" || frontend_tuner_allocation.sample_rate != 0.0) &&
								(tunerChannels[tuner_id].frontend_status->sample_rate < frontend_tuner_allocation.sample_rate ||
								tunerChannels[tuner_id].frontend_status->sample_rate > frontend_tuner_allocation.sample_rate+frontend_tuner_allocation.sample_rate * frontend_tuner_allocation.sample_rate_tolerance/100.0 )){
								char msg[512];
								sprintf(msg,"allocateCapacity(%d): returned sample rate \"%f\" does not meet tolerance criteria of \"%f + %f percent\". ",int(tuner_id),
										tunerChannels[tuner_id].frontend_status->sample_rate,frontend_tuner_allocation.sample_rate,frontend_tuner_allocation.sample_rate_tolerance);
								//TODO: add back log messages
								std::cout<<"allocateCapacity: did not meet sample rate tolerance"<<std::endl;
								throw std::logic_error(msg);
							}
						} // release tuner lock

						// enable tuner after successful allocation
						try {
							enableTuner(tuner_id,true);
						} catch(...){
							char msg[512];
							sprintf(msg,"FAILED TO ENABLE TUNER AFTER ALLOCATION");
							//TODO: add back log messages
							std::cout<<"allocateCapacity: FAILED TO ENABLE TUNER AFTER ALLOCATION"<<std::endl;
							throw std::logic_error(msg);
						}
					}
				}
				else if (id == "FRONTEND::listener_allocation") {
					// Check validity of allocation_id's
					if (frontend_listener_allocation.existing_allocation_id.empty()){
						//TODO: add back log messages
						std::cout<<"allocateCapacity: MISSING EXISTING ALLOCATION ID"<<std::endl;
						throw CF::Device::InvalidCapacity("MISSING EXISTING ALLOCATION ID", capacities);
					}
					if (frontend_listener_allocation.listener_allocation_id.empty()){
						//TODO: add back log messages
						std::cout<<"allocateCapacity: MISSING LISTENER ALLOCATION ID"<<std::endl;
						throw CF::Device::InvalidCapacity("MISSING LISTENER ALLOCATION ID", capacities);
					}
					// Check if listener allocation ID has already been used
					if(getTunerMapping(frontend_listener_allocation.listener_allocation_id) >= 0){
						//TODO: add back log messages
						std::cout<<"allocateCapacity: LISTENER ALLOCATION ID ALREADY IN USE"<<std::endl;
						throw CF::Device::InvalidCapacity("LISTENER ALLOCATION ID ALREADY IN USE", capacities);
					}

					if(addTunerMapping(frontend_listener_allocation) < 0){
						//TODO: add back log messages
						std::cout<<"allocateCapacity: UNKNOWN CONTROL ALLOCATION ID"<<std::endl;
						throw FRONTEND::BadParameterException("UNKNOWN CONTROL ALLOCATION ID");
					}
				}
				else {
					//TODO: add back log messages
					std::cout<<"allocateCapacity: UNKNOWN ALLOCATION PROPERTY2"<<std::endl;
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
		for (CORBA::ULong ii = 0; ii < capacities.length(); ++ii) {
			try{
				const std::string id = (const char*) capacities[ii].id;
				if (id != "FRONTEND::tuner_allocation" && id != "FRONTEND::listener_allocation")
					throw CF::Device::InvalidCapacity("UNKNOWN ALLOCATION PROPERTY", capacities);
				PropertyInterface* property = getPropertyFromId(id);
				if(!property)
					throw CF::Device::InvalidCapacity("UNKNOWN PROPERTY", capacities);
				property->setValue(capacities[ii].value);
				if (id == "FRONTEND::tuner_allocation"){
					// Try to remove control of the device
					long tuner_id = getTunerMapping(frontend_tuner_allocation.allocation_id);
					if (tuner_id < 0)
						throw CF::Device::InvalidState();
					if(tunerChannels[tuner_id].control_allocation_id == frontend_tuner_allocation.allocation_id){
						removeTuner(tuner_id);
						removeTunerMapping(tuner_id);
					}
					else {
						// send EOS to listener connection only
						push_EOS_on_listener(frontend_tuner_allocation.allocation_id);
						removeTunerMapping(frontend_tuner_allocation.allocation_id);
					}
					tunerChannels[tuner_id].frontend_status->allocation_id_csv = create_allocation_id_csv(tuner_id);
				}
				else if (id == "FRONTEND::listener_allocation") {
					long tuner_id = getTunerMapping(frontend_listener_allocation.listener_allocation_id);
					if (tuner_id < 0)
						throw CF::Device::InvalidState();
					// send EOS to listener connection only
					push_EOS_on_listener(frontend_listener_allocation.listener_allocation_id);
					removeTunerMapping(frontend_listener_allocation.listener_allocation_id);
					tunerChannels[tuner_id].frontend_status->allocation_id_csv = create_allocation_id_csv(tuner_id);
				}
				else {
					//LOG_TRACE(USRP_UHD_i,"WARNING: UNKNOWN ALLOCATION PROPERTY \""+ std::string(property->name) + "\". IGNORING!");
				}
			}
			catch(...){
				//LOG_DEBUG(USRP_UHD_i,"ERROR WHEN DEALLOCATING. SKIPPING...");
			}
		}
	}

	/*****************************************************************/
	/* Tuner Configurations                                          */
	/*****************************************************************/

	template < typename TunerStatusStructType >
	bool FrontendTunerDevice<TunerStatusStructType>::removeTuner(size_t tuner_id) {
		enableTuner(tuner_id, false);
		tunerChannels[tuner_id].reset();
		return true;
	}

	template < typename TunerStatusStructType >
	bool FrontendTunerDevice<TunerStatusStructType>::enableTuner(size_t tuner_id, bool enable) {
		// Lock the tuner
		exclusive_lock lock(*(tunerChannels[tuner_id].lock));

		bool prev_enabled = tunerChannels[tuner_id].frontend_status->enabled;
		tunerChannels[tuner_id].frontend_status->enabled = enable;

		// If going from disabled to enabled
		if (!prev_enabled && enable) {
			configureTunerSRI(& tunerChannels[tuner_id].sri,
					tunerChannels[tuner_id].frontend_status->center_frequency,
					tunerChannels[tuner_id].frontend_status->bandwidth,
					tunerChannels[tuner_id].frontend_status->sample_rate,
					tunerChannels[tuner_id].complex,
					tunerChannels[tuner_id].frontend_status->rf_flow_id);
			streamID_to_tunerID.insert(std::make_pair(std::string(tunerChannels[tuner_id].sri.streamID), tuner_id));
			_dev_enable(tuner_id);
		}

		// If going from enabled to disabled
		if (prev_enabled && !enable && !std::string(tunerChannels[tuner_id].sri.streamID).empty()) {

			_dev_disable(tuner_id);
			std::string streamID = std::string(tunerChannels[tuner_id].sri.streamID);
			streamID_to_tunerID.erase(streamID);
			BIO_HELPER::zeroSRI(& tunerChannels[tuner_id].sri);
		}

		return true;
	}

	////////////////////////////
	//        MAPPING         //
	////////////////////////////

	template < typename TunerStatusStructType >
	long FrontendTunerDevice<TunerStatusStructType>::addTunerMapping(const frontend::frontend_tuner_allocation_struct & frontend_alloc) {
		long NO_VALID_TUNER = -1;
		exclusive_lock lock(allocationID_MappingLock);

		// Do not allocate if allocation ID has already been used
		if(getTunerMapping(frontend_alloc.allocation_id) >= 0)
			return NO_VALID_TUNER;

		// Next, try to allocate a new tuner
		for (long tuner_id = 0; tuner_id < long(tunerChannels.size()); tuner_id++) {
			if(tunerChannels[tuner_id].frontend_status->tuner_type != frontend_alloc.tuner_type)
				continue;
			//listen
			if (!frontend_alloc.device_control && !tunerChannels[tuner_id].control_allocation_id.empty()){
				bool freq_valid = is_freq_valid(
						frontend_alloc.center_frequency,
						frontend_alloc.bandwidth,
						frontend_alloc.sample_rate,
						tunerChannels[tuner_id].frontend_status->center_frequency,
						tunerChannels[tuner_id].frontend_status->bandwidth,
						tunerChannels[tuner_id].frontend_status->sample_rate);
				if (freq_valid){
					allocationID_to_tunerID.insert(std::pair<std::string, size_t > (frontend_alloc.allocation_id, tuner_id));
					tunerChannels[tuner_id].frontend_status->allocation_id_csv = create_allocation_id_csv(tuner_id);
					return tuner_id;
				}
			}
			//control
			else if (frontend_alloc.device_control && tunerChannels[tuner_id].control_allocation_id.empty()){
				tunerChannels[tuner_id].control_allocation_id = frontend_alloc.allocation_id;
				allocationID_to_tunerID.insert(std::pair<std::string, size_t > (frontend_alloc.allocation_id, tuner_id));
				tunerChannels[tuner_id].frontend_status->allocation_id_csv = create_allocation_id_csv(tuner_id);
				return tuner_id;
			}
		}
		return NO_VALID_TUNER;
	}

	template < typename TunerStatusStructType >
	long FrontendTunerDevice<TunerStatusStructType>::addTunerMapping(const frontend::frontend_listener_allocation_struct & frontend_listener_alloc){
		long NO_VALID_TUNER = -1;
		exclusive_lock lock(allocationID_MappingLock);

		// Do not allocate if allocation ID has already been used
		if (getTunerMapping(frontend_listener_alloc.listener_allocation_id) >= 0)
			return NO_VALID_TUNER;

		long tuner_id = NO_VALID_TUNER;
		// Do not allocate if existing allocation ID does not exist
		if ((tuner_id = getTunerMapping(frontend_listener_alloc.existing_allocation_id)) < 0)
			return NO_VALID_TUNER;

		allocationID_to_tunerID.insert(std::pair<std::string, size_t > (frontend_listener_alloc.listener_allocation_id, tuner_id));
		tunerChannels[tuner_id].frontend_status->allocation_id_csv = create_allocation_id_csv(tuner_id);
		return tuner_id;
	}

	template < typename TunerStatusStructType >
	long FrontendTunerDevice<TunerStatusStructType>::getTunerMapping(std::string allocation_id) {
		long NO_VALID_TUNER = -1;
		exclusive_lock lock(allocationID_MappingLock);

		string_number_mapping::iterator iter = allocationID_to_tunerID.find(allocation_id);
		if (iter != allocationID_to_tunerID.end())
			return iter->second;

		return NO_VALID_TUNER;
	}


	template < typename TunerStatusStructType >
	bool FrontendTunerDevice<TunerStatusStructType>::removeTunerMapping(std::string allocation_id) {
		exclusive_lock lock(allocationID_MappingLock);
		if(allocationID_to_tunerID.erase(allocation_id) > 0)
			return true;
		return false;

	}

	template < typename TunerStatusStructType >
	bool FrontendTunerDevice<TunerStatusStructType>::removeTunerMapping(size_t tuner_id) {
		long cnt = 0;
		exclusive_lock lock(allocationID_MappingLock);
		for(string_number_mapping::iterator it = allocationID_to_tunerID.begin(); it != allocationID_to_tunerID.end(); it++){
			if(it->second == tuner_id){
				allocationID_to_tunerID.erase(it);
				cnt++;
			}
		}
		return cnt > 0;
	}

	template < typename TunerStatusStructType >
	bool FrontendTunerDevice<TunerStatusStructType>::is_connectionID_valid_for_tunerID(const size_t & tuner_id, const std::string & connectionID) {
		std::map<std::string, size_t>::iterator iter =  allocationID_to_tunerID.find(connectionID);
		if(iter == allocationID_to_tunerID.end())
			return false;
		if(iter->second != tuner_id)
			return false;
		return true;
	}


	template < typename TunerStatusStructType >
	bool FrontendTunerDevice<TunerStatusStructType>::is_connectionID_valid_for_streamID(const std::string & streamID, const std::string & connectionID) {
		string_number_mapping::iterator iter = streamID_to_tunerID.find(streamID);
		if (iter == streamID_to_tunerID.end())
			return false;
		return is_connectionID_valid_for_tunerID(iter->second, connectionID);
	}

	template < typename TunerStatusStructType >
	bool FrontendTunerDevice<TunerStatusStructType>::is_connectionID_controller_for_streamID(const std::string & streamID, const std::string & connectionID) {
		string_number_mapping::iterator iter = streamID_to_tunerID.find(streamID);
		if (iter == streamID_to_tunerID.end())
			return false;
		if (!is_connectionID_valid_for_tunerID(iter->second, connectionID))
			return false;
		if (tunerChannels[iter->second].control_allocation_id != connectionID)
			return false;
		return true;
	}

	template < typename TunerStatusStructType >
	bool FrontendTunerDevice<TunerStatusStructType>::is_connectionID_listener_for_streamID(const std::string & streamID, const std::string & connectionID) {
		string_number_mapping::iterator iter = streamID_to_tunerID.find(streamID);
		if (iter == streamID_to_tunerID.end())
			return false;
		if (!is_connectionID_valid_for_tunerID(iter->second, connectionID))
			return false;
		if (tunerChannels[iter->second].control_allocation_id == connectionID)
			return false;
		return true;
	}

	template < typename TunerStatusStructType >
	bool FrontendTunerDevice<TunerStatusStructType>::is_freq_valid(double req_cf, double req_bw, double req_sr, double cf, double bw, double sr){
		double req_min_bw_sr = std::min(req_bw,req_sr);
		double min_bw_sr = std::min(bw,sr);
		if( (req_cf + req_min_bw_sr/2 <= cf + min_bw_sr/2) && (req_cf - req_min_bw_sr/2 >= cf - min_bw_sr/2) )
			return true;
		return false;
	};

}; // end frontend namespace
