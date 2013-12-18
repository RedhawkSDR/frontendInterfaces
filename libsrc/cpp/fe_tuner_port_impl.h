#ifndef FE_TUNER_PORT_H
#define FE_TUNER_PORT_H

#include "fe_port_impl.h"

#include <FRONTEND/TunerControl.h>

namespace frontend {

	// ----------------------------------------------------------------------------------------
	// InFrontendTunerPort declaration
	// ----------------------------------------------------------------------------------------
	class InFrontendTunerPort : public virtual POA_FRONTEND::FrontendTuner, public Port_Provides_base_impl
	{
		public:
			InFrontendTunerPort(std::string port_name,
				CharFromChar *newTunerTypeGetterCB = NULL,
				BooleanFromChar *newTunerDeviceControlGetterCB = NULL,
				CharFromChar *newTunerGroupIdGetterCB = NULL,
				CharFromChar *newTunerRfFlowIdGetterCB = NULL,
				PropFromChar *newTunerStatusGetterCB = NULL);
			~InFrontendTunerPort();

			char* getTunerType(const char* id);
			CORBA::Boolean getTunerDeviceControl(const char* id);
			char* getTunerGroupId(const char* id);
			char* getTunerRfFlowId(const char* id);
			CF::Properties* getTunerStatus(const char* id);

			// Assign  TunerType callbacks - getters
			template< typename T > inline
			  void setTunerTypeGetterCB(T &target, char* (T::*func)( const char* id)  ) {
				getTunerTypeCB =  boost::make_shared< MemberCharFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerTypeGetterCB(T *target, char* (T::*func)( const char* id)  ) {
				getTunerTypeCB =  boost::make_shared< MemberCharFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerTypeGetterCB( CharFromChar *newCB );
			void   setTunerTypeGetterCB( CharFromCharFn  newCB );

			// Assign  TunerDeviceControl callbacks - getters
			template< typename T > inline
			  void setTunerDeviceControlGetterCB(T &target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerDeviceControlCB =  boost::make_shared< MemberBooleanFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerDeviceControlGetterCB(T *target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerDeviceControlCB =  boost::make_shared< MemberBooleanFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerDeviceControlGetterCB( BooleanFromChar *newCB );
			void   setTunerDeviceControlGetterCB( BooleanFromCharFn  newCB );

			// Assign  TunerGroupId callbacks - getters
			template< typename T > inline
			  void setTunerGroupIdGetterCB(T &target, char* (T::*func)( const char* id)  ) {
				getTunerGroupIdCB =  boost::make_shared< MemberCharFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerGroupIdGetterCB(T *target, char* (T::*func)( const char* id)  ) {
				getTunerGroupIdCB =  boost::make_shared< MemberCharFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerGroupIdGetterCB( CharFromChar *newCB );
			void   setTunerGroupIdGetterCB( CharFromCharFn  newCB );

			// Assign  TunerRfFlowId callbacks - getters
			template< typename T > inline
			  void setTunerRfFlowIdGetterCB(T &target, char* (T::*func)( const char* id)  ) {
				getTunerRfFlowIdCB =  boost::make_shared< MemberCharFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerRfFlowIdGetterCB(T *target, char* (T::*func)( const char* id)  ) {
				getTunerRfFlowIdCB =  boost::make_shared< MemberCharFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerRfFlowIdGetterCB( CharFromChar *newCB );
			void   setTunerRfFlowIdGetterCB( CharFromCharFn  newCB );

			// Assign  TunerStatus callbacks - getters
			template< typename T > inline
			  void setTunerStatusGetterCB(T &target, CF::Properties* (T::*func)( const char* id)  ) {
				getTunerStatusCB =  boost::make_shared< MemberPropFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerStatusGetterCB(T *target, CF::Properties* (T::*func)( const char* id)  ) {
				getTunerStatusCB =  boost::make_shared< MemberPropFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerStatusGetterCB( PropFromChar *newCB );
			void   setTunerStatusGetterCB( PropFromCharFn  newCB );

		protected:
			boost::mutex portAccess;

			// Callbacks
			boost::shared_ptr< CharFromChar > getTunerTypeCB;
			boost::shared_ptr< BooleanFromChar > getTunerDeviceControlCB;
			boost::shared_ptr< CharFromChar > getTunerGroupIdCB;
			boost::shared_ptr< CharFromChar > getTunerRfFlowIdCB;
			boost::shared_ptr< PropFromChar > getTunerStatusCB;
	};

	// ----------------------------------------------------------------------------------------
	// InAnalogTunerPort declaration
	// ----------------------------------------------------------------------------------------
	class InAnalogTunerPort : public virtual POA_FRONTEND::AnalogTuner, public InFrontendTunerPort
	{
		public:
			InAnalogTunerPort(std::string port_name,
				CharFromChar *newTunerTypeGetterCB = NULL,
				BooleanFromChar *newTunerDeviceControlGetterCB = NULL,
				CharFromChar *newTunerGroupIdGetterCB = NULL,
				CharFromChar *newTunerRfFlowIdGetterCB = NULL,
				PropFromChar *newTunerStatusGetterCB = NULL,
				DoubleFromChar *newTunerCenterFrequencyGetterCB = NULL,
				VoidFromCharDouble *newTunerCenterFrequencySetterCB = NULL,
				DoubleFromChar *newTunerBandwidthGetterCB = NULL,
				VoidFromCharDouble *newTunerBandwidthSetterCB = NULL,
				BooleanFromChar *newTunerAgcEnableGetterCB = NULL,
				VoidFromCharBoolean *newTunerAgcEnableSetterCB = NULL,
				FloatFromChar *newTunerGainGetterCB = NULL,
				VoidFromCharFloat *newTunerGainSetterCB = NULL,
				LongFromChar *newTunerReferenceSourceGetterCB = NULL,
				VoidFromCharLong *newTunerReferenceSourceSetterCB = NULL,
				BooleanFromChar *newTunerEnableGetterCB = NULL,
				VoidFromCharBoolean *newTunerEnableSetterCB = NULL);
			~InAnalogTunerPort();

			void setTunerCenterFrequency(const char* id, CORBA::Double freq);
			CORBA::Double getTunerCenterFrequency(const char* id);
			void setTunerBandwidth(const char* id, CORBA::Double bw);
			CORBA::Double getTunerBandwidth(const char* id);
			void setTunerAgcEnable(const char* id, CORBA::Boolean enable);
			CORBA::Boolean getTunerAgcEnable(const char* id);
			void setTunerGain(const char* id, CORBA::Float gain);
			CORBA::Float getTunerGain(const char* id);
			void setTunerReferenceSource(const char* id, CORBA::Long source);
			CORBA::Long getTunerReferenceSource(const char* id);
			void setTunerEnable(const char* id, CORBA::Boolean enable);
			CORBA::Boolean getTunerEnable(const char* id);

			// Assign  TunerCenterFrequency callbacks - getters
			template< typename T > inline
			  void setTunerCenterFrequencyGetterCB(T &target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerCenterFrequencyCB =  boost::make_shared< MemberDoubleFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerCenterFrequencyGetterCB(T *target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerCenterFrequencyCB =  boost::make_shared< MemberDoubleFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerCenterFrequencyGetterCB( DoubleFromChar *newCB );
			void   setTunerCenterFrequencyGetterCB( DoubleFromCharFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerCenterFrequencySetterCB(T &target, void (T::*func)( const char* id, CORBA::Double freq)  ) {
				setTunerCenterFrequencyCB =  boost::make_shared< MemberVoidFromCharDouble< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerCenterFrequencySetterCB(T *target, void (T::*func)( const char* id, CORBA::Double freq)  ) {
				setTunerCenterFrequencyCB =  boost::make_shared< MemberVoidFromCharDouble< T > >( boost::ref(*target), func );
			};
			void   setTunerCenterFrequencySetterCB( VoidFromCharDouble *newCB );
			void   setTunerCenterFrequencySetterCB( VoidFromCharDoubleFn  newCB );

			// Assign  TunerBandwidth callbacks - getters
			template< typename T > inline
			  void setTunerBandwidthGetterCB(T &target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerBandwidthCB =  boost::make_shared< MemberDoubleFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerBandwidthGetterCB(T *target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerBandwidthCB =  boost::make_shared< MemberDoubleFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerBandwidthGetterCB( DoubleFromChar *newCB );
			void   setTunerBandwidthGetterCB( DoubleFromCharFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerBandwidthSetterCB(T &target, void (T::*func)( const char* id, CORBA::Double bw)  ) {
				setTunerBandwidthCB =  boost::make_shared< MemberVoidFromCharDouble< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerBandwidthSetterCB(T *target, void (T::*func)( const char* id, CORBA::Double bw)  ) {
				setTunerBandwidthCB =  boost::make_shared< MemberVoidFromCharDouble< T > >( boost::ref(*target), func );
			};
			void   setTunerBandwidthSetterCB( VoidFromCharDouble *newCB );
			void   setTunerBandwidthSetterCB( VoidFromCharDoubleFn  newCB );

			// Assign  TunerAgcEnable callbacks - getters
			template< typename T > inline
			  void setTunerAgcEnableGetterCB(T &target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerAgcEnableCB =  boost::make_shared< MemberBooleanFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerAgcEnableGetterCB(T *target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerAgcEnableCB =  boost::make_shared< MemberBooleanFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerAgcEnableGetterCB( BooleanFromChar *newCB );
			void   setTunerAgcEnableGetterCB( BooleanFromCharFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerAgcEnableSetterCB(T &target, void (T::*func)( const char* id, CORBA::Boolean enable)  ) {
				setTunerAgcEnableCB =  boost::make_shared< MemberVoidFromCharBoolean< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerAgcEnableSetterCB(T *target, void (T::*func)( const char* id, CORBA::Boolean enable)  ) {
				setTunerAgcEnableCB =  boost::make_shared< MemberVoidFromCharBoolean< T > >( boost::ref(*target), func );
			};
			void   setTunerAgcEnableSetterCB( VoidFromCharBoolean *newCB );
			void   setTunerAgcEnableSetterCB( VoidFromCharBooleanFn  newCB );

			// Assign  TunerGain callbacks - getters
			template< typename T > inline
			  void setTunerGainGetterCB(T &target, CORBA::Float (T::*func)( const char* id)  ) {
				getTunerGainCB =  boost::make_shared< MemberFloatFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerGainGetterCB(T *target, CORBA::Float (T::*func)( const char* id)  ) {
				getTunerGainCB =  boost::make_shared< MemberFloatFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerGainGetterCB( FloatFromChar *newCB );
			void   setTunerGainGetterCB( FloatFromCharFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerGainSetterCB(T &target, void (T::*func)( const char* id, CORBA::Float gain)  ) {
				setTunerGainCB =  boost::make_shared< MemberVoidFromCharFloat< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerGainSetterCB(T *target, void (T::*func)( const char* id, CORBA::Float gain)  ) {
				setTunerGainCB =  boost::make_shared< MemberVoidFromCharFloat< T > >( boost::ref(*target), func );
			};
			void   setTunerGainSetterCB( VoidFromCharFloat *newCB );
			void   setTunerGainSetterCB( VoidFromCharFloatFn  newCB );

			// Assign  TunerReferenceSource callbacks - getters
			template< typename T > inline
			  void setTunerReferenceSourceGetterCB(T &target, CORBA::Long (T::*func)( const char* id)  ) {
				getTunerReferenceSourceCB =  boost::make_shared< MemberLongFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerReferenceSourceGetterCB(T *target, CORBA::Long (T::*func)( const char* id)  ) {
				getTunerReferenceSourceCB =  boost::make_shared< MemberLongFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerReferenceSourceGetterCB( LongFromChar *newCB );
			void   setTunerReferenceSourceGetterCB( LongFromCharFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerReferenceSourceSetterCB(T &target, void (T::*func)( const char* id, CORBA::Long source)  ) {
				setTunerReferenceSourceCB =  boost::make_shared< MemberVoidFromCharLong< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerReferenceSourceSetterCB(T *target, void (T::*func)( const char* id, CORBA::Long source)  ) {
				setTunerReferenceSourceCB =  boost::make_shared< MemberVoidFromCharLong< T > >( boost::ref(*target), func );
			};
			void   setTunerReferenceSourceSetterCB( VoidFromCharLong *newCB );
			void   setTunerReferenceSourceSetterCB( VoidFromCharLongFn  newCB );

			// Assign  TunerEnable callbacks - getters
			template< typename T > inline
			  void setTunerEnableGetterCB(T &target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerEnableCB =  boost::make_shared< MemberBooleanFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerEnableGetterCB(T *target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerEnableCB =  boost::make_shared< MemberBooleanFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerEnableGetterCB( BooleanFromChar *newCB );
			void   setTunerEnableGetterCB( BooleanFromCharFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerEnableSetterCB(T &target, void (T::*func)( const char* id, CORBA::Boolean enable)  ) {
				setTunerEnableCB =  boost::make_shared< MemberVoidFromCharBoolean< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerEnableSetterCB(T *target, void (T::*func)( const char* id, CORBA::Boolean enable)  ) {
				setTunerEnableCB =  boost::make_shared< MemberVoidFromCharBoolean< T > >( boost::ref(*target), func );
			};
			void   setTunerEnableSetterCB( VoidFromCharBoolean *newCB );
			void   setTunerEnableSetterCB( VoidFromCharBooleanFn  newCB );

		protected:

			// Callbacks
			boost::shared_ptr< DoubleFromChar > getTunerCenterFrequencyCB;
			boost::shared_ptr< VoidFromCharDouble > setTunerCenterFrequencyCB;
			boost::shared_ptr< DoubleFromChar > getTunerBandwidthCB;
			boost::shared_ptr< VoidFromCharDouble > setTunerBandwidthCB;
			boost::shared_ptr< BooleanFromChar > getTunerAgcEnableCB;
			boost::shared_ptr< VoidFromCharBoolean > setTunerAgcEnableCB;
			boost::shared_ptr< FloatFromChar > getTunerGainCB;
			boost::shared_ptr< VoidFromCharFloat > setTunerGainCB;
			boost::shared_ptr< LongFromChar > getTunerReferenceSourceCB;
			boost::shared_ptr< VoidFromCharLong > setTunerReferenceSourceCB;
			boost::shared_ptr< BooleanFromChar > getTunerEnableCB;
			boost::shared_ptr< VoidFromCharBoolean > setTunerEnableCB;
	};


	// ----------------------------------------------------------------------------------------
	// InDigitalTunerPort declaration
	// ----------------------------------------------------------------------------------------
	class InDigitalTunerPort : public virtual POA_FRONTEND::DigitalTuner, public InAnalogTunerPort
	{
		public:
			InDigitalTunerPort(std::string port_name,
				CharFromChar *newTunerTypeGetterCB = NULL,
				BooleanFromChar *newTunerDeviceControlGetterCB = NULL,
				CharFromChar *newTunerGroupIdGetterCB = NULL,
				CharFromChar *newTunerRfFlowIdGetterCB = NULL,
				PropFromChar *newTunerStatusGetterCB = NULL,
				DoubleFromChar *newTunerCenterFrequencyGetterCB = NULL,
				VoidFromCharDouble *newTunerCenterFrequencySetterCB = NULL,
				DoubleFromChar *newTunerBandwidthGetterCB = NULL,
				VoidFromCharDouble *newTunerBandwidthSetterCB = NULL,
				BooleanFromChar *newTunerAgcEnableGetterCB = NULL,
				VoidFromCharBoolean *newTunerAgcEnableSetterCB = NULL,
				FloatFromChar *newTunerGainGetterCB = NULL,
				VoidFromCharFloat *newTunerGainSetterCB = NULL,
				LongFromChar *newTunerReferenceSourceGetterCB = NULL,
				VoidFromCharLong *newTunerReferenceSourceSetterCB = NULL,
				BooleanFromChar *newTunerEnableGetterCB = NULL,
				VoidFromCharBoolean *newTunerEnableSetterCB = NULL,
				DoubleFromChar *newTunerOutputSampleRateGetterCB = NULL,
				VoidFromCharDouble *newTunerOutputSampleRateSetterCB = NULL);//, USRP_UHD_base *_parent);
			~InDigitalTunerPort();

			void setTunerOutputSampleRate(const char* id, CORBA::Double sr);
			CORBA::Double getTunerOutputSampleRate(const char* id);

			// Assign  TunerOutputSampleRate callbacks - getters
			template< typename T > inline
			  void setTunerOutputSampleRateGetterCB(T &target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerOutputSampleRateCB =  boost::make_shared< MemberDoubleFromChar< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerOutputSampleRateGetterCB(T *target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerOutputSampleRateCB =  boost::make_shared< MemberDoubleFromChar< T > >( boost::ref(*target), func );
			};
			void   setTunerOutputSampleRateGetterCB( DoubleFromChar *newCB );
			void   setTunerOutputSampleRateGetterCB( DoubleFromCharFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerOutputSampleRateSetterCB(T &target, void (T::*func)( const char* id, CORBA::Double sr)  ) {
				setTunerOutputSampleRateCB =  boost::make_shared< MemberVoidFromCharDouble< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerOutputSampleRateSetterCB(T *target, void (T::*func)( const char* id, CORBA::Double sr)  ) {
				setTunerOutputSampleRateCB =  boost::make_shared< MemberVoidFromCharDouble< T > >( boost::ref(*target), func );
			};
			void   setTunerOutputSampleRateSetterCB( VoidFromCharDouble *newCB );
			void   setTunerOutputSampleRateSetterCB( VoidFromCharDoubleFn  newCB );

		protected:

			// Callbacks
			boost::shared_ptr< DoubleFromChar > getTunerOutputSampleRateCB;
			boost::shared_ptr< VoidFromCharDouble > setTunerOutputSampleRateCB;
	};

	// ----------------------------------------------------------------------------------------
	// OutFrontendTunerPort declaration
	// ----------------------------------------------------------------------------------------
	class OutFrontendTunerPort : public OutFrontendPort<FRONTEND::FrontendTuner_var,FRONTEND::FrontendTuner>
	{
	    public:
			OutFrontendTunerPort(std::string port_name);
	        ~OutFrontendTunerPort();

	        char* getTunerType(const char* id);
	        CORBA::Boolean getTunerDeviceControl(const char* id);
	        char* getTunerGroupId(const char* id);
	        char* getTunerRfFlowId(const char* id);
	        CF::Properties* getTunerStatus(const char* id);
	};

	// ----------------------------------------------------------------------------------------
	// OutAnalogTunerPort declaration
	// ----------------------------------------------------------------------------------------
	class OutAnalogTunerPort : public OutFrontendPort<FRONTEND::AnalogTuner_var,FRONTEND::AnalogTuner>
	{
	    public:
	    	OutAnalogTunerPort(std::string port_name);
	        ~OutAnalogTunerPort();

	        char* getTunerType(const char* id);
	        CORBA::Boolean getTunerDeviceControl(const char* id);
	        char* getTunerGroupId(const char* id);
	        char* getTunerRfFlowId(const char* id);
	        CF::Properties* getTunerStatus(const char* id);

	        void setTunerCenterFrequency(const char* id, CORBA::Double freq);
	        CORBA::Double getTunerCenterFrequency(const char* id);
	        void setTunerBandwidth(const char* id, CORBA::Double bw);
	        CORBA::Double getTunerBandwidth(const char* id);
	        void setTunerAgcEnable(const char* id, CORBA::Boolean enable);
	        CORBA::Boolean getTunerAgcEnable(const char* id);
	        void setTunerGain(const char* id, CORBA::Float gain);
	        CORBA::Float getTunerGain(const char* id);
	        void setTunerReferenceSource(const char* id, CORBA::Long source);
	        CORBA::Long getTunerReferenceSource(const char* id);
	        void setTunerEnable(const char* id, CORBA::Boolean enable);
	        CORBA::Boolean getTunerEnable(const char* id);
	};

	// ----------------------------------------------------------------------------------------
	// OutDigitalTunerPort declaration
	// ----------------------------------------------------------------------------------------
	class OutDigitalTunerPort : public OutFrontendPort<FRONTEND::DigitalTuner_var,FRONTEND::DigitalTuner>
	{
	    public:
			OutDigitalTunerPort(std::string port_name);
	        ~OutDigitalTunerPort();

	        char* getTunerType(const char* id);
	        CORBA::Boolean getTunerDeviceControl(const char* id);
	        char* getTunerGroupId(const char* id);
	        char* getTunerRfFlowId(const char* id);
	        CF::Properties* getTunerStatus(const char* id);

	        void setTunerCenterFrequency(const char* id, CORBA::Double freq);
	        CORBA::Double getTunerCenterFrequency(const char* id);
	        void setTunerBandwidth(const char* id, CORBA::Double bw);
	        CORBA::Double getTunerBandwidth(const char* id);
	        void setTunerAgcEnable(const char* id, CORBA::Boolean enable);
	        CORBA::Boolean getTunerAgcEnable(const char* id);
	        void setTunerGain(const char* id, CORBA::Float gain);
	        CORBA::Float getTunerGain(const char* id);
	        void setTunerReferenceSource(const char* id, CORBA::Long source);
	        CORBA::Long getTunerReferenceSource(const char* id);
	        void setTunerEnable(const char* id, CORBA::Boolean enable);
	        CORBA::Boolean getTunerEnable(const char* id);

	        void setTunerOutputSampleRate(const char* id, CORBA::Double sr);
	        CORBA::Double getTunerOutputSampleRate(const char* id);
	};

} // end of frontend namespace


#endif
