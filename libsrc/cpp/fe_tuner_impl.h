#ifndef FE_TUNER_IMPL_BASE_H
#define FE_TUNER_IMPL_BASE_H

//#include <boost/thread.hpp>
#include <ossie/Device_impl.h>
#include <uuid/uuid.h>
#include <FRONTEND/Frontend.h>

#include "ossie/prop_helpers.h"
#include "bulkio/bulkio.h"
#include "fe_tuner_struct_props.h"


/*********************************************************************************************/
/**************************             UUID_HELPER                 **************************/
/*********************************************************************************************/
namespace UUID_HELPER { // should this just exist within namespace "frontend"?
    inline std::string new_uuid() {
        uuid_t new_random_uuid;
        uuid_generate_random(new_random_uuid);
        char new_random_uuid_str[37];
        uuid_unparse(new_random_uuid, new_random_uuid_str);
        return std::string(new_random_uuid_str);
    };
}; // end of namespace UUID_HELPER

/*********************************************************************************************/
/**************************             BULKIO HELPERS              **************************/
/*********************************************************************************************/
namespace BIO_HELPER{ // should this just extend the "bulkio" namespace, rather than create a new one? or be part of "frontend" namespace?

	inline void zeroSRI(BULKIO::StreamSRI *sri) {
		sri->hversion = 1;
		sri->xstart = 0.0;
		sri->xdelta = 1.0;
		sri->xunits = 1;
		sri->subsize = 1;
		sri->ystart = 0.0;
		sri->ydelta = 1.0;
		sri->yunits = 1;
		sri->mode = 0;
		sri->streamID = "";
		sri->keywords.length(0);
	};

	inline void zeroTime(BULKIO::PrecisionUTCTime *timeTag) {
		timeTag->tcmode = 1;
		timeTag->tcstatus = 0;
		timeTag->toff = 0.0;
		timeTag->twsec = 0.0;
		timeTag->tfsec = 0.0;
	};
}; // end of namespace BIO_HELPER


namespace frontend {

	/** Individual Tuner. This structure contains stream specific data for channel/tuner to include:
	 * 		- Additional stream metadata (sri)
	 * 		- Control information (allocation id's)
	 * 		- Reference to associated frontend_tuner_status property where additional information is held. Note: frontend_tuner_status structure is required by frontend interfaces v2.0
	 */

	struct indivTuner {
		indivTuner(){
			setFrontendStatus(NULL);
		}
		BULKIO::StreamSRI sri;
		boost::mutex *lock;
		std::string control_allocation_id;
		frontend::default_frontend_tuner_status_struct_struct* frontend_status;

		virtual frontend::default_frontend_tuner_status_struct_struct* getFrontendStatus(){
			return frontend_status;
		}
		virtual void setFrontendStatus(frontend::default_frontend_tuner_status_struct_struct* fs){
			frontend_status = fs;
		}

		void reset(){
			BIO_HELPER::zeroSRI(&sri);
			control_allocation_id.clear();

			frontend::default_frontend_tuner_status_struct_struct* stat = getFrontendStatus();
			if(stat != NULL){
				stat->allocation_id_csv.clear();
				stat->center_frequency = 0.0;
				stat->bandwidth = 0.0;
				stat->sample_rate = 0.0;
				stat->enabled = true;
			}
		}
	};

}; // end of namespace frontend


////////////////////////////
//    CLASS DEFINITION    //
////////////////////////////

class FE_Tuner_impl : public Device_impl
{
    public:
        FE_Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl);
        FE_Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev);
        FE_Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities);
        FE_Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev);
        ~FE_Tuner_impl();

        // this is overridden in child class if properties are added
        virtual void loadProperties();

    	// Device specific allocation handling
    	virtual CF::Device::UsageType updateUsageState();
        //TODO virtual CORBA::Boolean allocateCapacity(const CF::Properties & capacities) throw (CORBA::SystemException, CF::Device::InvalidCapacity, CF::Device::InvalidState);
        //TODO virtual void deallocateCapacity(const CF::Properties & capacities)throw (CORBA::SystemException, CF::Device::InvalidCapacity, CF::Device::InvalidState);

        // Mapping and translation helpers. External string identifiers to internal numerical identifiers
        //TODO virtual long addTunerMapping(const frontend::frontend_tuner_allocation_struct & frontend_alloc);
    	//TODO virtual long addTunerMapping(const frontend::frontend_listener_allocation_struct & frontend_listner_alloc);
    	virtual bool removeTunerMapping(std::string allocation_id);
    	virtual bool removeTunerMapping(size_t tuner_id);
    	virtual long getTunerMapping(std::string allocation_id);
    	virtual bool is_connectionID_valid_for_tunerNum( const size_t & tunerNum, const std::string & connectionID);
    	virtual bool is_connectionID_valid_for_streamID( const std::string & streamID, const std::string & connectionID);
    	virtual bool is_connectionID_controller_for_streamID(const std::string & streamID, const std::string & connectionID);
    	virtual bool is_connectionID_listener_for_streamID(const std::string & streamID, const std::string & connectionID);
    	virtual bool is_freq_valid(double req_cf, double req_bw, double req_sr, double cf, double bw, double sr);

    	// Configure wideband tuner - gets called during wideband allocation
    	virtual  bool setupTuner(size_t tuner_id, const frontend::frontend_tuner_allocation_struct& tuner_req) throw (std::logic_error,FRONTEND::BadParameterException) = 0;
    	virtual  bool enableTuner(size_t tuner_id, bool enable) = 0;
    	virtual  bool removeTuner(size_t tuner_id) = 0;

    protected:
    	//	typedef std::vector<std::string> stringVector;
    		typedef std::map<std::string, size_t> string_number_mapping;
    	//	typedef std::map<std::string, std::string> string_string_mapping;
    	//	typedef std::map<std::string, stringVector > string_stringVector_mapping;
    		typedef boost::mutex::scoped_lock exclusive_lock;

        // Member variables exposed as properties
        std::string device_kind;
        std::string device_model;
        frontend::frontend_tuner_allocation_struct frontend_tuner_allocation;
        frontend::frontend_listener_allocation_struct frontend_listener_allocation;
        std::vector<frontend::default_frontend_tuner_status_struct_struct> frontend_tuner_status;

        std::string create_allocation_id_csv(size_t tunerNum);

		// tunerChannels is exclusively paired with property tuner_status.
        // tunerChannels provide stream information for the channel while tuner_status provides the tuner information.
		std::vector<frontend::indivTuner> tunerChannels;
		// these will be overriden by parent classes if necessary
		virtual frontend::indivTuner* getTunerChannel(size_t tunerNum){return &(tunerChannels[tunerNum]);}
		virtual size_t sizeofTunerChannels(){return tunerChannels.size();}
		virtual void clearTunerChannels(){tunerChannels.clear();}
		virtual void resizeTunerChannels(size_t sz){tunerChannels.resize(sz);}

		// Provides mapping from unique allocation ID to internal tuner (channel) number
		string_number_mapping allocationId_to_tunerNum;
		string_number_mapping streamID_to_tunerNum;
		boost::mutex allocationID_MappingLock;


		////////////////////////////
		// Other helper functions //
		////////////////////////////

		inline frontend::frontend_tuner_allocation_struct feAlloc_from_feStatus(size_t tuner_id){
			frontend::frontend_tuner_allocation_struct newStruct;
			newStruct.tuner_type= getTunerChannel(tuner_id)->getFrontendStatus()->tuner_type;
			newStruct.allocation_id= getTunerChannel(tuner_id)->control_allocation_id;
			newStruct.center_frequency= getTunerChannel(tuner_id)->getFrontendStatus()->center_frequency;
			newStruct.bandwidth= getTunerChannel(tuner_id)->getFrontendStatus()->bandwidth;
			newStruct.sample_rate= getTunerChannel(tuner_id)->getFrontendStatus()->sample_rate;
			newStruct.device_control= true;
			newStruct.group_id = getTunerChannel(tuner_id)->getFrontendStatus()->group_id;
			newStruct.rf_flow_id= getTunerChannel(tuner_id)->getFrontendStatus()->rf_flow_id;
			return newStruct;
		}

		template <typename CORBAXX> bool addModifyKeyword(BULKIO::StreamSRI *sri, CORBA::String_member id, CORBAXX myValue, bool addOnly = false) {
			CORBA::Any value;
			value <<= myValue;
			unsigned long keySize = sri->keywords.length();
			if (!addOnly) {
				for (unsigned int i = 0; i < keySize; i++) {
					if (!strcmp(sri->keywords[i].id, id)) {
						sri->keywords[i].value = value;
						return true;
					}
				}
			}
			sri->keywords.length(keySize + 1);
			if (sri->keywords.length() != keySize + 1)
				return false;
			sri->keywords[keySize].id = CORBA::string_dup(id);
			sri->keywords[keySize].value = value;
			return true;
		}

		// This is not currently used but is available as a debugging tool
		void printSRI(BULKIO::StreamSRI *sri, std::string strHeader = "DEBUG SRI"){
			std::cout << strHeader << ":\n";
			std::cout << "\thversion: " << sri->hversion<< std::endl;
			std::cout << "\txstart: " << sri->xstart<< std::endl;
			std::cout << "\txdelta: " << sri->xdelta<< std::endl;
			std::cout << "\txunits: " << sri->xunits<< std::endl;
			std::cout << "\tsubsize: " << sri->subsize<< std::endl;
			std::cout << "\tystart: " << sri->ystart<< std::endl;
			std::cout << "\tydelta: " << sri->ydelta<< std::endl;
			std::cout << "\tyunits: " << sri->yunits<< std::endl;
			std::cout << "\tmode: " << sri->mode<< std::endl;
			std::cout << "\tstreamID: " << sri->streamID<< std::endl;
			unsigned long keySize = sri->keywords.length();
			for (unsigned int i = 0; i < keySize; i++) {
				std::cout << "\t KEYWORD KEY/VAL :: " << sri->keywords[i].id << ": " << ossie::any_to_string(sri->keywords[i].value) << std::endl;
			}
			std::cout << std::endl;
		}

    private:
		virtual void construct();

};
#endif
