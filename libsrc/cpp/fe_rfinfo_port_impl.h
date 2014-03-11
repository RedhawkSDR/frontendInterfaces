#ifndef FE_RFINFO_PORT_H
#define FE_RFINFO_PORT_H

#include "fe_port_impl.h"

#include <redhawk/FRONTEND/RFInfo.h>
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
    template<typename PortType_var, typename PortType>
    class OutRFInfoPortT : public OutFrontendPort<PortType_var,PortType>
    {
        public:
            OutRFInfoPortT(std::string port_name) : OutFrontendPort<PortType_var, PortType>(port_name)
            {};
            OutRFInfoPortT(std::string port_name, LOGGER_PTR logger) : OutFrontendPort<PortType_var, PortType>(port_name, logger)
            {};
            ~OutRFInfoPortT(){};
            
            std::string rf_flow_id() {
                CORBA::String_var retval;
                std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->rf_flow_id();
                        } catch(...) {
                            LOG_ERROR(OutRFInfoPortT,"Call to rf_flow_id by OutRFInfoPortT failed");
                        }
                    }
                }
                std::string str_retval = ossie::corba::returnString(retval);
                return str_retval;
            };
            void rf_flow_id(std::string &data) {
                std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            ((*i).first)->rf_flow_id(data.c_str());
                        } catch(...) {
                            LOG_ERROR(OutRFInfoPortT,"Call to rf_flow_id by OutRFInfoPortT failed");
                        }
                    }
                }
                return;
            };
            frontend::RFInfoPkt rfinfo_pkt() {
                frontend::RFInfoPkt retval;
                std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            const FRONTEND::RFInfoPkt_var tmp = ((*i).first)->rfinfo_pkt();
                            retval = frontend::returnRFInfoPkt(tmp);
                        } catch(...) {
                            LOG_ERROR(OutRFInfoPortT,"Call to rfinfo_pkt by OutRFInfoPortT failed");
                        }
                    }
                }
                return retval;
            };
            void rfinfo_pkt(frontend::RFInfoPkt data) {
                std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            const FRONTEND::RFInfoPkt_var tmp = frontend::returnRFInfoPkt(data);
                            ((*i).first)->rfinfo_pkt(tmp);
                        } catch(...) {
                            LOG_ERROR(OutRFInfoPortT,"Call to rfinfo_pkt by OutRFInfoPortT failed");
                        }
                    }
                }
                return;
            };
            void setLogger(LOGGER_PTR newLogger) {
                logger = newLogger;
            };
            
        protected:
                LOGGER_PTR logger;

    };
    class OutRFInfoPort : public OutRFInfoPortT<FRONTEND::RFInfo_var,FRONTEND::RFInfo> {
        public:
            OutRFInfoPort(std::string port_name) : OutRFInfoPortT<FRONTEND::RFInfo_var,FRONTEND::RFInfo>(port_name)
            {};
            OutRFInfoPort(std::string port_name, LOGGER_PTR logger) : OutRFInfoPortT<FRONTEND::RFInfo_var,FRONTEND::RFInfo>(port_name, logger)
            {};
    };
    
} // end of frontend namespace


#endif
