
#include "fe_rfinfo_port_impl.h"
#include "fe_log.h"

namespace frontend {
    
    // ----------------------------------------------------------------------------------------
    // OutRFInfoPort definition
    // ----------------------------------------------------------------------------------------
    OutRFInfoPort::OutRFInfoPort(std::string port_name) :
        OutFrontendPort<FRONTEND::RFInfo_var,FRONTEND::RFInfo>::OutFrontendPort(port_name){
    }

    OutRFInfoPort::OutRFInfoPort(std::string port_name,
                                     LOGGER_PTR logger) :
        OutFrontendPort<FRONTEND::RFInfo_var,FRONTEND::RFInfo>::OutFrontendPort(port_name,
                                                                                        logger){
    }

    OutRFInfoPort::~OutRFInfoPort(){
    }

    void OutRFInfoPort::setLogger(LOGGER_PTR newLogger)
    {
            logger = newLogger;
        }

    char* OutRFInfoPort::rf_flow_id(){
        char* retval;
        std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;

        boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

        if (active) {
            for (i = outConnections.begin(); i != outConnections.end(); ++i) {
                try {
                    retval = ((*i).first)->rf_flow_id();
                } catch(...) {
                    //LOG_ERROR(OutRFInfoPort,"Call to rf_flow_id by OutRFInfoPort failed");
                }
            }
        }

        return retval;
    }
    void OutRFInfoPort::rf_flow_id(char* data){
        std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;

        boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

        if (active) {
            for (i = outConnections.begin(); i != outConnections.end(); ++i) {
                try {
                    ((*i).first)->rf_flow_id(data);
                } catch(...) {
                    //LOG_ERROR(OutRFInfoPort,"Call to rf_flow_id by OutRFInfoPort failed");
                }
            }
        }
    }
    FRONTEND::RFInfoPkt* OutRFInfoPort::rfinfo_pkt(){
        FRONTEND::RFInfoPkt* retval;
        std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;

        boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

        if (active) {
            for (i = outConnections.begin(); i != outConnections.end(); ++i) {
                try {
                    retval = ((*i).first)->rfinfo_pkt();
                } catch(...) {
                    //LOG_ERROR(OutRFInfoPort,"Call to rfinfo_pkt by OutRFInfoPort failed");
                }
            }
        }

        return retval;
    }
    void OutRFInfoPort::rfinfo_pkt(FRONTEND::RFInfoPkt data){
        std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;

        boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

        if (active) {
            for (i = outConnections.begin(); i != outConnections.end(); ++i) {
                try {
                    ((*i).first)->rfinfo_pkt(data);
                } catch(...) {
                    //LOG_ERROR(OutRFInfoPort,"Call to rfinfo_pkt by OutRFInfoPort failed");
                }
            }
        }
    }

} // end of frontend namespace


