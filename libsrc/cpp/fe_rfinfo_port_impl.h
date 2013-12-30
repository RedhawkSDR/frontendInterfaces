#ifndef FE_RFINFO_PORT_H
#define FE_RFINFO_PORT_H

#include "fe_port_impl.h"

#include <FRONTEND/RFInfo.h>

namespace frontend {

	// ----------------------------------------------------------------------------------------
	// InRFInfoPort declaration
	// ----------------------------------------------------------------------------------------
	class InRFInfoPort : public POA_FRONTEND::RFInfo, public Port_Provides_base_impl
	{
	    public:
	        InRFInfoPort(std::string port_name,
                             CharFromVoid *newRFFlowIdGetterCB = NULL,
                             RFInfoPktFromVoid *newRFInfoPktGetterCB = NULL,
                             VoidFromChar *newRFFlowIdSetterCB = NULL,
                             VoidFromRFInfoPkt *newRFInfoPktSetterCB = NULL);
	        InRFInfoPort(std::string port_name,
                             LOGGER_PTR logger,
                             CharFromVoid *newRFFlowIdGetterCB = NULL,
                             RFInfoPktFromVoid *newRFInfoPktGetterCB = NULL,
                             VoidFromChar *newRFFlowIdSetterCB = NULL,
                             VoidFromRFInfoPkt *newRFInfoPktSetterCB = NULL);
	        ~InRFInfoPort();

	        char* rf_flow_id();
	        void rf_flow_id(const char* data);
	        FRONTEND::RFInfoPkt* rfinfo_pkt();
	        void rfinfo_pkt(const FRONTEND::RFInfoPkt& data);
	        void setLogger(LOGGER_PTR newLogger);

			// Assign rf_flow_id callbacks - getters
			template< typename T > inline
			  void setRFFlowIdGetterCB(T &target, char* (T::*func)( void )  ) {
				getRFFlowIdCB =  boost::make_shared< MemberCharFromVoid< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setRFFlowIdGetterCB(T *target, char* (T::*func)( void )  ) {
				getRFFlowIdCB =  boost::make_shared< MemberCharFromVoid< T > >( boost::ref(*target), func );
			};
			void   setRFFlowIdGetterCB( CharFromVoid *newCB );
			void   setRFFlowIdGetterCB( CharFromVoidFn  newCB );

			// and setters
			template< typename T > inline
			  void setRFFlowIdSetterCB(T &target, void (T::*func)( const char* id )  ) {
				setRFFlowIdCB =  boost::make_shared< MemberVoidFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setRFFlowIdSetterCB(T *target, void (T::*func)( const char* id )  ) {
				setRFFlowIdCB =  boost::make_shared< MemberVoidFromChar< T > >( boost::ref(*target), func );
			};
			void   setRFFlowIdSetterCB( VoidFromChar *newCB );
			void   setRFFlowIdSetterCB( VoidFromCharFn  newCB );

			// Assign rfinfo_pkt callbacks - getters
			template< typename T > inline
			  void setRFInfoPktGetterCB(T &target, FRONTEND::RFInfoPkt* (T::*func)( void )  ) {
				getRFInfoPktCB =  boost::make_shared< MemberRFInfoPktFromVoid< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setRFInfoPktGetterCB(T *target, FRONTEND::RFInfoPkt* (T::*func)( void )  ) {
				getRFInfoPktCB =  boost::make_shared< MemberRFInfoPktFromVoid< T > >( boost::ref(*target), func );
			};
			void   setRFInfoPktGetterCB( RFInfoPktFromVoid *newCB );
			void   setRFInfoPktGetterCB( RFInfoPktFromVoidFn  newCB );

			// and setters
			template< typename T > inline
			  void setRFInfoPktSetterCB(T &target, void (T::*func)( const FRONTEND::RFInfoPkt& data )  ) {
				setRFInfoPktCB =  boost::make_shared< MemberVoidFromRFInfoPkt< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setRFInfoPktSetterCB(T *target, void (T::*func)( const FRONTEND::RFInfoPkt& data )  ) {
				setRFInfoPktCB =  boost::make_shared< MemberVoidFromRFInfoPkt< T > >( boost::ref(*target), func );
			};
			void   setRFInfoPktSetterCB( VoidFromRFInfoPkt *newCB );
			void   setRFInfoPktSetterCB( VoidFromRFInfoPktFn  newCB );

	    protected:
	        boost::mutex portAccess;
                LOGGER_PTR logger;

			// Callbacks
			boost::shared_ptr< CharFromVoid > getRFFlowIdCB;
			boost::shared_ptr< RFInfoPktFromVoid > getRFInfoPktCB;
			boost::shared_ptr< VoidFromChar > setRFFlowIdCB;
			boost::shared_ptr< VoidFromRFInfoPkt > setRFInfoPktCB;
	};

	// ----------------------------------------------------------------------------------------
	// OutRFInfoPort declaration
	// ----------------------------------------------------------------------------------------
	class OutRFInfoPort : public OutFrontendPort<FRONTEND::RFInfo_var,FRONTEND::RFInfo>
	{
	    public:
	        OutRFInfoPort(std::string port_name);
	        OutRFInfoPort(std::string port_name, LOGGER_PTR logger);
	        ~OutRFInfoPort();

	        char* rf_flow_id();
	        void rf_flow_id(char* data);
	        FRONTEND::RFInfoPkt* rfinfo_pkt();
	        void rfinfo_pkt(FRONTEND::RFInfoPkt data);
	        void setLogger(LOGGER_PTR newLogger);

	    protected:
                LOGGER_PTR logger;

	};

} // end of frontend namespace


#endif
