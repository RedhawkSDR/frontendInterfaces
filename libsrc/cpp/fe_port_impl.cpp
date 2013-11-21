/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    Source: USRP_UHD.spd.xml

*******************************************************************************************/

//#include "USRP_UHD.h"

#include "fe_port_impl.h"

namespace frontend {

	/**
	* Wrap Callback functions as CB objects
	*/
	class StaticCharGetterCB : public CharGetterCB
	{
	public:
		virtual char* operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticCharGetterCB ( CharGetterCBFn func) :
			func_(func)
		{
		}
	private:
		CharGetterCBFn func_;
	};

	class StaticPropGetterCB : public PropGetterCB
	{
	public:
		virtual CF::Properties* operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticPropGetterCB ( PropGetterCBFn func) :
			func_(func)
		{
		}
	private:
		PropGetterCBFn func_;
	};

	class StaticDoubleGetterCB : public DoubleGetterCB
	{
	public:
		virtual CORBA::Double operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticDoubleGetterCB ( DoubleGetterCBFn func) :
			func_(func)
		{
		}
	private:
		DoubleGetterCBFn func_;
	};

	class StaticBooleanGetterCB : public BooleanGetterCB
	{
	public:
		virtual CORBA::Boolean operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticBooleanGetterCB ( BooleanGetterCBFn func) :
			func_(func)
		{
		}
	private:
		BooleanGetterCBFn func_;
	};

	class StaticFloatGetterCB : public FloatGetterCB
	{
	public:
		virtual CORBA::Float operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticFloatGetterCB ( FloatGetterCBFn func) :
			func_(func)
		{
		}
	private:
		FloatGetterCBFn func_;
	};

	class StaticLongGetterCB : public LongGetterCB
	{
	public:
		virtual CORBA::Long operator() ( const char* id)
		{
			return (*func_)(id);
		}
		StaticLongGetterCB ( LongGetterCBFn func) :
			func_(func)
		{
		}
	private:
		LongGetterCBFn func_;
	};

	class StaticDoubleSetterCB : public DoubleSetterCB
	{
	public:
		virtual void operator() ( const char* id, CORBA::Double val)
		{
			return (*func_)(id,val);
		}
		StaticDoubleSetterCB ( DoubleSetterCBFn func) :
			func_(func)
		{
		}
	private:
		DoubleSetterCBFn func_;
	};
	class StaticBooleanSetterCB : public BooleanSetterCB
	{
	public:
		virtual void operator() ( const char* id, CORBA::Boolean val)
		{
			return (*func_)(id,val);
		}
		StaticBooleanSetterCB ( BooleanSetterCBFn func) :
			func_(func)
		{
		}
	private:
		BooleanSetterCBFn func_;
	};
	class StaticFloatSetterCB : public FloatSetterCB
	{
	public:
		virtual void operator() ( const char* id, CORBA::Float val)
		{
			return (*func_)(id,val);
		}
		StaticFloatSetterCB ( FloatSetterCBFn func) :
			func_(func)
		{
		}
	private:
		FloatSetterCBFn func_;
	};
	class StaticLongSetterCB : public LongSetterCB
	{
	public:
		virtual void operator() ( const char* id, CORBA::Long val)
		{
			return (*func_)(id,val);
		}
		StaticLongSetterCB ( LongSetterCBFn func) :
			func_(func)
		{
		}
	private:
		LongSetterCBFn func_;
	};

	// ----------------------------------------------------------------------------------------
	// InDigitalTunerPort definition
	// ----------------------------------------------------------------------------------------
	InDigitalTunerPort::InDigitalTunerPort(std::string port_name,
			CharGetterCB *newTunerTypeGetterCB,
			BooleanGetterCB *newTunerDeviceControlGetterCB,
			CharGetterCB *newTunerGroupIdGetterCB,
			CharGetterCB *newTunerRfFlowIdGetterCB,
			PropGetterCB *newTunerStatusGetterCB,
			DoubleGetterCB *newTunerCenterFrequencyGetterCB,
			DoubleSetterCB *newTunerCenterFrequencySetterCB,
			DoubleGetterCB *newTunerBandwidthGetterCB,
			DoubleSetterCB *newTunerBandwidthSetterCB,
			BooleanGetterCB *newTunerAgcEnableGetterCB,
			BooleanSetterCB *newTunerAgcEnableSetterCB,
			FloatGetterCB *newTunerGainGetterCB,
			FloatSetterCB *newTunerGainSetterCB,
			LongGetterCB *newTunerReferenceSourceGetterCB,
			LongSetterCB *newTunerReferenceSourceSetterCB,
			BooleanGetterCB *newTunerEnableGetterCB,
			BooleanSetterCB *newTunerEnableSetterCB,
			DoubleGetterCB *newTunerOutputSampleRateGetterCB,
			DoubleSetterCB *newTunerOutputSampleRateSetterCB)://, USRP_UHD_base *_parent) :
	Port_Provides_base_impl(port_name),
	getTunerTypeCB(),
	getTunerDeviceControlCB(),
	getTunerGroupIdCB(),
	getTunerRfFlowIdCB(),
	getTunerStatusCB(),
	getTunerCenterFrequencyCB(),
	setTunerCenterFrequencyCB(),
	getTunerBandwidthCB(),
	setTunerBandwidthCB(),
	getTunerAgcEnableCB(),
	setTunerAgcEnableCB(),
	getTunerGainCB(),
	setTunerGainCB(),
	getTunerReferenceSourceCB(),
	setTunerReferenceSourceCB(),
	getTunerEnableCB(),
	setTunerEnableCB(),
	getTunerOutputSampleRateCB(),
	setTunerOutputSampleRateCB()
	{
		//parent = static_cast<USRP_UHD_i *> (_parent);
		if ( newTunerTypeGetterCB ) {
			getTunerTypeCB = boost::shared_ptr< CharGetterCB >( newTunerTypeGetterCB, null_deleter());
		}
		if ( newTunerDeviceControlGetterCB ) {
			getTunerDeviceControlCB = boost::shared_ptr< BooleanGetterCB >( newTunerDeviceControlGetterCB, null_deleter());
		}
		if ( newTunerGroupIdGetterCB ) {
			getTunerGroupIdCB = boost::shared_ptr< CharGetterCB >( newTunerGroupIdGetterCB, null_deleter());
		}
		if ( newTunerRfFlowIdGetterCB ) {
			getTunerRfFlowIdCB = boost::shared_ptr< CharGetterCB >( newTunerRfFlowIdGetterCB, null_deleter());
		}
		if ( newTunerStatusGetterCB ) {
			getTunerStatusCB = boost::shared_ptr< PropGetterCB >( newTunerStatusGetterCB, null_deleter());
		}
		if ( newTunerCenterFrequencyGetterCB ) {
			getTunerCenterFrequencyCB = boost::shared_ptr< DoubleGetterCB >( newTunerCenterFrequencyGetterCB, null_deleter());
		}
		if ( newTunerCenterFrequencySetterCB ) {
			setTunerCenterFrequencyCB = boost::shared_ptr< DoubleSetterCB >( newTunerCenterFrequencySetterCB, null_deleter());
		}
		if ( newTunerBandwidthGetterCB ) {
			getTunerBandwidthCB = boost::shared_ptr< DoubleGetterCB >( newTunerBandwidthGetterCB, null_deleter());
		}
		if ( newTunerBandwidthSetterCB ) {
			setTunerBandwidthCB = boost::shared_ptr< DoubleSetterCB >( newTunerBandwidthSetterCB, null_deleter());
		}
		if ( newTunerAgcEnableGetterCB ) {
			getTunerAgcEnableCB = boost::shared_ptr< BooleanGetterCB >( newTunerAgcEnableGetterCB, null_deleter());
		}
		if ( newTunerAgcEnableSetterCB ) {
			setTunerAgcEnableCB = boost::shared_ptr< BooleanSetterCB >( newTunerAgcEnableSetterCB, null_deleter());
		}
		if ( newTunerGainGetterCB ) {
			getTunerGainCB = boost::shared_ptr< FloatGetterCB >( newTunerGainGetterCB, null_deleter());
		}
		if ( newTunerGainSetterCB ) {
			setTunerGainCB = boost::shared_ptr< FloatSetterCB >( newTunerGainSetterCB, null_deleter());
		}
		if ( newTunerReferenceSourceGetterCB ) {
			getTunerReferenceSourceCB = boost::shared_ptr< LongGetterCB >( newTunerReferenceSourceGetterCB, null_deleter());
		}
		if ( newTunerReferenceSourceSetterCB ) {
			setTunerReferenceSourceCB = boost::shared_ptr< LongSetterCB >( newTunerReferenceSourceSetterCB, null_deleter());
		}
		if ( newTunerEnableGetterCB ) {
			getTunerEnableCB = boost::shared_ptr< BooleanGetterCB >( newTunerEnableGetterCB, null_deleter());
		}
		if ( newTunerEnableSetterCB ) {
			setTunerEnableCB = boost::shared_ptr< BooleanSetterCB >( newTunerEnableSetterCB, null_deleter());
		}
		if ( newTunerOutputSampleRateGetterCB ) {
			getTunerOutputSampleRateCB = boost::shared_ptr< DoubleGetterCB >( newTunerOutputSampleRateGetterCB, null_deleter());
		}
		if ( newTunerOutputSampleRateSetterCB ) {
			setTunerOutputSampleRateCB = boost::shared_ptr< DoubleSetterCB >( newTunerOutputSampleRateSetterCB, null_deleter());
		}
	}

	InDigitalTunerPort::~InDigitalTunerPort()
	{
	}

	char* InDigitalTunerPort::getTunerType(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerTypeCB ) return (*getTunerTypeCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerType(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return CORBA::string_dup(parent->tunerChannels[tunerNum].frontend_status->tuner_type.c_str());
	}

	CORBA::Boolean InDigitalTunerPort::getTunerDeviceControl(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerDeviceControlCB ) return (*getTunerDeviceControlCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerDeviceControl(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) == parent->tunerChannels[tunerNum].control_allocation_id)
	//		return true;
	//	return false;
	}

	char* InDigitalTunerPort::getTunerGroupId(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerGroupIdCB ) return (*getTunerGroupIdCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerGroupId(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return CORBA::string_dup(parent->tunerChannels[tunerNum].frontend_status->group_id.c_str());
	}

	char* InDigitalTunerPort::getTunerRfFlowId(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerRfFlowIdCB ) return (*getTunerRfFlowIdCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerRfFlowId(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return CORBA::string_dup(parent->tunerChannels[tunerNum].frontend_status->rf_flow_id.c_str());
	}

	CF::Properties* InDigitalTunerPort::getTunerStatus(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerStatusCB ) return (*getTunerStatusCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerStatus(const char* id) IS NOT CURRENTLY SUPPORTED");
	//    CF::Properties* tmpVal = new CF::Properties();
	//    long tunerNum = parent->getTunerMapping(id);
	//    if (tunerNum < 0)
	//    	throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//    CORBA::Any prop;
	//    prop <<= *(parent->tunerChannels[tunerNum].frontend_status);
	//    prop >>= tmpVal;
	//
	//    CF::Properties_var tmp = new CF::Properties(*tmpVal);
	//    return tmp._retn();
	}

	void InDigitalTunerPort::setTunerCenterFrequency(const char* id, CORBA::Double freq)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerCenterFrequencyCB ) (*setTunerCenterFrequencyCB)(id,freq);
		else throw FRONTEND::NotSupportedException("setTunerCenterFrequency(const char* id, CORBA::Double freq) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tunerNum].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tunerNum);
	//	newParams.allocation_id = std::string(id);
	//	newParams.center_frequency = freq;
	//	try {
	//		parent->setupTuner(tunerNum, newParams);
	//	} catch (std::exception& e) {
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Double InDigitalTunerPort::getTunerCenterFrequency(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerCenterFrequencyCB ) return (*getTunerCenterFrequencyCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerCenterFrequency(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tunerNum].frontend_status->center_frequency;
	}

	void InDigitalTunerPort::setTunerBandwidth(const char* id, CORBA::Double bw)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerBandwidthCB ) (*setTunerBandwidthCB)(id,bw);
		else throw FRONTEND::NotSupportedException("setTunerBandwidth(const char* id, CORBA::Double bw) IS NOT CURRENTLY SUPPORTED");
	//
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tunerNum].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tunerNum);
	//	newParams.allocation_id = std::string(id);
	//	newParams.bandwidth = bw;
	//	try {
	//		parent->setupTuner(tunerNum, newParams);
	//	} catch (std::exception& e) {
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Double InDigitalTunerPort::getTunerBandwidth(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerBandwidthCB ) return (*getTunerBandwidthCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerBandwidth(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tunerNum].frontend_status->bandwidth;
	}

	void InDigitalTunerPort::setTunerAgcEnable(const char* id, CORBA::Boolean enable)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerAgcEnableCB ) (*setTunerAgcEnableCB)(id,enable);
		else throw FRONTEND::NotSupportedException("setTunerAgcEnable(const char* id, CORBA::Boolean enable) IS NOT CURRENTLY SUPPORTED");
	}

	CORBA::Boolean InDigitalTunerPort::getTunerAgcEnable(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerAgcEnableCB ) return (*getTunerAgcEnableCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerAgcEnable(const char* id) IS NOT CURRENTLY SUPPORTED");
	}

	void InDigitalTunerPort::setTunerGain(const char* id, CORBA::Float gain)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerGainCB ) (*setTunerGainCB)(id,gain);
		else throw FRONTEND::NotSupportedException("setTunerGain(const char* id, CORBA::Float gain) IS NOT CURRENTLY SUPPORTED");
	//
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tunerNum].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	//double orig_gain = parent->tunerChannels[tunerNum].frontend_status->gain;
	//	parent->tunerChannels[tunerNum].frontend_status->gain = gain;
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tunerNum);
	//	newParams.allocation_id = std::string(id);
	//	try {
	//		parent->setupTuner(tunerNum, newParams);
	//	} catch (FRONTEND::BadParameterException &e) {
	//		// invalid gain, so undo whatever we did above and reset gain value to what is accurate
	//		//parent->tunerChannels[tunerNum].frontend_status->gain = orig_gain;
	//		size_t usrp_channel_number = parent->myDevice_channel_seq[tunerNum].chan_num;
	//		double actual_gain = parent->usrpDevice->get_rx_gain(usrp_channel_number);
	//		parent->tunerChannels[tunerNum].frontend_status->gain = actual_gain;
	//		throw e;
	//	} catch (std::exception& e) {
	//		// error occurred, reset gain value to what is accurate
	//		size_t usrp_channel_number = parent->myDevice_channel_seq[tunerNum].chan_num;
	//		double actual_gain = parent->usrpDevice->get_rx_gain(usrp_channel_number);
	//		parent->tunerChannels[tunerNum].frontend_status->gain = actual_gain;
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Float InDigitalTunerPort::getTunerGain(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerGainCB ) return (*getTunerGainCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerGain(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tunerNum].frontend_status->gain;
	}

	void InDigitalTunerPort::setTunerReferenceSource(const char* id, CORBA::Long source)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerReferenceSourceCB ) (*setTunerReferenceSourceCB)(id,source);
		else throw FRONTEND::NotSupportedException("setTunerReferenceSource(const char* id, CORBA::Long source) IS NOT CURRENTLY SUPPORTED");
	}

	CORBA::Long InDigitalTunerPort::getTunerReferenceSource(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerReferenceSourceCB ) return (*getTunerReferenceSourceCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerReferenceSource(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//
	//	CORBA::Long ref = 1;
	//	if (parent->clock_ref == "INTERNAL")
	//		ref = 0;
	//	return ref;
	}

	void InDigitalTunerPort::setTunerEnable(const char* id, CORBA::Boolean enable)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerEnableCB ) (*setTunerEnableCB)(id,enable);
		else throw FRONTEND::NotSupportedException("setTunerEnable(const char* id, CORBA::Boolean enable) IS NOT CURRENTLY SUPPORTED");
	//
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tunerNum].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	parent->tunerChannels[tunerNum].frontend_status->enabled = enable;
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tunerNum);
	//	newParams.allocation_id = std::string(id);
	//	try {
	//		parent->setupTuner(tunerNum, newParams);
	//	} catch (std::exception& e) {
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Boolean InDigitalTunerPort::getTunerEnable(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerEnableCB ) return (*getTunerEnableCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerEnable(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tunerNum].frontend_status->enabled;
	}

	void InDigitalTunerPort::setTunerOutputSampleRate(const char* id, CORBA::Double sr)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerOutputSampleRateCB ) (*setTunerOutputSampleRateCB)(id,sr);
		else throw FRONTEND::NotSupportedException("setTunerOutputSampleRate(const char* id, CORBA::Double sr) IS NOT CURRENTLY SUPPORTED");
	//
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tunerNum].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tunerNum);
	//	newParams.allocation_id = std::string(id);
	//	newParams.sample_rate = sr;
	//	try {
	//		parent->setupTuner(tunerNum, newParams);
	//	} catch (std::exception& e) {
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Double InDigitalTunerPort::getTunerOutputSampleRate(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerOutputSampleRateCB ) return (*getTunerOutputSampleRateCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerOutputSampleRate(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tunerNum = parent->getTunerMapping(id);
	//	if (tunerNum < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tunerNum].frontend_status->sample_rate;
	}

	//getTunerTypeCB
	void   InDigitalTunerPort::setTunerTypeGetterCB( CharGetterCB *newCB ) {
		getTunerTypeCB =  boost::shared_ptr< CharGetterCB >(newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerTypeGetterCB( CharGetterCBFn  newCB ) {
		getTunerTypeCB =  boost::make_shared< StaticCharGetterCB >( newCB );
	}

	//getTunerGroupIdCB
	void   InDigitalTunerPort::setTunerGroupIdGetterCB( CharGetterCB *newCB ) {
		getTunerGroupIdCB =  boost::shared_ptr< CharGetterCB >(newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerGroupIdGetterCB( CharGetterCBFn  newCB ) {
		getTunerGroupIdCB =  boost::make_shared< StaticCharGetterCB >( newCB );
	}

	//getTunerRfFlowIdCB
	void   InDigitalTunerPort::setTunerRfFlowIdGetterCB( CharGetterCB *newCB ) {
		getTunerRfFlowIdCB =  boost::shared_ptr< CharGetterCB >(newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerRfFlowIdGetterCB( CharGetterCBFn  newCB ) {
		getTunerRfFlowIdCB =  boost::make_shared< StaticCharGetterCB >( newCB );
	}

	//getTunerDeviceControlCB
	void   InDigitalTunerPort::setTunerDeviceControlGetterCB( BooleanGetterCB *newCB ) {
		getTunerDeviceControlCB =  boost::shared_ptr< BooleanGetterCB >(newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerDeviceControlGetterCB( BooleanGetterCBFn  newCB ) {
		getTunerDeviceControlCB =  boost::make_shared< StaticBooleanGetterCB >( newCB );
	}

	//getTunerStatusCB
	void   InDigitalTunerPort::setTunerStatusGetterCB( PropGetterCB *newCB ) {
		getTunerStatusCB =  boost::shared_ptr< PropGetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerStatusGetterCB( PropGetterCBFn  newCB ) {
		getTunerStatusCB =  boost::make_shared< StaticPropGetterCB >( newCB );
	}

	//getTunerCenterFrequencyCB
	void   InDigitalTunerPort::setTunerCenterFrequencyGetterCB( DoubleGetterCB *newCB ) {
		getTunerCenterFrequencyCB =  boost::shared_ptr< DoubleGetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerCenterFrequencyGetterCB( DoubleGetterCBFn  newCB ) {
		getTunerCenterFrequencyCB =  boost::make_shared< StaticDoubleGetterCB >( newCB );
	}

	//setTunerCenterFrequencyCB
	void   InDigitalTunerPort::setTunerCenterFrequencySetterCB( DoubleSetterCB *newCB ) {
		setTunerCenterFrequencyCB =  boost::shared_ptr< DoubleSetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerCenterFrequencySetterCB( DoubleSetterCBFn  newCB ) {
		setTunerCenterFrequencyCB =  boost::make_shared< StaticDoubleSetterCB >( newCB );
	}

	//getTunerBandwidthCB
	void   InDigitalTunerPort::setTunerBandwidthGetterCB( DoubleGetterCB *newCB ) {
		getTunerBandwidthCB =  boost::shared_ptr< DoubleGetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerBandwidthGetterCB( DoubleGetterCBFn  newCB ) {
		getTunerBandwidthCB =  boost::make_shared< StaticDoubleGetterCB >( newCB );
	}

	//setTunerBandwidthCB
	void   InDigitalTunerPort::setTunerBandwidthSetterCB( DoubleSetterCB *newCB ) {
		setTunerBandwidthCB =  boost::shared_ptr< DoubleSetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerBandwidthSetterCB( DoubleSetterCBFn  newCB ) {
		setTunerBandwidthCB =  boost::make_shared< StaticDoubleSetterCB >( newCB );
	}

	//getTunerAgcEnableCB
	void   InDigitalTunerPort::setTunerAgcEnableGetterCB( BooleanGetterCB *newCB ) {
		getTunerAgcEnableCB =  boost::shared_ptr< BooleanGetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerAgcEnableGetterCB( BooleanGetterCBFn  newCB ) {
		getTunerAgcEnableCB =  boost::make_shared< StaticBooleanGetterCB >( newCB );
	}

	//setTunerAgcEnableCB
	void   InDigitalTunerPort::setTunerAgcEnableSetterCB( BooleanSetterCB *newCB ) {
		setTunerAgcEnableCB =  boost::shared_ptr< BooleanSetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerAgcEnableSetterCB( BooleanSetterCBFn  newCB ) {
		setTunerAgcEnableCB =  boost::make_shared< StaticBooleanSetterCB >( newCB );
	}

	//getTunerGainCB
	void   InDigitalTunerPort::setTunerGainGetterCB( FloatGetterCB *newCB ) {
		getTunerGainCB =  boost::shared_ptr< FloatGetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerGainGetterCB( FloatGetterCBFn  newCB ) {
		getTunerGainCB =  boost::make_shared< StaticFloatGetterCB >( newCB );
	}

	//setTunerGainCB
	void   InDigitalTunerPort::setTunerGainSetterCB( FloatSetterCB *newCB ) {
		setTunerGainCB =  boost::shared_ptr< FloatSetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerGainSetterCB( FloatSetterCBFn  newCB ) {
		setTunerGainCB =  boost::make_shared< StaticFloatSetterCB >( newCB );
	}

	//getTunerReferenceSourceCB
	void   InDigitalTunerPort::setTunerReferenceSourceGetterCB( LongGetterCB *newCB ) {
		getTunerReferenceSourceCB =  boost::shared_ptr< LongGetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerReferenceSourceGetterCB( LongGetterCBFn  newCB ) {
		getTunerReferenceSourceCB =  boost::make_shared< StaticLongGetterCB >( newCB );
	}

	//setTunerReferenceSourceCB
	void   InDigitalTunerPort::setTunerReferenceSourceSetterCB( LongSetterCB *newCB ) {
		setTunerReferenceSourceCB =  boost::shared_ptr< LongSetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerReferenceSourceSetterCB( LongSetterCBFn  newCB ) {
		setTunerReferenceSourceCB =  boost::make_shared< StaticLongSetterCB >( newCB );
	}

	//getTunerEnableCB
	void   InDigitalTunerPort::setTunerEnableGetterCB( BooleanGetterCB *newCB ) {
		getTunerEnableCB =  boost::shared_ptr< BooleanGetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerEnableGetterCB( BooleanGetterCBFn  newCB ) {
		getTunerEnableCB =  boost::make_shared< StaticBooleanGetterCB >( newCB );
	}

	//setTunerEnableCB
	void   InDigitalTunerPort::setTunerEnableSetterCB( BooleanSetterCB *newCB ) {
		setTunerEnableCB =  boost::shared_ptr< BooleanSetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerEnableSetterCB( BooleanSetterCBFn  newCB ) {
		setTunerEnableCB =  boost::make_shared< StaticBooleanSetterCB >( newCB );
	}

	//getTunerOutputSampleRateCB
	void   InDigitalTunerPort::setTunerOutputSampleRateGetterCB( DoubleGetterCB *newCB ) {
		getTunerOutputSampleRateCB =  boost::shared_ptr< DoubleGetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerOutputSampleRateGetterCB( DoubleGetterCBFn  newCB ) {
		getTunerOutputSampleRateCB =  boost::make_shared< StaticDoubleGetterCB >( newCB );
	}

	//setTunerOutputSampleRateCB
	void   InDigitalTunerPort::setTunerOutputSampleRateSetterCB( DoubleSetterCB *newCB ) {
		setTunerOutputSampleRateCB =  boost::shared_ptr< DoubleSetterCB >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerOutputSampleRateSetterCB( DoubleSetterCBFn  newCB ) {
		setTunerOutputSampleRateCB =  boost::make_shared< StaticDoubleSetterCB >( newCB );
	}


} // end of frontend namespace

