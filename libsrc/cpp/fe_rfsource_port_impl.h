#ifndef FE_RFSOURCE_PORT_H
#define FE_RFSOURCE_PORT_H

#include "fe_port_impl.h"

#include <redhawk/FRONTEND/RFInfo.h>
#include "fe_types.h"

namespace frontend {
    
    class rfsource_delegation {
        public:
            virtual std::vector<RFInfoPkt> get_available_rf_inputs(std::string& port_name) = 0;
            virtual void set_available_rf_inputs(std::string& port_name, std::vector<RFInfoPkt> &inputs) = 0;
            virtual RFInfoPkt get_current_rf_input(std::string& port_name) = 0;
            virtual void set_current_rf_input(std::string& port_name, const RFInfoPkt &input) = 0;
    };
    
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
                std::vector<frontend::RFInfoPkt> retval = this->parent->get_available_rf_inputs(this->name);
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
                this->parent->set_available_rf_inputs(this->name, inputs);
            };
            FRONTEND::RFInfoPkt* current_rf_input() {
                boost::mutex::scoped_lock lock(this->portAccess);
                frontend::RFInfoPkt retval = this->parent->get_current_rf_input(this->name);
                FRONTEND::RFInfoPkt* tmpVal = frontend::returnRFInfoPkt(retval);
                return tmpVal;
            };
            void current_rf_input( const FRONTEND::RFInfoPkt& data) {
                boost::mutex::scoped_lock lock(this->portAccess);
                frontend::RFInfoPkt input = frontend::returnRFInfoPkt(data);
                this->parent->set_current_rf_input(this->name, input);
            };
            
        protected:
            rfsource_delegation *parent;
            boost::mutex portAccess;
    };
    // ----------------------------------------------------------------------------------------
    // OutRFSourcePort declaration
    // ----------------------------------------------------------------------------------------
    class OutRFSourcePort : public OutFrontendPort<FRONTEND::RFSource_var,FRONTEND::RFSource>
    {
        public:
            OutRFSourcePort(std::string port_name);
            OutRFSourcePort(std::string port_name, LOGGER_PTR logger);
            ~OutRFSourcePort();

            FRONTEND::RFInfoPktSequence* available_rf_inputs();
            void available_rf_inputs(const FRONTEND::RFInfoPktSequence& data);
            FRONTEND::RFInfoPkt* current_rf_input();
            void current_rf_input(const FRONTEND::RFInfoPkt& data);
                void setLogger(LOGGER_PTR newLogger);

        protected:
                LOGGER_PTR logger;
    };

} // end of frontend namespace

#endif
