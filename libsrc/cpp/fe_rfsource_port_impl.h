#ifndef FE_RFSOURCE_PORT_H
#define FE_RFSOURCE_PORT_H

#include "fe_port_impl.h"

#include <FRONTEND/RFInfo.h>

namespace frontend {

	// ----------------------------------------------------------------------------------------
	// InRFSourcePort declaration
	// ----------------------------------------------------------------------------------------
	class InRFSourcePort : public POA_FRONTEND::RFSource, public Port_Provides_base_impl
	{
	    public:
	        InRFSourcePort(std::string port_name,
	        		RFInfoPktSeqFromVoid *newAvailableRFInputsGetterCB = NULL,
	        		RFInfoPktFromVoid *newCurrentRFInputGetterCB = NULL,
	        		VoidFromRFInfoPktSeq *newAvailableRFInputsSetterCB = NULL,
	        		VoidFromRFInfoPkt *newCurrentRFInputSetterCB = NULL);
	        ~InRFSourcePort();

	        FRONTEND::RFInfoPktSequence* available_rf_inputs();
	        void available_rf_inputs(const FRONTEND::RFInfoPktSequence& data);
	        FRONTEND::RFInfoPkt* current_rf_input();
	        void current_rf_input(const FRONTEND::RFInfoPkt& data);

			// Assign available_rf_inputs callbacks - getters
			template< typename T > inline
			  void setAvailableRFInputsGetterCB(T &target, FRONTEND::RFInfoPktSequence* (T::*func)( void )  ) {
				getAvailableRFInputsCB =  boost::make_shared< MemberRFInfoPktSeqFromVoid< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setAvailableRFInputsGetterCB(T *target, FRONTEND::RFInfoPktSequence* (T::*func)( void )  ) {
				getAvailableRFInputsCB =  boost::make_shared< MemberRFInfoPktSeqFromVoid< T > >( boost::ref(*target), func );
			};
			void   setAvailableRFInputsGetterCB( RFInfoPktSeqFromVoid *newCB );
			void   setAvailableRFInputsGetterCB( RFInfoPktSeqFromVoidFn  newCB );

			// and setters
			template< typename T > inline
			  void setAvailableRFInputsSetterCB(T &target, void (T::*func)( const FRONTEND::RFInfoPktSequence& data )  ) {
				setAvailableRFInputsCB =  boost::make_shared< MemberVoidFromRFInfoPktSeq< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setAvailableRFInputsSetterCB(T *target, void (T::*func)( const FRONTEND::RFInfoPktSequence& data )  ) {
				setAvailableRFInputsCB =  boost::make_shared< MemberVoidFromRFInfoPktSeq< T > >( boost::ref(*target), func );
			};
			void   setAvailableRFInputsSetterCB( VoidFromRFInfoPktSeq *newCB );
			void   setAvailableRFInputsSetterCB( VoidFromRFInfoPktSeqFn  newCB );

			// Assign current_rf_input callbacks - getters
			template< typename T > inline
			  void setCurrentRFInputGetterCB(T &target, FRONTEND::RFInfoPkt* (T::*func)( void )  ) {
				getCurrentRFInputCB =  boost::make_shared< MemberRFInfoPktFromVoid< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setCurrentRFInputGetterCB(T *target, FRONTEND::RFInfoPkt* (T::*func)( void )  ) {
				getCurrentRFInputCB =  boost::make_shared< MemberRFInfoPktFromVoid< T > >( boost::ref(*target), func );
			};
			void   setCurrentRFInputGetterCB( RFInfoPktFromVoid *newCB );
			void   setCurrentRFInputGetterCB( RFInfoPktFromVoidFn  newCB );

			// and setters
			template< typename T > inline
			  void setCurrentRFInputSetterCB(T &target, void (T::*func)( const FRONTEND::RFInfoPkt& data )  ) {
				setCurrentRFInputCB =  boost::make_shared< MemberVoidFromRFInfoPkt< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setCurrentRFInputSetterCB(T *target, void (T::*func)( const FRONTEND::RFInfoPkt& data )  ) {
				setCurrentRFInputCB =  boost::make_shared< MemberVoidFromRFInfoPkt< T > >( boost::ref(*target), func );
			};
			void   setCurrentRFInputSetterCB( VoidFromRFInfoPkt *newCB );
			void   setCurrentRFInputSetterCB( VoidFromRFInfoPktFn  newCB );

	    protected:
	        boost::mutex portAccess;

			// Callbacks
			boost::shared_ptr< RFInfoPktSeqFromVoid > getAvailableRFInputsCB;
			boost::shared_ptr< RFInfoPktFromVoid > getCurrentRFInputCB;
			boost::shared_ptr< VoidFromRFInfoPktSeq > setAvailableRFInputsCB;
			boost::shared_ptr< VoidFromRFInfoPkt > setCurrentRFInputCB;
	};

	// ----------------------------------------------------------------------------------------
	// OutRFSourcePort declaration
	// ----------------------------------------------------------------------------------------
	class OutRFSourcePort : public OutFrontendPort<FRONTEND::RFSource_var,FRONTEND::RFSource>
	{
	    public:
	        OutRFSourcePort(std::string port_name);
	        ~OutRFSourcePort();

	        FRONTEND::RFInfoPktSequence* available_rf_inputs();
	        void available_rf_inputs(const FRONTEND::RFInfoPktSequence& data);
	        FRONTEND::RFInfoPkt* current_rf_input();
	        void current_rf_input(const FRONTEND::RFInfoPkt& data);
	};

} // end of frontend namespace

#endif
