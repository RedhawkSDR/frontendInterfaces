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
	        InNavDataPort(std::string port_name,
	    			NavPktFromVoid *newNavPktGetterCB = NULL,
	    			VoidFromNavPkt *newNavPktSetterCB = NULL);
	        ~InNavDataPort();

	        FRONTEND::NavigationPacket* nav_packet();
	        void nav_packet(const FRONTEND::NavigationPacket& data);

			// Assign current_rf_input callbacks - getters
			template< typename T > inline
			  void setNavPktGetterCB(T &target, FRONTEND::NavigationPacket* (T::*func)( void )  ) {
				getNavPktCB =  boost::make_shared< MemberNavPktFromVoid< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setNavPktGetterCB(T *target, FRONTEND::NavigationPacket* (T::*func)( void )  ) {
				getNavPktCB =  boost::make_shared< MemberNavPktFromVoid< T > >( boost::ref(*target), func );
			};
			void   setNavPktGetterCB( NavPktFromVoid *newCB );
			void   setNavPktGetterCB( NavPktFromVoidFn  newCB );

			// and setters
			template< typename T > inline
			  void setNavPktSetterCB(T &target, void (T::*func)( const FRONTEND::NavigationPacket& data )  ) {
				setNavPktCB =  boost::make_shared< MemberVoidFromNavPkt< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setNavPktSetterCB(T *target, void (T::*func)( const FRONTEND::NavigationPacket& data )  ) {
				setNavPktCB =  boost::make_shared< MemberVoidFromNavPkt< T > >( boost::ref(*target), func );
			};
			void   setNavPktSetterCB( VoidFromNavPkt *newCB );
			void   setNavPktSetterCB( VoidFromNavPktFn  newCB );

	    protected:
	        boost::mutex portAccess;

			// Callbacks
			boost::shared_ptr< NavPktFromVoid > getNavPktCB;
			boost::shared_ptr< VoidFromNavPkt > setNavPktCB;
	};

	// ----------------------------------------------------------------------------------------
	// OutNavDataPort declaration
	// ----------------------------------------------------------------------------------------
	class OutNavDataPort : public OutFrontendPort<FRONTEND::NavData_var,FRONTEND::NavData>
	{
	    public:
	        OutNavDataPort(std::string port_name, LOGGER_PTR logger);
	        ~OutNavDataPort();

	        FRONTEND::NavigationPacket* nav_packet();
	        void nav_packet(const FRONTEND::NavigationPacket& data);
	};

} // end of frontend namespace


#endif
