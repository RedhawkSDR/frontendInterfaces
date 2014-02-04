#ifndef FE_RFINFO_PORT_H
#define FE_RFINFO_PORT_H

#include "fe_port_impl.h"

#include <FRONTEND/RFInfo.h>
#include <ossie/CorbaUtils.h>

namespace frontend {
    
    struct FreqRange {
        double min_val;
        double max_val;
        std::vector<double> values;
    };
    struct AntennaInfo {
        std::string name;
        std::string type;
        std::string size;
        std::string description;
    };
    struct FeedInfo {
        std::string name;
        std::string polarization;
        FreqRange freq_range;
    };
    struct SensorInfo {
        std::string mission;
        std::string collector;
        std::string rx;
        AntennaInfo antenna;
        FeedInfo feed;
    };
    struct PathDelay {
        double freq;
        double delay_ns;
    };
    typedef std::vector<PathDelay> PathDelays;
    struct RFCapabilities {
        FreqRange freq_range;
        FreqRange bw_range;
    };
    struct RFInfoPkt {
        std::string rf_flow_id;
        double rf_center_freq;
        double rf_bandwidth;
        double if_center_freq;
        bool spectrum_inverted;
        SensorInfo sensor;
        PathDelays ext_path_delays;
        RFCapabilities capabilities;
        CF::Properties additional_info;
    };
    typedef std::vector<RFInfoPkt> RFInfoPktSequence;
    
    class rfsource_delegation {
        public:
            virtual std::vector<RFInfoPkt> get_available_rf_inputs() = 0;
            virtual void set_available_rf_inputs(std::vector<RFInfoPkt> &inputs) = 0;
            virtual RFInfoPkt get_current_rf_input() = 0;
            virtual void set_current_rf_input(RFInfoPkt &input) = 0;
    };
    class rfinfo_delegation {
        public:
            virtual std::string get_rf_flow_id(std::string& port_name) = 0;
            virtual void set_rf_flow_id(std::string& port_name, const std::string& id) = 0;
            virtual RFInfoPkt get_rfinfo_pkt(std::string& port_name) = 0;
            virtual void set_rfinfo_pkt(std::string& port_name, const RFInfoPkt &pkt) = 0;
    };
    
    FRONTEND::RFInfoPkt* returnRFInfoPkt(const RFInfoPkt &val);
    RFInfoPkt returnRFInfoPkt(const FRONTEND::RFInfoPkt &tmpVal);
    
    class InRFSourcePort : public POA_FRONTEND::RFSource, public Port_Provides_base_impl
    {
        public:
            InRFSourcePort(std::string port_name, rfsource_delegation *_parent) : 
            Port_Provides_base_impl(port_name)
            {
                parent = _parent;
            };
            ~InRFSourcePort() {};
            
            FRONTEND::RFInfoPktSequence* available_rf_inputs() {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::vector<frontend::RFInfoPkt> retval = this->parent->get_available_rf_inputs();
                FRONTEND::RFInfoPktSequence* tmpVal = new FRONTEND::RFInfoPktSequence();
                std::vector<frontend::RFInfoPkt>::iterator itr = retval.begin();
                while (itr != retval.end()) {
                    FRONTEND::RFInfoPkt_var tmp = frontend::returnRFInfoPkt((*itr));
                    tmpVal->length(tmpVal->length()+1);
                    (*tmpVal)[tmpVal->length()-1] = tmp;
                    itr++;
                }
                return tmpVal;
            };
            void available_rf_inputs( const FRONTEND::RFInfoPktSequence& data) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::vector<frontend::RFInfoPkt> inputs;
                inputs.resize(data.length());
                for (unsigned int i=0; i<inputs.size(); i++) {
                    inputs[i] = frontend::returnRFInfoPkt(data[i]);
                }
                this->parent->set_available_rf_inputs(inputs);
            };
            FRONTEND::RFInfoPkt* current_rf_input() {
                boost::mutex::scoped_lock lock(this->portAccess);
                frontend::RFInfoPkt retval = this->parent->get_current_rf_input();
                FRONTEND::RFInfoPkt* tmpVal = frontend::returnRFInfoPkt(retval);
                return tmpVal;
            };
            void current_rf_input( const FRONTEND::RFInfoPkt& data) {
                boost::mutex::scoped_lock lock(this->portAccess);
                frontend::RFInfoPkt input = frontend::returnRFInfoPkt(data);
                this->parent->set_current_rf_input(input);
            };
            
        protected:
            rfsource_delegation *parent;
            boost::mutex portAccess;
    };
    
    class InRFInfoPort : public POA_FRONTEND::RFInfo, public Port_Provides_base_impl
    {
        public:
            InRFInfoPort(std::string port_name, rfinfo_delegation *_parent) : 
            Port_Provides_base_impl(port_name)
            {
                parent = _parent;
            };
            ~InRFInfoPort() {};
            
            char* rf_flow_id() {
                boost::mutex::scoped_lock lock(portAccess);
                return (CORBA::string_dup(this->parent->get_rf_flow_id(this->name).c_str()));
            };
            void rf_flow_id(const char *id) {
                boost::mutex::scoped_lock lock(portAccess);
                std::string _id(id);
                this->parent->set_rf_flow_id(this->name, _id);
                return;
            };
            FRONTEND::RFInfoPkt* rfinfo_pkt() {
                boost::mutex::scoped_lock lock(portAccess);
                frontend::RFInfoPkt retval = this->parent->get_rfinfo_pkt(this->name);
                FRONTEND::RFInfoPkt* tmpVal = frontend::returnRFInfoPkt(retval);
                return tmpVal;
            };
            void rfinfo_pkt(const FRONTEND::RFInfoPkt& data) {
                boost::mutex::scoped_lock lock(portAccess);
                frontend::RFInfoPkt input = frontend::returnRFInfoPkt(data);
                this->parent->set_rfinfo_pkt(this->name, input);
                return;
            };
            
        protected:
            rfinfo_delegation *parent;
            boost::mutex portAccess;
    };
    
	// ----------------------------------------------------------------------------------------
	// InRFInfoPort declaration
	// ----------------------------------------------------------------------------------------
	/*class InRFInfoPort : public POA_FRONTEND::RFInfo, public Port_Provides_base_impl
	{
	    public:
	        InRFInfoPort(std::string port_name,
                             CharFromVoid *newRFFlowIdGetterCB = NULL,
                             RFInfoPktFromVoid *newRFInfoPktGetterCB = NULL,
                             VoidFromChar *newRFFlowIdSetterCB = NULL,
                             VoidFromRFInfoPkt *newRFInfoPktSetterCB = NULL);
	        InRFInfoPort(std::string port_name,
                             LOGGER_PTR logger,
                             CharFromVoid *newRFFlowIdGetterCB = NULL,
                             RFInfoPktFromVoid *newRFInfoPktGetterCB = NULL,
                             VoidFromChar *newRFFlowIdSetterCB = NULL,
                             VoidFromRFInfoPkt *newRFInfoPktSetterCB = NULL);
	        ~InRFInfoPort();

	        char* rf_flow_id();
	        void rf_flow_id(const char* data);
	        FRONTEND::RFInfoPkt* rfinfo_pkt();
	        void rfinfo_pkt(const FRONTEND::RFInfoPkt& data);
	        void setLogger(LOGGER_PTR newLogger);

			// Assign rf_flow_id callbacks - getters
			template< typename T > inline
			  void setRFFlowIdGetterCB(T &target, char* (T::*func)( void )  ) {
				getRFFlowIdCB =  boost::make_shared< MemberCharFromVoid< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setRFFlowIdGetterCB(T *target, char* (T::*func)( void )  ) {
				getRFFlowIdCB =  boost::make_shared< MemberCharFromVoid< T > >( boost::ref(*target), func );
			};
			void   setRFFlowIdGetterCB( CharFromVoid *newCB );
			void   setRFFlowIdGetterCB( CharFromVoidFn  newCB );

			// and setters
			template< typename T > inline
			  void setRFFlowIdSetterCB(T &target, void (T::*func)( const char* id )  ) {
				setRFFlowIdCB =  boost::make_shared< MemberVoidFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setRFFlowIdSetterCB(T *target, void (T::*func)( const char* id )  ) {
				setRFFlowIdCB =  boost::make_shared< MemberVoidFromChar< T > >( boost::ref(*target), func );
			};
			void   setRFFlowIdSetterCB( VoidFromChar *newCB );
			void   setRFFlowIdSetterCB( VoidFromCharFn  newCB );

			// Assign rfinfo_pkt callbacks - getters
			template< typename T > inline
			  void setRFInfoPktGetterCB(T &target, FRONTEND::RFInfoPkt* (T::*func)( void )  ) {
				getRFInfoPktCB =  boost::make_shared< MemberRFInfoPktFromVoid< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setRFInfoPktGetterCB(T *target, FRONTEND::RFInfoPkt* (T::*func)( void )  ) {
				getRFInfoPktCB =  boost::make_shared< MemberRFInfoPktFromVoid< T > >( boost::ref(*target), func );
			};
			void   setRFInfoPktGetterCB( RFInfoPktFromVoid *newCB );
			void   setRFInfoPktGetterCB( RFInfoPktFromVoidFn  newCB );

			// and setters
			template< typename T > inline
			  void setRFInfoPktSetterCB(T &target, void (T::*func)( const FRONTEND::RFInfoPkt& data )  ) {
				setRFInfoPktCB =  boost::make_shared< MemberVoidFromRFInfoPkt< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setRFInfoPktSetterCB(T *target, void (T::*func)( const FRONTEND::RFInfoPkt& data )  ) {
				setRFInfoPktCB =  boost::make_shared< MemberVoidFromRFInfoPkt< T > >( boost::ref(*target), func );
			};
			void   setRFInfoPktSetterCB( VoidFromRFInfoPkt *newCB );
			void   setRFInfoPktSetterCB( VoidFromRFInfoPktFn  newCB );

	    protected:
	        boost::mutex portAccess;
                LOGGER_PTR logger;

			// Callbacks
			boost::shared_ptr< CharFromVoid > getRFFlowIdCB;
			boost::shared_ptr< RFInfoPktFromVoid > getRFInfoPktCB;
			boost::shared_ptr< VoidFromChar > setRFFlowIdCB;
			boost::shared_ptr< VoidFromRFInfoPkt > setRFInfoPktCB;
	};*/

	// ----------------------------------------------------------------------------------------
	// OutRFInfoPort declaration
	// ----------------------------------------------------------------------------------------
	class OutRFInfoPort : public OutFrontendPort<FRONTEND::RFInfo_var,FRONTEND::RFInfo>
	{
	    public:
	        OutRFInfoPort(std::string port_name);
	        OutRFInfoPort(std::string port_name, LOGGER_PTR logger);
	        ~OutRFInfoPort();

	        char* rf_flow_id();
	        void rf_flow_id(char* data);
	        FRONTEND::RFInfoPkt* rfinfo_pkt();
	        void rfinfo_pkt(FRONTEND::RFInfoPkt data);
	        void setLogger(LOGGER_PTR newLogger);

	    protected:
                LOGGER_PTR logger;

	};

} // end of frontend namespace


#endif
