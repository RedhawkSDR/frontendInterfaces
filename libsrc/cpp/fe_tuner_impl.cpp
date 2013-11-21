#include "fe_tuner_impl.h"

FE_Tuner_impl::FE_Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl) :
    Device_impl(devMgr_ior, id, lbl, sftwrPrfl)
{
    construct();
}

FE_Tuner_impl::FE_Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev) :
    Device_impl(devMgr_ior, id, lbl, sftwrPrfl, compDev)
{
    construct();
}

FE_Tuner_impl::FE_Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities) :
    Device_impl(devMgr_ior, id, lbl, sftwrPrfl, capacities)
{
    construct();
}

FE_Tuner_impl::FE_Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev) :
    Device_impl(devMgr_ior, id, lbl, sftwrPrfl, capacities, compDev)
{
    construct();
}

void FE_Tuner_impl::construct()
{
    Resource_impl::_started = false;
    loadProperties();
}

FE_Tuner_impl::~FE_Tuner_impl()
{
	for (size_t i = 0; i < tunerChannels.size(); i++) {
		if (tunerChannels[i].lock != NULL)
			delete tunerChannels[i].lock;
	}
	tunerChannels.clear();
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void FE_Tuner_impl::loadProperties()
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

std::string FE_Tuner_impl::create_allocation_id_csv(size_t tunerNum){
	std::string alloc_id_csv = "";
	// ensure control allocation_id is first in list
	if (!getTunerChannel(tunerNum)->control_allocation_id.empty())
		alloc_id_csv = getTunerChannel(tunerNum)->control_allocation_id + ",";
	// now add the rest
	for(string_number_mapping::iterator it = allocationId_to_tunerNum.begin(); it != allocationId_to_tunerNum.end(); it++){
		if(it->second == tunerNum && it->first != getTunerChannel(tunerNum)->control_allocation_id)
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
CF::Device::UsageType FE_Tuner_impl::updateUsageState() {
	size_t tunerAllocated = 0;
	for (size_t i = 0; i < sizeofTunerChannels(); i++) {
		if (!getTunerChannel(i)->control_allocation_id.empty())
			tunerAllocated++;
	}
	// If no tuners are allocated, device is idle
	if (tunerAllocated == 0)
		return CF::Device::IDLE;
	// If all tuners are allocated, device is busy
	if (tunerAllocated == sizeofTunerChannels())
		return CF::Device::BUSY;
	// Else, device is active
	return CF::Device::ACTIVE;
}

////////////////////////////
//        MAPPING         //
////////////////////////////
/*
long FE_Tuner_impl::addTunerMapping(const frontend::frontend_tuner_allocation_struct & frontend_alloc) {
	long NO_VALID_TUNER = -1;

	// Do not allocate if allocation ID has already been used
	if(getTunerMapping(frontend_alloc.allocation_id) >= 0)
		return NO_VALID_TUNER;

	// Next, try to allocate a new tuner
	exclusive_lock lock(allocationID_MappingLock);
	for (long tunerNum = 0; tunerNum < long(frontend_tuner_status.size()); tunerNum++) {
		if(getTunerChannel(tunerNum)->getFrontendStatus()->tuner_type != frontend_alloc.tuner_type)
			continue;
		bool freq_valid = is_freq_valid(frontend_alloc.center_frequency, frontend_alloc.bandwidth, frontend_alloc.sample_rate,
				frontend_tuner_status[tunerNum].center_frequency, frontend_tuner_status[tunerNum].bandwidth, frontend_tuner_status[tunerNum].sample_rate);
		//listen
		if (!frontend_alloc.device_control && ! getTunerChannel(tunerNum)->control_allocation_id.empty() && freq_valid){
			allocationId_to_tunerNum.insert(std::pair<std::string, size_t > (frontend_alloc.allocation_id, tunerNum));
			getTunerChannel(tunerNum)->getFrontendStatus()->allocation_id_csv = create_allocation_id_csv(tunerNum);
			return tunerNum;
		}
		//control
		else if (frontend_alloc.device_control && getTunerChannel(tunerNum)->control_allocation_id.empty()){
			getTunerChannel(tunerNum)->control_allocation_id = frontend_alloc.allocation_id;
			allocationId_to_tunerNum.insert(std::pair<std::string, size_t > (frontend_alloc.allocation_id, tunerNum));
			getTunerChannel(tunerNum)->getFrontendStatus()->allocation_id_csv = create_allocation_id_csv(tunerNum);
			return tunerNum;
		}

	}
	return NO_VALID_TUNER;
}


long FE_Tuner_impl::addTunerMapping(const frontend::frontend_listener_allocation_struct & frontend_listner_alloc){

	long NO_VALID_TUNER = -1;

	//TODO (add this to USRP develop branch) - Do not allocate if allocation ID has already been used
	if (getTunerMapping(frontend_listner_alloc.listener_allocation_id) >= 0)
		return NO_VALID_TUNER;
	int tunerNum = NO_VALID_TUNER;
	// Do not allocate if existing allocation ID does not exist
	if ((tunerNum = getTunerMapping(frontend_listner_alloc.existing_allocation_id)) < 0)
		return NO_VALID_TUNER;

	allocationId_to_tunerNum.insert(std::pair<std::string, size_t > (frontend_listner_alloc.listener_allocation_id, tunerNum));
	getTunerChannel(tunerNum)->getFrontendStatus()->allocation_id_csv = create_allocation_id_csv(tunerNum);
	return tunerNum;
}*/


long FE_Tuner_impl::getTunerMapping(std::string allocation_id) {
	long NO_VALID_TUNER = -1;

	exclusive_lock lock(allocationID_MappingLock);
	string_number_mapping::iterator iter = allocationId_to_tunerNum.find(allocation_id);
	if (iter != allocationId_to_tunerNum.end())
		return iter->second;

	return NO_VALID_TUNER;
}


bool FE_Tuner_impl::removeTunerMapping(std::string allocation_id) {
	exclusive_lock lock(allocationID_MappingLock);
	if(allocationId_to_tunerNum.erase(allocation_id) > 0)
		return true;
	return false;

}

bool FE_Tuner_impl::removeTunerMapping(size_t tuner_id) {
	long cnt = 0;
	for(string_number_mapping::iterator it = allocationId_to_tunerNum.begin(); it != allocationId_to_tunerNum.end(); it++){
		if(it->second == tuner_id){
			allocationId_to_tunerNum.erase(it);
			cnt++;
		}
	}
	return cnt > 0;
}

bool FE_Tuner_impl::is_connectionID_valid_for_tunerNum(const size_t & tunerNum, const std::string & connectionID) {
	std::map<std::string, size_t>::iterator iter =  allocationId_to_tunerNum.find(connectionID);
	if(iter == allocationId_to_tunerNum.end())
		return false;
	if(iter->second != tunerNum)
		return false;
	return true;
}


bool FE_Tuner_impl::is_connectionID_valid_for_streamID(const std::string & streamID, const std::string & connectionID) {
	string_number_mapping::iterator iter = streamID_to_tunerNum.find(streamID);
	if (iter == streamID_to_tunerNum.end())
		return false;
	return is_connectionID_valid_for_tunerNum(iter->second, connectionID);
}

bool FE_Tuner_impl::is_connectionID_controller_for_streamID(const std::string & streamID, const std::string & connectionID) {
	string_number_mapping::iterator iter = streamID_to_tunerNum.find(streamID);
	if (iter == streamID_to_tunerNum.end())
		return false;
	if (!is_connectionID_valid_for_tunerNum(iter->second, connectionID))
		return false;
	if (getTunerChannel(iter->second)->control_allocation_id != connectionID)
		return false;
	return true;
}

bool FE_Tuner_impl::is_connectionID_listener_for_streamID(const std::string & streamID, const std::string & connectionID) {
	string_number_mapping::iterator iter = streamID_to_tunerNum.find(streamID);
	if (iter == streamID_to_tunerNum.end())
		return false;
	if (!is_connectionID_valid_for_tunerNum(iter->second, connectionID))
		return false;
	if (getTunerChannel(iter->second)->control_allocation_id == connectionID)
		return false;
	return true;
}

bool FE_Tuner_impl::is_freq_valid(double req_cf, double req_bw, double req_sr, double cf, double bw, double sr){
	double req_min_bw_sr = std::min(req_bw,req_sr);
	double min_bw_sr = std::min(bw,sr);
	if( (req_cf + req_min_bw_sr/2 <= cf + min_bw_sr/2) && (req_cf - req_min_bw_sr/2 >= cf - min_bw_sr/2) )
		return true;
	return false;
};

