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
	        InGPSPort(std::string port_name,
	        		GPSInfoFromVoid *newGPSInfoGetterCB = NULL,
	        		GpsTimePosFromVoid *newGpsTimePosGetterCB = NULL,
	        		VoidFromGPSInfo *newGPSInfoSetterCB = NULL,
	        		VoidFromGpsTimePos *newGpsTimePosSetterCB = NULL);
	        ~InGPSPort();

	        FRONTEND::GPSInfo* gps_info();
	        void gps_info(const FRONTEND::GPSInfo& data);
	        FRONTEND::GpsTimePos* gps_time_pos();
	        void gps_time_pos(const FRONTEND::GpsTimePos& data);

			// Assign gps_info callbacks - getters
			template< typename T > inline
			  void setGPSInfoGetterCB(T &target, FRONTEND::GPSInfo* (T::*func)( void )  ) {
				getGPSInfoCB =  boost::make_shared< MemberGPSInfoFromVoid< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setGPSInfoGetterCB(T *target, FRONTEND::GPSInfo* (T::*func)( void )  ) {
				getGPSInfoCB =  boost::make_shared< MemberGPSInfoFromVoid< T > >( boost::ref(*target), func );
			};
			void   setGPSInfoGetterCB( GPSInfoFromVoid *newCB );
			void   setGPSInfoGetterCB( GPSInfoFromVoidFn  newCB );

			// and setters
			template< typename T > inline
			  void setGPSInfoSetterCB(T &target, void (T::*func)( const FRONTEND::GPSInfo& data )  ) {
				setGPSInfoCB =  boost::make_shared< MemberVoidFromGPSInfo< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setGPSInfoSetterCB(T *target, void (T::*func)( const FRONTEND::GPSInfo& data )  ) {
				setGPSInfoCB =  boost::make_shared< MemberVoidFromGPSInfo< T > >( boost::ref(*target), func );
			};
			void   setGPSInfoSetterCB( VoidFromGPSInfo *newCB );
			void   setGPSInfoSetterCB( VoidFromGPSInfoFn  newCB );

			// Assign gps_time_pos callbacks - getters
			template< typename T > inline
			  void setGpsTimePosGetterCB(T &target, FRONTEND::GpsTimePos* (T::*func)( void )  ) {
				getGpsTimePosCB =  boost::make_shared< MemberGpsTimePosFromVoid< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setGpsTimePosGetterCB(T *target, FRONTEND::GpsTimePos* (T::*func)( void )  ) {
				getGpsTimePosCB =  boost::make_shared< MemberGpsTimePosFromVoid< T > >( boost::ref(*target), func );
			};
			void   setGpsTimePosGetterCB( GpsTimePosFromVoid *newCB );
			void   setGpsTimePosGetterCB( GpsTimePosFromVoidFn  newCB );

			// and setters
			template< typename T > inline
			  void setGpsTimePosSetterCB(T &target, void (T::*func)( const FRONTEND::GpsTimePos& data )  ) {
				setGpsTimePosCB =  boost::make_shared< MemberVoidFromGpsTimePos< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setGpsTimePosSetterCB(T *target, void (T::*func)( const FRONTEND::GpsTimePos& data )  ) {
				setGpsTimePosCB =  boost::make_shared< MemberVoidFromGpsTimePos< T > >( boost::ref(*target), func );
			};
			void   setGpsTimePosSetterCB( VoidFromGpsTimePos *newCB );
			void   setGpsTimePosSetterCB( VoidFromGpsTimePosFn  newCB );

	    protected:
	        boost::mutex portAccess;

			// Callbacks
			boost::shared_ptr< GPSInfoFromVoid > getGPSInfoCB;
			boost::shared_ptr< GpsTimePosFromVoid > getGpsTimePosCB;
			boost::shared_ptr< VoidFromGPSInfo > setGPSInfoCB;
			boost::shared_ptr< VoidFromGpsTimePos > setGpsTimePosCB;
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
	        void gps_info(const FRONTEND::GPSInfo& data);
	        FRONTEND::GpsTimePos* gps_time_pos();
	        void gps_time_pos(const FRONTEND::GpsTimePos& data);
	};

} // end of frontend namespace


#endif
