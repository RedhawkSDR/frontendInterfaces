
#include "fe_navdata_port_impl.h"
#include "fe_log.h"

namespace frontend {

	// ----------------------------------------------------------------------------------------
	// InNavDataPort definition
	// ----------------------------------------------------------------------------------------
	InNavDataPort::InNavDataPort(std::string port_name,
		NavPktFromVoid *newNavPktGetterCB,
		VoidFromNavPkt *newNavPktSetterCB) :
	Port_Provides_base_impl(port_name),
	getNavPktCB(),
	setNavPktCB()
	{
		if ( newNavPktGetterCB ) {
			getNavPktCB = boost::shared_ptr< NavPktFromVoid >( newNavPktGetterCB, null_deleter());
		}
		if ( newNavPktSetterCB ) {
			setNavPktCB = boost::shared_ptr< VoidFromNavPkt >( newNavPktSetterCB, null_deleter());
		}
	}

	InNavDataPort::InNavDataPort(std::string port_name,
                LOGGER_PTR logger,
		NavPktFromVoid *newNavPktGetterCB,
		VoidFromNavPkt *newNavPktSetterCB) :
	Port_Provides_base_impl(port_name),
	logger(logger),
	getNavPktCB(),
	setNavPktCB()
	{
		if ( newNavPktGetterCB ) {
			getNavPktCB = boost::shared_ptr< NavPktFromVoid >( newNavPktGetterCB, null_deleter());
		}
		if ( newNavPktSetterCB ) {
			setNavPktCB = boost::shared_ptr< VoidFromNavPkt >( newNavPktSetterCB, null_deleter());
		}
	}

	InNavDataPort::~InNavDataPort()
	{
	}

    void InNavDataPort::setLogger(LOGGER_PTR newLogger){
        logger = newLogger;
    }

    FRONTEND::NavigationPacket* InNavDataPort::nav_packet(){
		boost::mutex::scoped_lock lock(portAccess);
		if ( getNavPktCB ) return (*getNavPktCB)();
		else throw FRONTEND::NotSupportedException("nav_packet() IS NOT CURRENTLY SUPPORTED");
    }
    void InNavDataPort::nav_packet(const FRONTEND::NavigationPacket& data){
		boost::mutex::scoped_lock lock(portAccess);
		if ( setNavPktCB ) (*setNavPktCB)(data);
		else throw FRONTEND::NotSupportedException("nav_packet(const FRONTEND::NavigationPacket& data) IS NOT CURRENTLY SUPPORTED");
    }
    //getNavPktCB
	void   InNavDataPort::setNavPktGetterCB( NavPktFromVoid *newCB ){
		getNavPktCB =  boost::shared_ptr< NavPktFromVoid >(newCB, null_deleter());
	}
	void   InNavDataPort::setNavPktGetterCB( NavPktFromVoidFn  newCB ){
		getNavPktCB =  boost::make_shared< StaticNavPktFromVoid >( newCB );
	}

	//setNavPktCB
	void   InNavDataPort::setNavPktSetterCB( VoidFromNavPkt *newCB ){
		setNavPktCB =  boost::shared_ptr< VoidFromNavPkt >(newCB, null_deleter());
	}
	void   InNavDataPort::setNavPktSetterCB( VoidFromNavPktFn  newCB ){
		setNavPktCB =  boost::make_shared< StaticVoidFromNavPkt >( newCB );
	}

	// ----------------------------------------------------------------------------------------
	// OutNavDataPort definition
	// ----------------------------------------------------------------------------------------
	OutNavDataPort::OutNavDataPort(std::string port_name) :
			OutFrontendPort<FRONTEND::NavData_var,FRONTEND::NavData>::OutFrontendPort(port_name)
		{
		}

	OutNavDataPort::OutNavDataPort(std::string port_name,
                                       LOGGER_PTR logger) :
			OutFrontendPort<FRONTEND::NavData_var,FRONTEND::NavData>::OutFrontendPort(port_name,
                                                                                                  logger)
		{
		}

	OutNavDataPort::~OutNavDataPort()
		{
		}

        void OutNavDataPort::setLogger(LOGGER_PTR newLogger){
            logger = newLogger;
        }

	FRONTEND::NavigationPacket* OutNavDataPort::nav_packet()
	{
		FRONTEND::NavigationPacket* retval;
		std::vector < std::pair < FRONTEND::NavData_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					retval = ((*i).first)->nav_packet();
				} catch(...) {
					//LOG_ERROR(OutNavDataPort,"Call to nav_packet by OutNavDataPort failed");
				}
			}
		}

		return retval;
	}

	void OutNavDataPort::nav_packet(const FRONTEND::NavigationPacket& data)
	{
		std::vector < std::pair < FRONTEND::NavData_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					((*i).first)->nav_packet(data);
				} catch(...) {
					//LOG_ERROR(OutNavDataPort,"Call to nav_packet by OutNavDataPort failed");
				}
			}
		}

		return;
	}

} // end of frontend namespace
