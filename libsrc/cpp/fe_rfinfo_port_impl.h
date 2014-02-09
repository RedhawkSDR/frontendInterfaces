#ifndef FE_RFINFO_PORT_H
#define FE_RFINFO_PORT_H

#include "fe_port_impl.h"

#include <FRONTEND/RFInfo.h>
#include "fe_types.h"

namespace frontend {
    
    class rfinfo_delegation {
        public:
            virtual std::string get_rf_flow_id(std::string& port_name) = 0;
            virtual void set_rf_flow_id(std::string& port_name, const std::string& id) = 0;
            virtual RFInfoPkt get_rfinfo_pkt(std::string& port_name) = 0;
            virtual void set_rfinfo_pkt(std::string& port_name, const RFInfoPkt &pkt) = 0;
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
