
#include "fe_rfsource_port_impl.h"

namespace frontend {

    // ----------------------------------------------------------------------------------------
    // OutRFSourcePort definition
    // ----------------------------------------------------------------------------------------
    OutRFSourcePort::OutRFSourcePort(std::string port_name) :
        OutFrontendPort<FRONTEND::RFSource_var,FRONTEND::RFSource>::OutFrontendPort(port_name)
    {
    }

    OutRFSourcePort::~OutRFSourcePort()
    {
    }

    FRONTEND::RFInfoPktSequence* OutRFSourcePort::available_rf_inputs()
    {
        FRONTEND::RFInfoPktSequence* retval;
        std::vector < std::pair < FRONTEND::RFSource_var, std::string > >::iterator i;

        boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

        if (active) {
            for (i = outConnections.begin(); i != outConnections.end(); ++i) {
                try {
                    retval = ((*i).first)->available_rf_inputs();
                } catch(...) {
                }
            }
        }

        return retval;
    }

    void OutRFSourcePort::available_rf_inputs(const FRONTEND::RFInfoPktSequence& data)
    {
        std::vector < std::pair < FRONTEND::RFSource_var, std::string > >::iterator i;

        boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

        if (active) {
            for (i = outConnections.begin(); i != outConnections.end(); ++i) {
                try {
                    ((*i).first)->available_rf_inputs(data);
                } catch(...) {
                }
            }
        }

        return;
    }

    FRONTEND::RFInfoPkt* OutRFSourcePort::current_rf_input()
    {
        FRONTEND::RFInfoPkt* retval;
        std::vector < std::pair < FRONTEND::RFSource_var, std::string > >::iterator i;

        boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

        if (active) {
            for (i = outConnections.begin(); i != outConnections.end(); ++i) {
                try {
                    retval = ((*i).first)->current_rf_input();
                } catch(...) {
                }
            }
        }

        return retval;
    }

    void OutRFSourcePort::current_rf_input(const FRONTEND::RFInfoPkt& data)
    {
        std::vector < std::pair < FRONTEND::RFSource_var, std::string > >::iterator i;

        boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

        if (active) {
            for (i = outConnections.begin(); i != outConnections.end(); ++i) {
                try {
                    ((*i).first)->current_rf_input(data);
                } catch(...) {
                }
            }
        }

        return;
    }
} // end of frontend namespace
