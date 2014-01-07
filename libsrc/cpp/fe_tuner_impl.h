#ifndef FE_TUNER_IMPL_BASE_H
#define FE_TUNER_IMPL_BASE_H

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





/*********************************************************************************************/
/**************************              FRONTEND                   **************************/
/*********************************************************************************************/
namespace frontend {

	// Time Type Definition
	enum timeTypes {
		J1970 = 1,
		JCY = 2
	};

	/** Individual Tuner. This structure contains stream specific data for channel/tuner to include:
	 * 		- Additional stream metadata (sri)
	 * 		- Control information (allocation id's)
	 * 		- Reference to associated frontend_tuner_status property where additional information is held. Note: frontend_tuner_status structure is required by frontend interfaces v2.0
	 */

	template < typename TunerStatusStructType >
	struct indivTuner {
		indivTuner(){
			frontend_status = NULL;
			lock = NULL;
		}
		BULKIO::StreamSRI sri;
		boost::mutex *lock;
		std::string control_allocation_id;
		TunerStatusStructType* frontend_status;

		void reset(){
			BIO_HELPER::zeroSRI(&sri);
			control_allocation_id.clear();
			if(frontend_status != NULL){
				frontend_status->allocation_id_csv.clear();
				frontend_status->center_frequency = 0.0;
				frontend_status->bandwidth = 0.0;
				frontend_status->sample_rate = 0.0;
				frontend_status->complex = true;
				frontend_status->enabled = false;
			}
		}
	};

	//////////////////////////////////
	//    TUNER CLASS DEFINITION    //
	//////////////////////////////////

	template < typename TunerStatusStructType >
	class Tuner_impl : public Device_impl
	{
		public:
			Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl);
			Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev);
			Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities);
			Tuner_impl(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev);
			~Tuner_impl();

			// this is implemented in the generated base class once all properties are known
			virtual void loadProperties();

			// Device specific allocation handling
			virtual CF::Device::UsageType updateUsageState();
			virtual CORBA::Boolean allocateCapacity(const CF::Properties & capacities) throw (CORBA::SystemException, CF::Device::InvalidCapacity, CF::Device::InvalidState);
			virtual void deallocateCapacity(const CF::Properties & capacities)throw (CORBA::SystemException, CF::Device::InvalidCapacity, CF::Device::InvalidState);

	    	// Mapping and translation helpers. External string identifiers to internal numerical identifiers
	        virtual long addTunerMapping(const frontend::frontend_tuner_allocation_struct & frontend_alloc);
	    	virtual long addTunerMapping(const frontend::frontend_listener_allocation_struct & frontend_listner_alloc);
			virtual bool removeTunerMapping(std::string allocation_id);
			virtual bool removeTunerMapping(size_t tuner_id);
			virtual long getTunerMapping(std::string allocation_id);
			virtual bool is_connectionID_valid_for_tunerID( const size_t & tuner_id, const std::string & connectionID);
			virtual bool is_connectionID_valid_for_streamID( const std::string & streamID, const std::string & connectionID);
			virtual bool is_connectionID_controller_for_streamID(const std::string & streamID, const std::string & connectionID);
			virtual bool is_connectionID_listener_for_streamID(const std::string & streamID, const std::string & connectionID);
			virtual bool is_freq_valid(double req_cf, double req_bw, double req_sr, double cf, double bw, double sr);

			// Configure tuner - gets called during allocation
			virtual bool enableTuner(size_t tuner_id, bool enable);
			virtual bool removeTuner(size_t tuner_id);

		protected:
			typedef std::map<std::string, size_t> string_number_mapping;
			typedef boost::mutex::scoped_lock exclusive_lock;

			// Member variables exposed as properties
			std::string device_kind;
			std::string device_model;
			frontend::frontend_tuner_allocation_struct frontend_tuner_allocation;
			frontend::frontend_listener_allocation_struct frontend_listener_allocation;
			std::vector<TunerStatusStructType> frontend_tuner_status;

			std::string create_allocation_id_csv(size_t tuner_id);

			// tunerChannels is exclusively paired with property tuner_status.
			// tunerChannels provide stream information for the channel while tuner_status provides the tuner information.
			std::vector<frontend::indivTuner<TunerStatusStructType> > tunerChannels;

			// Provides mapping from unique allocation ID to internal tuner (channel) number
			string_number_mapping allocationID_to_tunerID;
			string_number_mapping streamID_to_tunerID;
			boost::mutex allocationID_MappingLock;

			///////////////////////////////
			// Device specific functions // -- virtual - to be implemented by device developer
			///////////////////////////////
		    virtual bool push_EOS_on_listener(std::string listener_allocation_id) = 0;

			virtual bool _valid_tuner_type(std::string tuner_type) = 0;
			virtual bool _valid_center_frequency(double req_freq, size_t tuner_id) = 0;
			virtual bool _valid_bandwidth(double req_bw, size_t tuner_id) = 0;
			virtual bool _valid_sample_rate(double req_sr, size_t tuner_id) = 0;

			virtual bool _dev_enable(size_t tuner_id) = 0;
			virtual bool _dev_disable(size_t tuner_id) = 0;

			virtual bool _dev_set_all(double req_freq, double req_bw, double req_sr, size_t tuner_id) = 0;
			virtual bool _dev_set_center_frequency(double req_freq, size_t tuner_id) = 0;
			virtual bool _dev_set_bandwidth(double req_bw, size_t tuner_id) = 0;
			virtual bool _dev_set_sample_rate(double req_sr, size_t tuner_id) = 0;

			virtual bool _dev_get_all(double &freq, double &bw, double &sr, size_t tuner_id) = 0;
			virtual double _dev_get_center_frequency(size_t tuner_id) = 0;
			virtual double _dev_get_bandwidth(size_t tuner_id) = 0;
			virtual double _dev_get_sample_rate(size_t tuner_id) = 0;

			////////////////////////////
			// Other helper functions //
			////////////////////////////

		    virtual double optimize_rate(const double& req_rate, const double& max_rate, const double& min_rate){
		        for(size_t dec = size_t(max_rate/min_rate); dec >= 1; dec--){
		            if(max_rate/double(dec) >= req_rate)
		                return max_rate/double(dec);
		        }
		        return req_rate;
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

			virtual void configureTunerSRI(BULKIO::StreamSRI *sri, double frequency, double bandwidth, double sample_rate, short mode, std::string rf_flow_id) {
				if (sri == NULL)
					return;

				//Convert CenterFreq into string
				long centerFreq = long(frequency);
				char centerFreq_str[16];
				sprintf(centerFreq_str, "%ld", centerFreq);

				//Create new streamID
				std::string streamID = "tuner_freq_" + std::string(centerFreq_str) + "_Hz_" + UUID_HELPER::new_uuid();

				sri->mode = mode;
				sri->hversion = 0;
				sri->xstart = 0;
				sri->xdelta = (1.0 / (sample_rate));
				sri->subsize = 0;// 1-dimensional data
				sri->xunits = 1;
				sri->ystart = 0;
				sri->ydelta = 0.001;
				sri->yunits = 1;
				sri->streamID = CORBA::string_dup(streamID.c_str());
				sri->blocking = false;

				addModifyKeyword<CORBA::Double > (sri, "COL_RF", CORBA::Double(centerFreq));
				addModifyKeyword<CORBA::Double > (sri, "CHAN_RF", CORBA::Double(centerFreq));
				addModifyKeyword<std::string> (sri,"FRONTEND::RF_FLOW_ID",rf_flow_id);
				addModifyKeyword<CORBA::Double> (sri,"FRONTEND::BANDWIDTH", CORBA::Double(bandwidth));
				addModifyKeyword<std::string> (sri,"FRONTEND::DEVICE_ID",std::string(identifier()));
			}

			virtual void updateSriTimes(BULKIO::StreamSRI *sri, double timeUp, double timeDown, timeTypes timeType) {

				std::stringstream DOIU;
				std::stringstream TUOI;
				std::stringstream DOID;
				std::stringstream TDOI;

				time_t time_up = (time_t) timeUp;
				time_t time_down = (time_t) timeDown;
				time_t now;
				struct tm curr_time;
				curr_time.tm_year = 0;
				struct tm gmt_up;
				struct tm gmt_down;

				gmt_up = *gmtime(&time_up);
				gmt_down = *gmtime(&time_down);
				if (timeType == JCY) {
					now = time(0);
					curr_time = *gmtime(&now);
				}

				DOIU.width(4);
				DOIU.fill('0');
				if (timeType == JCY)
					DOIU << (curr_time.tm_year + 1900);
				else
					DOIU << (gmt_up.tm_year + 1900);
				DOIU.width(2);
				DOIU.fill('0');
				DOIU << (gmt_up.tm_mon + 1);
				DOIU.width(2);
				DOIU.fill('0');
				DOIU << gmt_up.tm_mday;

				TUOI.width(2);
				TUOI.fill('0');
				TUOI << gmt_up.tm_hour;
				TUOI.width(2);
				TUOI.fill('0');
				TUOI << gmt_up.tm_min;
				TUOI.width(2);
				TUOI.fill('0');
				TUOI << gmt_up.tm_sec;

				DOID.width(4);
				DOID.fill('0');
				DOID << (gmt_down.tm_year + 1900);
				DOID.width(2);
				DOID.fill('0');
				DOID << (gmt_down.tm_mon + 1);
				DOID.width(2);
				DOID.fill('0');
				DOID << gmt_down.tm_mday;

				TDOI.width(2);
				TDOI.fill('0');
				TDOI << gmt_down.tm_hour;
				TDOI.width(2);
				TDOI.fill('0');
				TDOI << gmt_down.tm_min;
				TDOI.width(2);
				TDOI.fill('0');
				TDOI << gmt_down.tm_sec;


				addModifyKeyword<std::string > (sri, "DOIU", DOIU.str());
				addModifyKeyword<std::string > (sri, "TUOI", TUOI.str());
				addModifyKeyword<std::string > (sri, "DOID", DOID.str());
				addModifyKeyword<std::string > (sri, "TDOI", TDOI.str());

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
			// this will be overridden by the generated base class once all ports are known
			virtual void construct();
	};

}; // end frontend namespace

#endif
