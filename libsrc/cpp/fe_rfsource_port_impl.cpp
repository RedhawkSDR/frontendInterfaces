
#include "fe_rfsource_port_impl.h"
#include "fe_log.h"

namespace frontend {

    // ----------------------------------------------------------------------------------------
    // OutRFSourcePort definition
    // ----------------------------------------------------------------------------------------
    OutRFSourcePort::OutRFSourcePort(std::string port_name) :
        OutFrontendPort<FRONTEND::RFSource_var,FRONTEND::RFSource>::OutFrontendPort(port_name)
    {
    }

    OutRFSourcePort::OutRFSourcePort(std::string port_name,
                                         LOGGER_PTR logger) :
        OutFrontendPort<FRONTEND::RFSource_var,FRONTEND::RFSource>::OutFrontendPort(port_name,
                                                                                            logger)
    {
    }

    OutRFSourcePort::~OutRFSourcePort()
    {
    }

    void OutRFSourcePort::setLogger(LOGGER_PTR newLogger)
        {
            logger = newLogger;
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
                    //LOG_ERROR(InRFSourcePort,"Call to available_rf_inputs by InRFSourcePort failed");
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
                    //LOG_ERROR(InRFSourcePort,"Call to available_rf_inputs by InRFSourcePort failed");
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
                    //LOG_ERROR(InRFSourcePort,"Call to current_rf_input by InRFSourcePort failed");
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
                    //LOG_ERROR(InRFSourcePort,"Call to current_rf_input by InRFSourcePort failed");
                }
            }
        }

        return;
    }
} // end of frontend namespace
