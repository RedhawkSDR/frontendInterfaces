#ifndef FE_PORT_H
#define FE_PORT_H

#include "ossie/Port_impl.h"
#include <queue>
#include <list>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/locks.hpp>
#include <boost/make_shared.hpp>
#include <boost/ref.hpp>

#define CORBA_MAX_TRANSFER_BYTES omniORB::giopMaxMsgSize()

#include <FRONTEND/TunerControl.h>
#include <FRONTEND/RFInfo.h>


namespace frontend {

	//
	// BEGIN FROM bulkio_p.h
	// used for boost shared pointer instantiation when user
	// supplied callback is provided
	//
	struct null_deleter
	{
		void operator()(void const *) const
		{
		}
	};
	// END FROM bulkio_p.h


	//
	// Callback signatures to register when functions are called
	//
	typedef char* (*CharGetterCBFn)( const char* id );
	typedef CF::Properties* (*PropGetterCBFn)( const char* id );
	typedef CORBA::Double (*DoubleGetterCBFn)( const char* id );
	typedef CORBA::Boolean (*BooleanGetterCBFn)( const char* id );
	typedef CORBA::Float (*FloatGetterCBFn)( const char* id );
	typedef CORBA::Long (*LongGetterCBFn)( const char* id );

	typedef void (*DoubleSetterCBFn)( const char* id, CORBA::Double val );
	typedef void (*BooleanSetterCBFn)( const char* id, CORBA::Boolean val );
	typedef void (*FloatSetterCBFn)( const char* id, CORBA::Float val );
	typedef void (*LongSetterCBFn)( const char* id, CORBA::Long val );

	//
	// Interface definition that will be notified when a function is called
	//
	class CharGetterCB {
		public:
			virtual char* operator() ( const char* id ) = 0;
			virtual ~CharGetterCB() {};
	};
	class PropGetterCB {
		public:
			virtual CF::Properties* operator() ( const char* id ) = 0;
			virtual ~PropGetterCB() {};
	};
	class DoubleGetterCB {
		public:
			virtual CORBA::Double operator() ( const char* id ) = 0;
			virtual ~DoubleGetterCB() {};
	};
	class BooleanGetterCB {
		public:
			virtual CORBA::Boolean operator() ( const char* id ) = 0;
			virtual ~BooleanGetterCB() {};
	};
	class FloatGetterCB {
		public:
			virtual CORBA::Float operator() ( const char* id ) = 0;
			virtual ~FloatGetterCB() {};
	};
	class LongGetterCB {
		public:
			virtual CORBA::Long operator() ( const char* id ) = 0;
			virtual ~LongGetterCB() {};
	};

	class DoubleSetterCB {
		public:
			virtual void operator() ( const char* id, CORBA::Double val ) = 0;
			virtual ~DoubleSetterCB() {};
	};
	class BooleanSetterCB {
		public:
			virtual void operator() ( const char* id, CORBA::Boolean val ) = 0;
			virtual ~BooleanSetterCB() {};
	};
	class FloatSetterCB {
		public:
			virtual void operator() ( const char* id, CORBA::Float val ) = 0;
			virtual ~FloatSetterCB() {};
	};
	class LongSetterCB {
		public:
			virtual void operator() ( const char* id, CORBA::Long val ) = 0;
			virtual ~LongSetterCB() {};
	};

	/**
	* Allow for member functions to be used as callbacks
	*/
	template <class T>
	class MemberCharGetterCB : public CharGetterCB
	{
		public:
			typedef boost::shared_ptr< MemberCharGetterCB< T > > SPtr;
			typedef char* (T::*MemberCharGetterFn)( const char* id );
			static SPtr Create( T &target, MemberCharGetterFn func ){
				return SPtr( new MemberCharGetterCB(target, func ) );
			};
			virtual char* operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberCharGetterCB ( T& target,  MemberCharGetterFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberCharGetterFn func_;
	};
	template <class T>
	class MemberPropGetterCB : public PropGetterCB
	{
		public:
			typedef boost::shared_ptr< MemberPropGetterCB< T > > SPtr;
			typedef CF::Properties* (T::*MemberPropGetterFn)( const char* id );
			static SPtr Create( T &target, MemberPropGetterFn func ){
				return SPtr( new MemberPropGetterCB(target, func ) );
			};
			virtual CF::Properties* operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberPropGetterCB ( T& target,  MemberPropGetterFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberPropGetterFn func_;
	};
	template <class T>
	class MemberDoubleGetterCB : public DoubleGetterCB
	{
		public:
			typedef boost::shared_ptr< MemberDoubleGetterCB< T > > SPtr;
			typedef CORBA::Double (T::*MemberDoubleGetterFn)( const char* id );
			static SPtr Create( T &target, MemberDoubleGetterFn func ){
				return SPtr( new MemberDoubleGetterCB(target, func ) );
			};
			virtual CORBA::Double operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberDoubleGetterCB ( T& target,  MemberDoubleGetterFn func) :
				target_(target),
				func_(func)
				  {
				  }

		private:
			T& target_;
			MemberDoubleGetterFn func_;
	};
	template <class T>
	class MemberBooleanGetterCB : public BooleanGetterCB
	{
		public:
			typedef boost::shared_ptr< MemberBooleanGetterCB< T > > SPtr;
			typedef CORBA::Boolean (T::*MemberBooleanGetterFn)( const char* id );
			static SPtr Create( T &target, MemberBooleanGetterFn func ){
				return SPtr( new MemberBooleanGetterCB(target, func ) );
			};
			virtual CORBA::Boolean operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberBooleanGetterCB ( T& target,  MemberBooleanGetterFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberBooleanGetterFn func_;
	};
	template <class T>
	class MemberFloatGetterCB : public FloatGetterCB
	{
		public:
			typedef boost::shared_ptr< MemberFloatGetterCB< T > > SPtr;
			typedef CORBA::Float (T::*MemberFloatGetterFn)( const char* id );
			static SPtr Create( T &target, MemberFloatGetterFn func ){
				return SPtr( new MemberFloatGetterCB(target, func ) );
			};
			virtual CORBA::Float operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberFloatGetterCB ( T& target,  MemberFloatGetterFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberFloatGetterFn func_;
	};
	template <class T>
	class MemberLongGetterCB : public LongGetterCB
	{
		public:
			typedef boost::shared_ptr< MemberLongGetterCB< T > > SPtr;
			typedef CORBA::Long (T::*MemberLongGetterFn)( const char* id );
			static SPtr Create( T &target, MemberLongGetterFn func ){
				return SPtr( new MemberLongGetterCB(target, func ) );
			};
			virtual CORBA::Long operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberLongGetterCB ( T& target,  MemberLongGetterFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberLongGetterFn func_;
	};
	template <class T>
	class MemberDoubleSetterCB : public DoubleSetterCB
	{
		public:
			typedef boost::shared_ptr< MemberDoubleSetterCB< T > > SPtr;
			typedef void (T::*MemberDoubleSetterFn)( const char* id, CORBA::Double val );
			static SPtr Create( T &target, MemberDoubleSetterFn func ){
				return SPtr( new MemberDoubleSetterCB(target, func ) );
			};
			virtual void operator() (const char* id, CORBA::Double val )
			{
				(target_.*func_)(id,val);
			}
			MemberDoubleSetterCB ( T& target,  MemberDoubleSetterFn func) :
				target_(target),
				func_(func)
				  {
				  }

		private:
			T& target_;
			MemberDoubleSetterFn func_;
	};
	template <class T>
	class MemberBooleanSetterCB : public BooleanSetterCB
	{
		public:
			typedef boost::shared_ptr< MemberBooleanSetterCB< T > > SPtr;
			typedef void (T::*MemberBooleanSetterFn)( const char* id, CORBA::Boolean val );
			static SPtr Create( T &target, MemberBooleanSetterFn func ){
				return SPtr( new MemberBooleanSetterCB(target, func ) );
			};
			virtual void operator() (const char* id, CORBA::Boolean val )
			{
				(target_.*func_)(id,val);
			}
			MemberBooleanSetterCB ( T& target,  MemberBooleanSetterFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberBooleanSetterFn func_;
	};
	template <class T>
	class MemberFloatSetterCB : public FloatSetterCB
	{
		public:
			typedef boost::shared_ptr< MemberFloatSetterCB< T > > SPtr;
			typedef void (T::*MemberFloatSetterFn)( const char* id, CORBA::Float val );
			static SPtr Create( T &target, MemberFloatSetterFn func ){
				return SPtr( new MemberFloatSetterCB(target, func ) );
			};
			virtual void operator() (const char* id, CORBA::Float val )
			{
				(target_.*func_)(id,val);
			}
			MemberFloatSetterCB ( T& target,  MemberFloatSetterFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberFloatSetterFn func_;
	};
	template <class T>
	class MemberLongSetterCB : public LongSetterCB
	{
		public:
			typedef boost::shared_ptr< MemberLongSetterCB< T > > SPtr;
			typedef void (T::*MemberLongSetterFn)( const char* id, CORBA::Long val );
			static SPtr Create( T &target, MemberLongSetterFn func ){
				return SPtr( new MemberLongSetterCB(target, func ) );
			};
			virtual void operator() (const char* id, CORBA::Long val )
			{
				(target_.*func_)(id,val);
			}
			MemberLongSetterCB ( T& target,  MemberLongSetterFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberLongSetterFn func_;
	};


	// ----------------------------------------------------------------------------------------
	// InDigitalTunerPort declaration
	// ----------------------------------------------------------------------------------------
	class InDigitalTunerPort : public POA_FRONTEND::DigitalTuner, public Port_Provides_base_impl
	{
		public:
			InDigitalTunerPort(std::string port_name,
				CharGetterCB *newTunerTypeGetterCB = NULL,
				BooleanGetterCB *newTunerDeviceControlGetterCB = NULL,
				CharGetterCB *newTunerGroupIdGetterCB = NULL,
				CharGetterCB *newTunerRfFlowIdGetterCB = NULL,
				PropGetterCB *newTunerStatusGetterCB = NULL,
				DoubleGetterCB *newTunerCenterFrequencyGetterCB = NULL,
				DoubleSetterCB *newTunerCenterFrequencySetterCB = NULL,
				DoubleGetterCB *newTunerBandwidthGetterCB = NULL,
				DoubleSetterCB *newTunerBandwidthSetterCB = NULL,
				BooleanGetterCB *newTunerAgcEnableGetterCB = NULL,
				BooleanSetterCB *newTunerAgcEnableSetterCB = NULL,
				FloatGetterCB *newTunerGainGetterCB = NULL,
				FloatSetterCB *newTunerGainSetterCB = NULL,
				LongGetterCB *newTunerReferenceSourceGetterCB = NULL,
				LongSetterCB *newTunerReferenceSourceSetterCB = NULL,
				BooleanGetterCB *newTunerEnableGetterCB = NULL,
				BooleanSetterCB *newTunerEnableSetterCB = NULL,
				DoubleGetterCB *newTunerOutputSampleRateGetterCB = NULL,
				DoubleSetterCB *newTunerOutputSampleRateSetterCB = NULL);//, USRP_UHD_base *_parent);
			~InDigitalTunerPort();

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

			// Assign  TunerType callbacks - getters
			template< typename T > inline
			  void setTunerTypeGetterCB(T &target, char* (T::*func)( const char* id)  ) {
				getTunerTypeCB =  boost::make_shared< MemberCharGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerTypeGetterCB(T *target, char* (T::*func)( const char* id)  ) {
				getTunerTypeCB =  boost::make_shared< MemberCharGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerTypeGetterCB( CharGetterCB *newCB );
			void   setTunerTypeGetterCB( CharGetterCBFn  newCB );

			// Assign  TunerDeviceControl callbacks - getters
			template< typename T > inline
			  void setTunerDeviceControlGetterCB(T &target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerDeviceControlCB =  boost::make_shared< MemberBooleanGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerDeviceControlGetterCB(T *target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerDeviceControlCB =  boost::make_shared< MemberBooleanGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerDeviceControlGetterCB( BooleanGetterCB *newCB );
			void   setTunerDeviceControlGetterCB( BooleanGetterCBFn  newCB );

			// Assign  TunerGroupId callbacks - getters
			template< typename T > inline
			  void setTunerGroupIdGetterCB(T &target, char* (T::*func)( const char* id)  ) {
				getTunerGroupIdCB =  boost::make_shared< MemberCharGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerGroupIdGetterCB(T *target, char* (T::*func)( const char* id)  ) {
				getTunerGroupIdCB =  boost::make_shared< MemberCharGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerGroupIdGetterCB( CharGetterCB *newCB );
			void   setTunerGroupIdGetterCB( CharGetterCBFn  newCB );

			// Assign  TunerRfFlowId callbacks - getters
			template< typename T > inline
			  void setTunerRfFlowIdGetterCB(T &target, char* (T::*func)( const char* id)  ) {
				getTunerRfFlowIdCB =  boost::make_shared< MemberCharGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerRfFlowIdGetterCB(T *target, char* (T::*func)( const char* id)  ) {
				getTunerRfFlowIdCB =  boost::make_shared< MemberCharGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerRfFlowIdGetterCB( CharGetterCB *newCB );
			void   setTunerRfFlowIdGetterCB( CharGetterCBFn  newCB );

			// Assign  TunerStatus callbacks - getters
			template< typename T > inline
			  void setTunerStatusGetterCB(T &target, CF::Properties* (T::*func)( const char* id)  ) {
				getTunerStatusCB =  boost::make_shared< MemberPropGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerStatusGetterCB(T *target, CF::Properties* (T::*func)( const char* id)  ) {
				getTunerStatusCB =  boost::make_shared< MemberPropGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerStatusGetterCB( PropGetterCB *newCB );
			void   setTunerStatusGetterCB( PropGetterCBFn  newCB );

			// Assign  TunerCenterFrequency callbacks - getters
			template< typename T > inline
			  void setTunerCenterFrequencyGetterCB(T &target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerCenterFrequencyCB =  boost::make_shared< MemberDoubleGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerCenterFrequencyGetterCB(T *target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerCenterFrequencyCB =  boost::make_shared< MemberDoubleGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerCenterFrequencyGetterCB( DoubleGetterCB *newCB );
			void   setTunerCenterFrequencyGetterCB( DoubleGetterCBFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerCenterFrequencySetterCB(T &target, void (T::*func)( const char* id, CORBA::Double freq)  ) {
				setTunerCenterFrequencyCB =  boost::make_shared< MemberDoubleSetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerCenterFrequencySetterCB(T *target, void (T::*func)( const char* id, CORBA::Double freq)  ) {
				setTunerCenterFrequencyCB =  boost::make_shared< MemberDoubleSetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerCenterFrequencySetterCB( DoubleSetterCB *newCB );
			void   setTunerCenterFrequencySetterCB( DoubleSetterCBFn  newCB );

			// Assign  TunerBandwidth callbacks - getters
			template< typename T > inline
			  void setTunerBandwidthGetterCB(T &target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerBandwidthCB =  boost::make_shared< MemberDoubleGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerBandwidthGetterCB(T *target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerBandwidthCB =  boost::make_shared< MemberDoubleGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerBandwidthGetterCB( DoubleGetterCB *newCB );
			void   setTunerBandwidthGetterCB( DoubleGetterCBFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerBandwidthSetterCB(T &target, void (T::*func)( const char* id, CORBA::Double bw)  ) {
				setTunerBandwidthCB =  boost::make_shared< MemberDoubleSetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerBandwidthSetterCB(T *target, void (T::*func)( const char* id, CORBA::Double bw)  ) {
				setTunerBandwidthCB =  boost::make_shared< MemberDoubleSetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerBandwidthSetterCB( DoubleSetterCB *newCB );
			void   setTunerBandwidthSetterCB( DoubleSetterCBFn  newCB );

			// Assign  TunerAgcEnable callbacks - getters
			template< typename T > inline
			  void setTunerAgcEnableGetterCB(T &target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerAgcEnableCB =  boost::make_shared< MemberBooleanGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerAgcEnableGetterCB(T *target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerAgcEnableCB =  boost::make_shared< MemberBooleanGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerAgcEnableGetterCB( BooleanGetterCB *newCB );
			void   setTunerAgcEnableGetterCB( BooleanGetterCBFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerAgcEnableSetterCB(T &target, void (T::*func)( const char* id, CORBA::Boolean enable)  ) {
				setTunerAgcEnableCB =  boost::make_shared< MemberBooleanSetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerAgcEnableSetterCB(T *target, void (T::*func)( const char* id, CORBA::Boolean enable)  ) {
				setTunerAgcEnableCB =  boost::make_shared< MemberBooleanSetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerAgcEnableSetterCB( BooleanSetterCB *newCB );
			void   setTunerAgcEnableSetterCB( BooleanSetterCBFn  newCB );

			// Assign  TunerGain callbacks - getters
			template< typename T > inline
			  void setTunerGainGetterCB(T &target, CORBA::Float (T::*func)( const char* id)  ) {
				getTunerGainCB =  boost::make_shared< MemberFloatGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerGainGetterCB(T *target, CORBA::Float (T::*func)( const char* id)  ) {
				getTunerGainCB =  boost::make_shared< MemberFloatGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerGainGetterCB( FloatGetterCB *newCB );
			void   setTunerGainGetterCB( FloatGetterCBFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerGainSetterCB(T &target, void (T::*func)( const char* id, CORBA::Float gain)  ) {
				setTunerGainCB =  boost::make_shared< MemberFloatSetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerGainSetterCB(T *target, void (T::*func)( const char* id, CORBA::Float gain)  ) {
				setTunerGainCB =  boost::make_shared< MemberFloatSetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerGainSetterCB( FloatSetterCB *newCB );
			void   setTunerGainSetterCB( FloatSetterCBFn  newCB );

			// Assign  TunerReferenceSource callbacks - getters
			template< typename T > inline
			  void setTunerReferenceSourceGetterCB(T &target, CORBA::Long (T::*func)( const char* id)  ) {
				getTunerReferenceSourceCB =  boost::make_shared< MemberLongGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerReferenceSourceGetterCB(T *target, CORBA::Long (T::*func)( const char* id)  ) {
				getTunerReferenceSourceCB =  boost::make_shared< MemberLongGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerReferenceSourceGetterCB( LongGetterCB *newCB );
			void   setTunerReferenceSourceGetterCB( LongGetterCBFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerReferenceSourceSetterCB(T &target, void (T::*func)( const char* id, CORBA::Long source)  ) {
				setTunerReferenceSourceCB =  boost::make_shared< MemberLongSetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerReferenceSourceSetterCB(T *target, void (T::*func)( const char* id, CORBA::Long source)  ) {
				setTunerReferenceSourceCB =  boost::make_shared< MemberLongSetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerReferenceSourceSetterCB( LongSetterCB *newCB );
			void   setTunerReferenceSourceSetterCB( LongSetterCBFn  newCB );

			// Assign  TunerEnable callbacks - getters
			template< typename T > inline
			  void setTunerEnableGetterCB(T &target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerEnableCB =  boost::make_shared< MemberBooleanGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerEnableGetterCB(T *target, CORBA::Boolean (T::*func)( const char* id)  ) {
				getTunerEnableCB =  boost::make_shared< MemberBooleanGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerEnableGetterCB( BooleanGetterCB *newCB );
			void   setTunerEnableGetterCB( BooleanGetterCBFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerEnableSetterCB(T &target, void (T::*func)( const char* id, CORBA::Boolean enable)  ) {
				setTunerEnableCB =  boost::make_shared< MemberBooleanSetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerEnableSetterCB(T *target, void (T::*func)( const char* id, CORBA::Boolean enable)  ) {
				setTunerEnableCB =  boost::make_shared< MemberBooleanSetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerEnableSetterCB( BooleanSetterCB *newCB );
			void   setTunerEnableSetterCB( BooleanSetterCBFn  newCB );

			// Assign  TunerOutputSampleRate callbacks - getters
			template< typename T > inline
			  void setTunerOutputSampleRateGetterCB(T &target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerOutputSampleRateCB =  boost::make_shared< MemberDoubleGetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerOutputSampleRateGetterCB(T *target, CORBA::Double (T::*func)( const char* id)  ) {
				getTunerOutputSampleRateCB =  boost::make_shared< MemberDoubleGetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerOutputSampleRateGetterCB( DoubleGetterCB *newCB );
			void   setTunerOutputSampleRateGetterCB( DoubleGetterCBFn  newCB );
			// and setters
			template< typename T > inline
			  void setTunerOutputSampleRateSetterCB(T &target, void (T::*func)( const char* id, CORBA::Double sr)  ) {
				setTunerOutputSampleRateCB =  boost::make_shared< MemberDoubleSetterCB< T > >( boost::ref(target), func );
			};
			template< typename T > inline
			  void setTunerOutputSampleRateSetterCB(T *target, void (T::*func)( const char* id, CORBA::Double sr)  ) {
				setTunerOutputSampleRateCB =  boost::make_shared< MemberDoubleSetterCB< T > >( boost::ref(*target), func );
			};
			void   setTunerOutputSampleRateSetterCB( DoubleSetterCB *newCB );
			void   setTunerOutputSampleRateSetterCB( DoubleSetterCBFn  newCB );

		protected:
			//USRP_UHD_i *parent;
			boost::mutex portAccess;

			// Callbacks
			boost::shared_ptr< CharGetterCB > getTunerTypeCB;
			boost::shared_ptr< BooleanGetterCB > getTunerDeviceControlCB;
			boost::shared_ptr< CharGetterCB > getTunerGroupIdCB;
			boost::shared_ptr< CharGetterCB > getTunerRfFlowIdCB;
			boost::shared_ptr< PropGetterCB > getTunerStatusCB;
			boost::shared_ptr< DoubleGetterCB > getTunerCenterFrequencyCB;
			boost::shared_ptr< DoubleSetterCB > setTunerCenterFrequencyCB;
			boost::shared_ptr< DoubleGetterCB > getTunerBandwidthCB;
			boost::shared_ptr< DoubleSetterCB > setTunerBandwidthCB;
			boost::shared_ptr< BooleanGetterCB > getTunerAgcEnableCB;
			boost::shared_ptr< BooleanSetterCB > setTunerAgcEnableCB;
			boost::shared_ptr< FloatGetterCB > getTunerGainCB;
			boost::shared_ptr< FloatSetterCB > setTunerGainCB;
			boost::shared_ptr< LongGetterCB > getTunerReferenceSourceCB;
			boost::shared_ptr< LongSetterCB > setTunerReferenceSourceCB;
			boost::shared_ptr< BooleanGetterCB > getTunerEnableCB;
			boost::shared_ptr< BooleanSetterCB > setTunerEnableCB;
			boost::shared_ptr< DoubleGetterCB > getTunerOutputSampleRateCB;
			boost::shared_ptr< DoubleSetterCB > setTunerOutputSampleRateCB;
	};

} // end of frontend namespace

#endif
