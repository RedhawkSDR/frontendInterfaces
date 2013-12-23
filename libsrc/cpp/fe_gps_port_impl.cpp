
#include "fe_gps_port_impl.h"
#include "fe_log.h"

namespace frontend {

	// ----------------------------------------------------------------------------------------
	// InGPSPort definition
	// ----------------------------------------------------------------------------------------
	InGPSPort::InGPSPort(std::string port_name,
                LOGGER_PTR logger,
    		GPSInfoFromVoid *newGPSInfoGetterCB,
    		GpsTimePosFromVoid *newGpsTimePosGetterCB,
    		VoidFromGPSInfo *newGPSInfoSetterCB,
    		VoidFromGpsTimePos *newGpsTimePosSetterCB) :
	Port_Provides_base_impl(port_name),
        logger(logger),
	getGPSInfoCB(),
	getGpsTimePosCB(),
	setGPSInfoCB(),
	setGpsTimePosCB()
	{
		if ( newGPSInfoGetterCB ) {
			getGPSInfoCB = boost::shared_ptr< GPSInfoFromVoid >( newGPSInfoGetterCB, null_deleter());
		}
		if ( newGpsTimePosGetterCB ) {
			getGpsTimePosCB = boost::shared_ptr< GpsTimePosFromVoid >( newGpsTimePosGetterCB, null_deleter());
		}
		if ( newGPSInfoSetterCB ) {
			setGPSInfoCB = boost::shared_ptr< VoidFromGPSInfo >( newGPSInfoSetterCB, null_deleter());
		}
		if ( newGpsTimePosSetterCB ) {
			setGpsTimePosCB = boost::shared_ptr< VoidFromGpsTimePos >( newGpsTimePosSetterCB, null_deleter());
		}
	}

	InGPSPort::~InGPSPort()
	{
	}

    void InGPSPort::setLogger(LOGGER_PTR newLogger){
        logger = newLogger;
    }

    FRONTEND::GPSInfo* InGPSPort::gps_info(){
		boost::mutex::scoped_lock lock(portAccess);
		if ( getGPSInfoCB ) return (*getGPSInfoCB)();
		else throw FRONTEND::NotSupportedException("gps_info() IS NOT CURRENTLY SUPPORTED");
    }
    void InGPSPort::gps_info(const FRONTEND::GPSInfo& data){
		boost::mutex::scoped_lock lock(portAccess);
		if ( setGPSInfoCB ) return (*setGPSInfoCB)(data);
		else throw FRONTEND::NotSupportedException("gps_info(const FRONTEND::GPSInfo& data) IS NOT CURRENTLY SUPPORTED");
    }
    FRONTEND::GpsTimePos* InGPSPort::gps_time_pos(){
		boost::mutex::scoped_lock lock(portAccess);
		if ( getGpsTimePosCB ) (*getGpsTimePosCB)();
		else throw FRONTEND::NotSupportedException("gps_time_pos() IS NOT CURRENTLY SUPPORTED");
    }
    void InGPSPort::gps_time_pos(const FRONTEND::GpsTimePos& data){
		boost::mutex::scoped_lock lock(portAccess);
		if ( setGpsTimePosCB ) (*setGpsTimePosCB)(data);
		else throw FRONTEND::NotSupportedException("gps_time_pos(const FRONTEND::GpsTimePos& data) IS NOT CURRENTLY SUPPORTED");
    }

    //getGPSInfoCB
	void   InGPSPort::setGPSInfoGetterCB( GPSInfoFromVoid *newCB ){
		getGPSInfoCB =  boost::shared_ptr< GPSInfoFromVoid >(newCB, null_deleter());
	}
	void   InGPSPort::setGPSInfoGetterCB( GPSInfoFromVoidFn  newCB ){
		getGPSInfoCB =  boost::make_shared< StaticGPSInfoFromVoid >( newCB );
	}

    //setGPSInfoCB
	void   InGPSPort::setGPSInfoSetterCB( VoidFromGPSInfo *newCB ){
		setGPSInfoCB =  boost::shared_ptr< VoidFromGPSInfo >(newCB, null_deleter());
	}
	void   InGPSPort::setGPSInfoSetterCB( VoidFromGPSInfoFn  newCB ){
		setGPSInfoCB =  boost::make_shared< StaticVoidFromGPSInfo >( newCB );
	}

	//getGpsTimePosCB
	void   InGPSPort::setGpsTimePosGetterCB( GpsTimePosFromVoid *newCB ){
		getGpsTimePosCB =  boost::shared_ptr< GpsTimePosFromVoid >(newCB, null_deleter());
	}
	void   InGPSPort::setGpsTimePosGetterCB( GpsTimePosFromVoidFn  newCB ){
		getGpsTimePosCB =  boost::make_shared< StaticGpsTimePosFromVoid >( newCB );
	}

	//setGpsTimePosCB
	void   InGPSPort::setGpsTimePosSetterCB( VoidFromGpsTimePos *newCB ){
		setGpsTimePosCB =  boost::shared_ptr< VoidFromGpsTimePos >(newCB, null_deleter());
	}
	void   InGPSPort::setGpsTimePosSetterCB( VoidFromGpsTimePosFn  newCB ){
		setGpsTimePosCB =  boost::make_shared< StaticVoidFromGpsTimePos >( newCB );
	}


	// ----------------------------------------------------------------------------------------
	// OutGPSPort definition
	// ----------------------------------------------------------------------------------------
	OutGPSPort::OutGPSPort(std::string port_name,
                               LOGGER_PTR logger) :
		OutFrontendPort<FRONTEND::GPS_var,FRONTEND::GPS>::OutFrontendPort(port_name, 
                                                                                  logger)
	{
	}

	OutGPSPort::~OutGPSPort()
	{
	}

	FRONTEND::GPSInfo* OutGPSPort::gps_info()
	{
		FRONTEND::GPSInfo* retval;
		std::vector < std::pair < FRONTEND::GPS_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					retval = ((*i).first)->gps_info();
				} catch(...) {
					//LOG_ERROR(OutGPSPort,"Call to gps_info by OutGPSPort failed");
				}
			}
		}

		return retval;
	}

	void OutGPSPort::gps_info(const FRONTEND::GPSInfo& data)
	{
		std::vector < std::pair < FRONTEND::GPS_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					((*i).first)->gps_info(data);
				} catch(...) {
					//LOG_ERROR(OutGPSPort,"Call to gps_info by OutGPSPort failed");
				}
			}
		}

		return;
	}

	FRONTEND::GpsTimePos* OutGPSPort::gps_time_pos()
	{
		FRONTEND::GpsTimePos* retval;
		std::vector < std::pair < FRONTEND::GPS_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					retval = ((*i).first)->gps_time_pos();
				} catch(...) {
					//LOG_ERROR(OutGPSPort,"Call to gps_time_pos by OutGPSPort failed");
				}
			}
		}

		return retval;
	}

	void OutGPSPort::gps_time_pos(const FRONTEND::GpsTimePos& data)
	{
		std::vector < std::pair < FRONTEND::GPS_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					((*i).first)->gps_time_pos(data);
				} catch(...) {
					//LOG_ERROR(OutGPSPort,"Call to gps_time_pos by OutGPSPort failed");
				}
			}
		}

		return;
	}

} // end of frontend namespace
