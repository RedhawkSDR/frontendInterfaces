/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    Source: fei_device_rfinfo_in.spd.xml

*******************************************************************************************/

#include "rfinfo_port_impl.h"

namespace frontend {

// ----------------------------------------------------------------------------------------
// FRONTEND_RFInfo_In_i definition
// ----------------------------------------------------------------------------------------
InRFInfoPort::InRFInfoPort(std::string port_name) : 
Port_Provides_base_impl(port_name)
{
}

InRFInfoPort::~InRFInfoPort()
{
}

char* InRFInfoPort::rf_flow_id()
{
    boost::mutex::scoped_lock lock(portAccess);
    char* tmpVal;
    // TODO: Fill in this function

    return CORBA::string_dup(tmpVal);
}

void InRFInfoPort::rf_flow_id(const char* data)
{
    boost::mutex::scoped_lock lock(portAccess);
    // TODO: Fill in this function
}

FRONTEND::RFInfoPkt* InRFInfoPort::rfinfo_pkt()
{
    boost::mutex::scoped_lock lock(portAccess);
    FRONTEND::RFInfoPkt* tmpVal;
    // TODO: Fill in this function

    return tmpVal;
}

void InRFInfoPort::rfinfo_pkt(const FRONTEND::RFInfoPkt& data)
{
    boost::mutex::scoped_lock lock(portAccess);
    // TODO: Fill in this function
}

}

