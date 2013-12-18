#ifndef FE_GPS_PORT_H
#define FE_GPS_PORT_H

#include "fe_port_impl.h"

#include <FRONTEND/GPS.h>

namespace frontend {

	// ----------------------------------------------------------------------------------------
	// InGPSPort declaration
	// ----------------------------------------------------------------------------------------
	class InGPSPort : public POA_FRONTEND::GPS, public Port_Provides_base_impl
	{
	    public:
	        InGPSPort(std::string port_name);
	        ~InGPSPort();

	        FRONTEND::GPSInfo* gps_info();
	        void gps_info(FRONTEND::GPSInfo data);
	        FRONTEND::GpsTimePos* gps_time_pos();
	        void gps_time_pos(FRONTEND::GpsTimePos data);

	    protected:
	        boost::mutex portAccess;
	};

	// ----------------------------------------------------------------------------------------
	// OutGPSPort declaration
	// ----------------------------------------------------------------------------------------
	class OutGPSPort : OutFrontendPort<FRONTEND::GPS_var,FRONTEND::GPS>
	{
	    public:
	        OutGPSPort(std::string port_name);
	        ~OutGPSPort();

	        FRONTEND::GPSInfo* gps_info();
	        void gps_info(FRONTEND::GPSInfo data);
	        FRONTEND::GpsTimePos* gps_time_pos();
	        void gps_time_pos(FRONTEND::GpsTimePos data);
	};

} // end of frontend namespace


#endif
