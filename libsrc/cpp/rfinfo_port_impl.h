#ifndef RFINFO_PORT_H
#define RFINFO_PORT_H

#include "ossie/Port_impl.h"
#include <queue>
#include <list>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/locks.hpp>

class fei_device_rfinfo_in_base;
class fei_device_rfinfo_in_i;

#define CORBA_MAX_TRANSFER_BYTES omniORB::giopMaxMsgSize()

#include <FRONTEND/RFInfo.h>

namespace frontend {

// ----------------------------------------------------------------------------------------
// FRONTEND_RFInfo_In_i declaration
// ----------------------------------------------------------------------------------------
class InRFInfoPort : public POA_FRONTEND::RFInfo, public Port_Provides_base_impl
{
    public:
        InRFInfoPort(std::string port_name);
        ~InRFInfoPort();

        char* rf_flow_id();
        void rf_flow_id(const char* data);
        FRONTEND::RFInfoPkt* rfinfo_pkt();
        void rfinfo_pkt(const FRONTEND::RFInfoPkt& data);

    protected:
        boost::mutex portAccess;
};

}
#endif
