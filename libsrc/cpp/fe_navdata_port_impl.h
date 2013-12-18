#ifndef FE_NAVDATA_PORT_H
#define FE_NAVDATA_PORT_H

#include "fe_port_impl.h"

#include <FRONTEND/NavigationData.h>

namespace frontend {

	// ----------------------------------------------------------------------------------------
	// InNavDataPort declaration
	// ----------------------------------------------------------------------------------------
	class InNavDataPort : public POA_FRONTEND::NavData, public Port_Provides_base_impl
	{
	    public:
	        InNavDataPort(std::string port_name);
	        ~InNavDataPort();

	        FRONTEND::NavigationPacket* nav_packet();
	        void nav_packet(FRONTEND::NavigationPacket data);

	    protected:
	        boost::mutex portAccess;
	};

	// ----------------------------------------------------------------------------------------
	// OutNavDataPort declaration
	// ----------------------------------------------------------------------------------------
	class OutNavDataPort : public OutFrontendPort<FRONTEND::NavData_var,FRONTEND::NavData>
	{
	    public:
	        OutNavDataPort(std::string port_name);
	        ~OutNavDataPort();

	        FRONTEND::NavigationPacket* nav_packet();
	        void nav_packet(FRONTEND::NavigationPacket data);
	};

} // end of frontend namespace


#endif
