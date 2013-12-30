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

#include <ossie/CF/QueryablePort.h>

#include <FRONTEND/RFInfo.h>
#include <FRONTEND/GPS.h>
#include <FRONTEND/NavigationData.h>

#include "fe_base.h"


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
	// Callback signatures to register when functions are called (provides ports only)
	//

	// for InDigitalTunerPort, InAnalogTunerPort, InFrontendTunerPort
	typedef char* (*CharFromCharFn)( const char* id );
	typedef CF::Properties* (*PropFromCharFn)( const char* id );
	typedef CORBA::Double (*DoubleFromCharFn)( const char* id );
	typedef CORBA::Boolean (*BooleanFromCharFn)( const char* id );
	typedef CORBA::Float (*FloatFromCharFn)( const char* id );
	typedef CORBA::Long (*LongFromCharFn)( const char* id );

	typedef void (*VoidFromCharDoubleFn)( const char* id, CORBA::Double val );
	typedef void (*VoidFromCharBooleanFn)( const char* id, CORBA::Boolean val );
	typedef void (*VoidFromCharFloatFn)( const char* id, CORBA::Float val );
	typedef void (*VoidFromCharLongFn)( const char* id, CORBA::Long val );

	// for InRFInfoPort, InRFSourcePort
	typedef char* (*CharFromVoidFn)( void );
	typedef FRONTEND::RFInfoPkt* (*RFInfoPktFromVoidFn)( void );
	typedef FRONTEND::RFInfoPktSequence* (*RFInfoPktSeqFromVoidFn)( void );

	typedef void (*VoidFromCharFn)( const char* data );
	typedef void (*VoidFromRFInfoPktFn)( const FRONTEND::RFInfoPkt& data );
	typedef void (*VoidFromRFInfoPktSeqFn)( const FRONTEND::RFInfoPktSequence& data );

	// for InGPSPort
	typedef FRONTEND::GPSInfo* (*GPSInfoFromVoidFn)( void );
	typedef void (*VoidFromGPSInfoFn)( const FRONTEND::GPSInfo& data );
	typedef FRONTEND::GpsTimePos* (*GpsTimePosFromVoidFn)( void );
	typedef void (*VoidFromGpsTimePosFn)( const FRONTEND::GpsTimePos& data );

	// for InNavDataPort
	typedef FRONTEND::NavigationPacket* (*NavPktFromVoidFn)( void );
	typedef void (*VoidFromNavPktFn)( const FRONTEND::NavigationPacket& data );

	//
	// Interface definition that will be notified when a function is called
	//

	// for InDigitalTunerPort, InAnalogTunerPort, InFrontendTunerPort
	class CharFromChar {
		public:
			virtual char* operator() ( const char* id ) = 0;
			virtual ~CharFromChar() {};
	};
	class PropFromChar {
		public:
			virtual CF::Properties* operator() ( const char* id ) = 0;
			virtual ~PropFromChar() {};
	};
	class DoubleFromChar {
		public:
			virtual CORBA::Double operator() ( const char* id ) = 0;
			virtual ~DoubleFromChar() {};
	};
	class BooleanFromChar {
		public:
			virtual CORBA::Boolean operator() ( const char* id ) = 0;
			virtual ~BooleanFromChar() {};
	};
	class FloatFromChar {
		public:
			virtual CORBA::Float operator() ( const char* id ) = 0;
			virtual ~FloatFromChar() {};
	};
	class LongFromChar {
		public:
			virtual CORBA::Long operator() ( const char* id ) = 0;
			virtual ~LongFromChar() {};
	};

	class VoidFromCharDouble {
		public:
			virtual void operator() ( const char* id, CORBA::Double val ) = 0;
			virtual ~VoidFromCharDouble() {};
	};
	class VoidFromCharBoolean {
		public:
			virtual void operator() ( const char* id, CORBA::Boolean val ) = 0;
			virtual ~VoidFromCharBoolean() {};
	};
	class VoidFromCharFloat {
		public:
			virtual void operator() ( const char* id, CORBA::Float val ) = 0;
			virtual ~VoidFromCharFloat() {};
	};
	class VoidFromCharLong {
		public:
			virtual void operator() ( const char* id, CORBA::Long val ) = 0;
			virtual ~VoidFromCharLong() {};
	};

	// for InRFInfoPort, InRFSourcePort
	class CharFromVoid {
		public:
			virtual char* operator() ( void ) = 0;
			virtual ~CharFromVoid() {};
	};
	class RFInfoPktFromVoid {
		public:
			virtual FRONTEND::RFInfoPkt* operator() ( void ) = 0;
			virtual ~RFInfoPktFromVoid() {};
	};
	class RFInfoPktSeqFromVoid {
		public:
			virtual FRONTEND::RFInfoPktSequence* operator() ( void ) = 0;
			virtual ~RFInfoPktSeqFromVoid() {};
	};
	class VoidFromChar {
		public:
			virtual void operator() ( const char* data ) = 0;
			virtual ~VoidFromChar() {};
	};
	class VoidFromRFInfoPkt {
		public:
			virtual void operator() ( const FRONTEND::RFInfoPkt& data ) = 0;
			virtual ~VoidFromRFInfoPkt() {};
	};
	class VoidFromRFInfoPktSeq {
		public:
			virtual void operator() ( const FRONTEND::RFInfoPktSequence& data ) = 0;
			virtual ~VoidFromRFInfoPktSeq() {};
	};

	// for InGPSPort
	class GPSInfoFromVoid {
		public:
			virtual FRONTEND::GPSInfo* operator() ( void ) = 0;
			virtual ~GPSInfoFromVoid() {};
	};
	class GpsTimePosFromVoid {
		public:
			virtual FRONTEND::GpsTimePos* operator() ( void ) = 0;
			virtual ~GpsTimePosFromVoid() {};
	};
	class VoidFromGPSInfo {
		public:
			virtual void operator() ( const FRONTEND::GPSInfo& data ) = 0;
			virtual ~VoidFromGPSInfo() {};
	};
	class VoidFromGpsTimePos {
		public:
			virtual void operator() ( const FRONTEND::GpsTimePos& data ) = 0;
			virtual ~VoidFromGpsTimePos() {};
	};

	// for InNavDataPort
	class NavPktFromVoid {
		public:
			virtual FRONTEND::NavigationPacket* operator() ( void ) = 0;
			virtual ~NavPktFromVoid() {};
	};

	class VoidFromNavPkt {
		public:
			virtual void operator() ( const FRONTEND::NavigationPacket& data ) = 0;
			virtual ~VoidFromNavPkt() {};
	};

	/**
	* Allow for member functions to be used as callbacks
	*/

	// for InDigitalTunerPort, InAnalogTunerPort, InFrontendTunerPort
	template <class T>
	class MemberCharFromChar : public CharFromChar
	{
		public:
			typedef boost::shared_ptr< MemberCharFromChar< T > > SPtr;
			typedef char* (T::*MemberCharFromCharFn)( const char* id );
			static SPtr Create( T &target, MemberCharFromCharFn func ){
				return SPtr( new MemberCharFromChar(target, func ) );
			};
			virtual char* operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberCharFromChar ( T& target,  MemberCharFromCharFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberCharFromCharFn func_;
	};
	template <class T>
	class MemberPropFromChar : public PropFromChar
	{
		public:
			typedef boost::shared_ptr< MemberPropFromChar< T > > SPtr;
			typedef CF::Properties* (T::*MemberPropFromCharFn)( const char* id );
			static SPtr Create( T &target, MemberPropFromCharFn func ){
				return SPtr( new MemberPropFromChar(target, func ) );
			};
			virtual CF::Properties* operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberPropFromChar ( T& target,  MemberPropFromCharFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberPropFromCharFn func_;
	};
	template <class T>
	class MemberDoubleFromChar : public DoubleFromChar
	{
		public:
			typedef boost::shared_ptr< MemberDoubleFromChar< T > > SPtr;
			typedef CORBA::Double (T::*MemberDoubleFromCharFn)( const char* id );
			static SPtr Create( T &target, MemberDoubleFromCharFn func ){
				return SPtr( new MemberDoubleFromChar(target, func ) );
			};
			virtual CORBA::Double operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberDoubleFromChar ( T& target,  MemberDoubleFromCharFn func) :
				target_(target),
				func_(func)
				  {
				  }

		private:
			T& target_;
			MemberDoubleFromCharFn func_;
	};
	template <class T>
	class MemberBooleanFromChar : public BooleanFromChar
	{
		public:
			typedef boost::shared_ptr< MemberBooleanFromChar< T > > SPtr;
			typedef CORBA::Boolean (T::*MemberBooleanFromCharFn)( const char* id );
			static SPtr Create( T &target, MemberBooleanFromCharFn func ){
				return SPtr( new MemberBooleanFromChar(target, func ) );
			};
			virtual CORBA::Boolean operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberBooleanFromChar ( T& target,  MemberBooleanFromCharFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberBooleanFromCharFn func_;
	};
	template <class T>
	class MemberFloatFromChar : public FloatFromChar
	{
		public:
			typedef boost::shared_ptr< MemberFloatFromChar< T > > SPtr;
			typedef CORBA::Float (T::*MemberFloatFromCharFn)( const char* id );
			static SPtr Create( T &target, MemberFloatFromCharFn func ){
				return SPtr( new MemberFloatFromChar(target, func ) );
			};
			virtual CORBA::Float operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberFloatFromChar ( T& target,  MemberFloatFromCharFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberFloatFromCharFn func_;
	};
	template <class T>
	class MemberLongFromChar : public LongFromChar
	{
		public:
			typedef boost::shared_ptr< MemberLongFromChar< T > > SPtr;
			typedef CORBA::Long (T::*MemberLongFromCharFn)( const char* id );
			static SPtr Create( T &target, MemberLongFromCharFn func ){
				return SPtr( new MemberLongFromChar(target, func ) );
			};
			virtual CORBA::Long operator() (const char* id )
			{
				return (target_.*func_)(id);
			}
			MemberLongFromChar ( T& target,  MemberLongFromCharFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberLongFromCharFn func_;
	};
	template <class T>
	class MemberVoidFromCharDouble : public VoidFromCharDouble
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromCharDouble< T > > SPtr;
			typedef void (T::*MemberVoidFromCharDoubleFn)( const char* id, CORBA::Double val );
			static SPtr Create( T &target, MemberVoidFromCharDoubleFn func ){
				return SPtr( new MemberVoidFromCharDouble(target, func ) );
			};
			virtual void operator() (const char* id, CORBA::Double val )
			{
				(target_.*func_)(id,val);
			}
			MemberVoidFromCharDouble ( T& target,  MemberVoidFromCharDoubleFn func) :
				target_(target),
				func_(func)
				  {
				  }

		private:
			T& target_;
			MemberVoidFromCharDoubleFn func_;
	};
	template <class T>
	class MemberVoidFromCharBoolean : public VoidFromCharBoolean
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromCharBoolean< T > > SPtr;
			typedef void (T::*MemberVoidFromCharBooleanFn)( const char* id, CORBA::Boolean val );
			static SPtr Create( T &target, MemberVoidFromCharBooleanFn func ){
				return SPtr( new MemberVoidFromCharBoolean(target, func ) );
			};
			virtual void operator() (const char* id, CORBA::Boolean val )
			{
				(target_.*func_)(id,val);
			}
			MemberVoidFromCharBoolean ( T& target,  MemberVoidFromCharBooleanFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberVoidFromCharBooleanFn func_;
	};
	template <class T>
	class MemberVoidFromCharFloat : public VoidFromCharFloat
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromCharFloat< T > > SPtr;
			typedef void (T::*MemberVoidFromCharFloatFn)( const char* id, CORBA::Float val );
			static SPtr Create( T &target, MemberVoidFromCharFloatFn func ){
				return SPtr( new MemberVoidFromCharFloat(target, func ) );
			};
			virtual void operator() (const char* id, CORBA::Float val )
			{
				(target_.*func_)(id,val);
			}
			MemberVoidFromCharFloat ( T& target,  MemberVoidFromCharFloatFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberVoidFromCharFloatFn func_;
	};
	template <class T>
	class MemberVoidFromCharLong : public VoidFromCharLong
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromCharLong< T > > SPtr;
			typedef void (T::*MemberVoidFromCharLongFn)( const char* id, CORBA::Long val );
			static SPtr Create( T &target, MemberVoidFromCharLongFn func ){
				return SPtr( new MemberVoidFromCharLong(target, func ) );
			};
			virtual void operator() (const char* id, CORBA::Long val )
			{
				(target_.*func_)(id,val);
			}
			MemberVoidFromCharLong ( T& target,  MemberVoidFromCharLongFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberVoidFromCharLongFn func_;
	};

	// for InRFInfoPort, InRFSourcePort
	template <class T>
	class MemberCharFromVoid : public CharFromVoid
	{
		public:
			typedef boost::shared_ptr< MemberCharFromVoid< T > > SPtr;
			typedef char* (T::*MemberCharFromVoidFn)( void );
			static SPtr Create( T &target, MemberCharFromVoidFn func ){
				return SPtr( new MemberCharFromVoid(target, func ) );
			};
			virtual char* operator() ( void )
			{
				return (target_.*func_)();
			}
			MemberCharFromVoid ( T& target,  MemberCharFromVoidFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberCharFromVoidFn func_;
	};
	template <class T>
	class MemberRFInfoPktFromVoid : public RFInfoPktFromVoid
	{
		public:
			typedef boost::shared_ptr< MemberRFInfoPktFromVoid< T > > SPtr;
			typedef FRONTEND::RFInfoPkt* (T::*MemberRFInfoPktFromVoidFn)( void );
			static SPtr Create( T &target, MemberRFInfoPktFromVoidFn func ){
				return SPtr( new MemberRFInfoPktFromVoid(target, func ) );
			};
			virtual FRONTEND::RFInfoPkt* operator() ( void )
			{
				return (target_.*func_)();
			}
			MemberRFInfoPktFromVoid ( T& target,  MemberRFInfoPktFromVoidFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberRFInfoPktFromVoidFn func_;
	};
	template <class T>
	class MemberRFInfoPktSeqFromVoid : public RFInfoPktSeqFromVoid
	{
		public:
			typedef boost::shared_ptr< MemberRFInfoPktSeqFromVoid< T > > SPtr;
			typedef FRONTEND::RFInfoPktSequence* (T::*MemberRFInfoPktSeqFromVoidFn)( void );
			static SPtr Create( T &target, MemberRFInfoPktSeqFromVoidFn func ){
				return SPtr( new MemberRFInfoPktSeqFromVoid(target, func ) );
			};
			virtual FRONTEND::RFInfoPktSequence* operator() ( void )
			{
				return (target_.*func_)();
			}
			MemberRFInfoPktSeqFromVoid ( T& target,  MemberRFInfoPktSeqFromVoidFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberRFInfoPktSeqFromVoidFn func_;
	};
	template <class T>
	class MemberVoidFromChar : public VoidFromChar
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromChar< T > > SPtr;
			typedef void (T::*MemberVoidFromCharFn)( const char* data );
			static SPtr Create( T &target, MemberVoidFromCharFn func ){
				return SPtr( new MemberVoidFromChar(target, func ) );
			};
			virtual void operator() (const char* data )
			{
				(target_.*func_)(data);
			}
			MemberVoidFromChar ( T& target,  MemberVoidFromCharFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberVoidFromCharFn func_;
	};
	template <class T>
	class MemberVoidFromRFInfoPkt : public VoidFromRFInfoPkt
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromRFInfoPkt< T > > SPtr;
			typedef void (T::*MemberVoidFromRFInfoPktFn)( const FRONTEND::RFInfoPkt& data );
			static SPtr Create( T &target, MemberVoidFromRFInfoPktFn func ){
				return SPtr( new MemberVoidFromRFInfoPkt(target, func ) );
			};
			virtual void operator() (const FRONTEND::RFInfoPkt& data )
			{
				(target_.*func_)(data);
			}
			MemberVoidFromRFInfoPkt ( T& target,  MemberVoidFromRFInfoPktFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberVoidFromRFInfoPktFn func_;
	};
	template <class T>
	class MemberVoidFromRFInfoPktSeq : public VoidFromRFInfoPktSeq
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromRFInfoPktSeq< T > > SPtr;
			typedef void (T::*MemberVoidFromRFInfoPktSeqFn)( const FRONTEND::RFInfoPktSequence& data );
			static SPtr Create( T &target, MemberVoidFromRFInfoPktSeqFn func ){
				return SPtr( new MemberVoidFromRFInfoPktSeq(target, func ) );
			};
			virtual void operator() (const FRONTEND::RFInfoPktSequence& data )
			{
				(target_.*func_)(data);
			}
			MemberVoidFromRFInfoPktSeq ( T& target,  MemberVoidFromRFInfoPktSeqFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberVoidFromRFInfoPktSeqFn func_;
	};

	// for InGPSPort
	template <class T>
	class MemberGPSInfoFromVoid : public GPSInfoFromVoid
	{
		public:
			typedef boost::shared_ptr< MemberGPSInfoFromVoid< T > > SPtr;
			typedef FRONTEND::GPSInfo* (T::*MemberGPSInfoFromVoidFn)( void );
			static SPtr Create( T &target, MemberGPSInfoFromVoidFn func ){
				return SPtr( new MemberGPSInfoFromVoid(target, func ) );
			};
			virtual FRONTEND::GPSInfo* operator() ( void )
			{
				return (target_.*func_)();
			}
			MemberGPSInfoFromVoid ( T& target,  MemberGPSInfoFromVoidFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberGPSInfoFromVoidFn func_;
	};
	template <class T>
	class MemberGpsTimePosFromVoid : public GpsTimePosFromVoid
	{
		public:
			typedef boost::shared_ptr< MemberGpsTimePosFromVoid< T > > SPtr;
			typedef FRONTEND::GpsTimePos* (T::*MemberGpsTimePosFromVoidFn)( void );
			static SPtr Create( T &target, MemberGpsTimePosFromVoidFn func ){
				return SPtr( new MemberGpsTimePosFromVoid(target, func ) );
			};
			virtual FRONTEND::GpsTimePos* operator() ( void )
			{
				return (target_.*func_)();
			}
			MemberGpsTimePosFromVoid ( T& target,  MemberGpsTimePosFromVoidFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberGpsTimePosFromVoidFn func_;
	};
	template <class T>
	class MemberVoidFromGPSInfo : public VoidFromGPSInfo
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromGPSInfo< T > > SPtr;
			typedef void (T::*MemberVoidFromGPSInfoFn)( const FRONTEND::GPSInfo& data );
			static SPtr Create( T &target, MemberVoidFromGPSInfoFn func ){
				return SPtr( new MemberVoidFromGPSInfo(target, func ) );
			};
			virtual void operator() (const FRONTEND::GPSInfo& data )
			{
				(target_.*func_)(data);
			}
			MemberVoidFromGPSInfo ( T& target,  MemberVoidFromGPSInfoFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberVoidFromGPSInfoFn func_;
	};
	template <class T>
	class MemberVoidFromGpsTimePos : public VoidFromGpsTimePos
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromGpsTimePos< T > > SPtr;
			typedef void (T::*MemberVoidFromGpsTimePosFn)( const FRONTEND::GpsTimePos& data );
			static SPtr Create( T &target, MemberVoidFromGpsTimePosFn func ){
				return SPtr( new MemberVoidFromGpsTimePos(target, func ) );
			};
			virtual void operator() (const FRONTEND::GpsTimePos& data )
			{
				(target_.*func_)(data);
			}
			MemberVoidFromGpsTimePos ( T& target,  MemberVoidFromGpsTimePosFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberVoidFromGpsTimePosFn func_;
	};

	// for InNavDataPort
	template <class T>
	class MemberNavPktFromVoid : public NavPktFromVoid
	{
		public:
			typedef boost::shared_ptr< MemberNavPktFromVoid< T > > SPtr;
			typedef FRONTEND::NavigationPacket* (T::*MemberNavPktFromVoidFn)( void );
			static SPtr Create( T &target, MemberNavPktFromVoidFn func ){
				return SPtr( new MemberNavPktFromVoid(target, func ) );
			};
			virtual FRONTEND::NavigationPacket* operator() ( void )
			{
				return (target_.*func_)();
			}
			MemberNavPktFromVoid ( T& target,  MemberNavPktFromVoidFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberNavPktFromVoidFn func_;
	};
	template <class T>
	class MemberVoidFromNavPkt : public VoidFromNavPkt
	{
		public:
			typedef boost::shared_ptr< MemberVoidFromNavPkt< T > > SPtr;
			typedef void (T::*MemberVoidFromNavPktFn)( const FRONTEND::NavigationPacket& data );
			static SPtr Create( T &target, MemberVoidFromNavPktFn func ){
				return SPtr( new MemberVoidFromNavPkt(target, func ) );
			};
			virtual void operator() (const FRONTEND::NavigationPacket& data )
			{
				(target_.*func_)(data);
			}
			MemberVoidFromNavPkt ( T& target,  MemberVoidFromNavPktFn func) :
				target_(target),
				func_(func)
				  {
				  }
		private:
			T& target_;
			MemberVoidFromNavPktFn func_;
	};

	/**
	* Wrap Callback functions as CB objects
	*/

	// for InDigitalTunerPort, InAnalogTunerPort, InFrontendTunerPort
	class StaticCharFromChar : public CharFromChar
	{
	public:
		virtual char* operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticCharFromChar ( CharFromCharFn func) :
			func_(func)
		{
		}
	private:
		CharFromCharFn func_;
	};

	class StaticPropFromChar : public PropFromChar
	{
	public:
		virtual CF::Properties* operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticPropFromChar ( PropFromCharFn func) :
			func_(func)
		{
		}
	private:
		PropFromCharFn func_;
	};

	class StaticDoubleFromChar : public DoubleFromChar
	{
	public:
		virtual CORBA::Double operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticDoubleFromChar ( DoubleFromCharFn func) :
			func_(func)
		{
		}
	private:
		DoubleFromCharFn func_;
	};

	class StaticBooleanFromChar : public BooleanFromChar
	{
	public:
		virtual CORBA::Boolean operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticBooleanFromChar ( BooleanFromCharFn func) :
			func_(func)
		{
		}
	private:
		BooleanFromCharFn func_;
	};

	class StaticFloatFromChar : public FloatFromChar
	{
	public:
		virtual CORBA::Float operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticFloatFromChar ( FloatFromCharFn func) :
			func_(func)
		{
		}
	private:
		FloatFromCharFn func_;
	};

	class StaticLongFromChar : public LongFromChar
	{
	public:
		virtual CORBA::Long operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticLongFromChar ( LongFromCharFn func) :
			func_(func)
		{
		}
	private:
		LongFromCharFn func_;
	};

	class StaticVoidFromCharDouble : public VoidFromCharDouble
	{
	public:
		virtual void operator() ( const char* id, CORBA::Double val)
		{
			return (*func_)(id,val);
		}
		StaticVoidFromCharDouble ( VoidFromCharDoubleFn func) :
			func_(func)
		{
		}
	private:
		VoidFromCharDoubleFn func_;
	};
	class StaticVoidFromCharBoolean : public VoidFromCharBoolean
	{
	public:
		virtual void operator() ( const char* id, CORBA::Boolean val)
		{
			return (*func_)(id,val);
		}
		StaticVoidFromCharBoolean ( VoidFromCharBooleanFn func) :
			func_(func)
		{
		}
	private:
		VoidFromCharBooleanFn func_;
	};
	class StaticVoidFromCharFloat : public VoidFromCharFloat
	{
	public:
		virtual void operator() ( const char* id, CORBA::Float val)
		{
			return (*func_)(id,val);
		}
		StaticVoidFromCharFloat ( VoidFromCharFloatFn func) :
			func_(func)
		{
		}
	private:
		VoidFromCharFloatFn func_;
	};
	class StaticVoidFromCharLong : public VoidFromCharLong
	{
	public:
		virtual void operator() ( const char* id, CORBA::Long val)
		{
			return (*func_)(id,val);
		}
		StaticVoidFromCharLong ( VoidFromCharLongFn func) :
			func_(func)
		{
		}
	private:
		VoidFromCharLongFn func_;
	};

	// for InRFInfoPort, InRFSourcePort
	class StaticCharFromVoid : public CharFromVoid
	{
	public:
		virtual char* operator() ( void )
		{
			return (*func_)();
		}
		StaticCharFromVoid ( CharFromVoidFn func) :
			func_(func)
		{
		}
	private:
		CharFromVoidFn func_;
	};
	class StaticRFInfoPktFromVoid : public RFInfoPktFromVoid
	{
	public:
		virtual FRONTEND::RFInfoPkt* operator() ( void )
		{
			return (*func_)();
		}
		StaticRFInfoPktFromVoid ( RFInfoPktFromVoidFn func) :
			func_(func)
		{
		}
	private:
		RFInfoPktFromVoidFn func_;
	};
	class StaticRFInfoPktSeqFromVoid : public RFInfoPktSeqFromVoid
	{
	public:
		virtual FRONTEND::RFInfoPktSequence* operator() ( void )
		{
			return (*func_)();
		}
		StaticRFInfoPktSeqFromVoid ( RFInfoPktSeqFromVoidFn func) :
			func_(func)
		{
		}
	private:
		RFInfoPktSeqFromVoidFn func_;
	};
	class StaticVoidFromChar : public VoidFromChar
	{
	public:
		virtual void operator() ( const char* data)
		{
			return (*func_)(data);
		}
		StaticVoidFromChar ( VoidFromCharFn func) :
			func_(func)
		{
		}
	private:
		VoidFromCharFn func_;
	};
	class StaticVoidFromRFInfoPkt : public VoidFromRFInfoPkt
	{
	public:
		virtual void operator() ( const FRONTEND::RFInfoPkt& data)
		{
			return (*func_)(data);
		}
		StaticVoidFromRFInfoPkt ( VoidFromRFInfoPktFn func) :
			func_(func)
		{
		}
	private:
		VoidFromRFInfoPktFn func_;
	};
	class StaticVoidFromRFInfoPktSeq : public VoidFromRFInfoPktSeq
	{
	public:
		virtual void operator() ( const FRONTEND::RFInfoPktSequence& data)
		{
			return (*func_)(data);
		}
		StaticVoidFromRFInfoPktSeq ( VoidFromRFInfoPktSeqFn func) :
			func_(func)
		{
		}
	private:
		VoidFromRFInfoPktSeqFn func_;
	};

	// for InGPSPort
	class StaticGPSInfoFromVoid : public GPSInfoFromVoid
	{
	public:
		virtual FRONTEND::GPSInfo* operator() ( void )
		{
			return (*func_)();
		}
		StaticGPSInfoFromVoid ( GPSInfoFromVoidFn func) :
			func_(func)
		{
		}
	private:
		GPSInfoFromVoidFn func_;
	};
	class StaticGpsTimePosFromVoid : public GpsTimePosFromVoid
	{
	public:
		virtual FRONTEND::GpsTimePos* operator() ( void )
		{
			return (*func_)();
		}
		StaticGpsTimePosFromVoid ( GpsTimePosFromVoidFn func) :
			func_(func)
		{
		}
	private:
		GpsTimePosFromVoidFn func_;
	};
	class StaticVoidFromGPSInfo : public VoidFromGPSInfo
	{
	public:
		virtual void operator() ( const FRONTEND::GPSInfo& data)
		{
			return (*func_)(data);
		}
		StaticVoidFromGPSInfo ( VoidFromGPSInfoFn func) :
			func_(func)
		{
		}
	private:
		VoidFromGPSInfoFn func_;
	};
	class StaticVoidFromGpsTimePos : public VoidFromGpsTimePos
	{
	public:
		virtual void operator() ( const FRONTEND::GpsTimePos& data)
		{
			return (*func_)(data);
		}
		StaticVoidFromGpsTimePos ( VoidFromGpsTimePosFn func) :
			func_(func)
		{
		}
	private:
		VoidFromGpsTimePosFn func_;
	};

	// for InNavDataPort
	class StaticNavPktFromVoid : public NavPktFromVoid
	{
	public:
		virtual FRONTEND::NavigationPacket* operator() ( void )
		{
			return (*func_)();
		}
		StaticNavPktFromVoid ( NavPktFromVoidFn func) :
			func_(func)
		{
		}
	private:
		NavPktFromVoidFn func_;
	};
	class StaticVoidFromNavPkt : public VoidFromNavPkt
	{
	public:
		virtual void operator() ( const FRONTEND::NavigationPacket& data)
		{
			return (*func_)(data);
		}
		StaticVoidFromNavPkt ( VoidFromNavPktFn func) :
			func_(func)
		{
		}
	private:
		VoidFromNavPktFn func_;
	};

	// ----------------------------------------------------------------------------------------
	// OutFrontendPort declaration
	// ----------------------------------------------------------------------------------------
	template <typename PortType_var, typename PortType>
	class OutFrontendPort : public Port_Uses_base_impl, public POA_ExtendedCF::QueryablePort
	{
	    public:
			OutFrontendPort(std::string port_name) :
				Port_Uses_base_impl(port_name)
			{
			    recConnectionsRefresh = false;
			    recConnections.length(0);
			}
			OutFrontendPort(std::string port_name,
                                        LOGGER_PTR logger) :
				Port_Uses_base_impl(port_name),
                                logger(logger)
			{
			    recConnectionsRefresh = false;
			    recConnections.length(0);
			}
	        ~OutFrontendPort(){
	        }

                void setLogger(LOGGER_PTR newLogger){
                    logger = newLogger;
                }

	        ExtendedCF::UsesConnectionSequence * connections()
	        {
	            boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in
	            if (recConnectionsRefresh) {
	                recConnections.length(outConnections.size());
	                for (unsigned int i = 0; i < outConnections.size(); i++) {
	                    recConnections[i].connectionId = CORBA::string_dup(outConnections[i].second.c_str());
	                    recConnections[i].port = CORBA::Object::_duplicate(outConnections[i].first);
	                }
	                recConnectionsRefresh = false;
	            }
	            ExtendedCF::UsesConnectionSequence_var retVal = new ExtendedCF::UsesConnectionSequence(recConnections);
	            // NOTE: You must delete the object that this function returns!
	            return retVal._retn();
	        };

	        void connectPort(CORBA::Object_ptr connection, const char* connectionId)
	        {
	            boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in
	            PortType_var port = PortType::_narrow(connection);
	            outConnections.push_back(std::make_pair(port, connectionId));
	            active = true;
	            recConnectionsRefresh = true;
	        };

	        void disconnectPort(const char* connectionId)
	        {
	            boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in
	            for (unsigned int i = 0; i < outConnections.size(); i++) {
	                if (outConnections[i].second == connectionId) {
	                    outConnections.erase(outConnections.begin() + i);
	                    break;
	                }
	            }

	            if (outConnections.size() == 0) {
	                active = false;
	            }
	            recConnectionsRefresh = true;
	        };

	        std::vector< std::pair<PortType_var, std::string> > _getConnections()
	        {
	            return outConnections;
	        };

	    protected:
	        std::vector < std::pair<PortType_var, std::string> > outConnections;
	        ExtendedCF::UsesConnectionSequence recConnections;
	        bool recConnectionsRefresh;

                LOGGER_PTR logger;
	};

} // end of frontend namespace


#endif
