
#include "fe_tuner_port_impl.h"
#include "fe_log.h"

namespace frontend {

	// ----------------------------------------------------------------------------------------
	// InFrontendTunerPort definition
	// ----------------------------------------------------------------------------------------
	InFrontendTunerPort::InFrontendTunerPort(std::string port_name,
			CharFromChar *newTunerTypeGetterCB,
			BooleanFromChar *newTunerDeviceControlGetterCB,
			CharFromChar *newTunerGroupIdGetterCB,
			CharFromChar *newTunerRfFlowIdGetterCB,
			PropFromChar *newTunerStatusGetterCB):
	Port_Provides_base_impl(port_name),
	getTunerTypeCB(),
	getTunerDeviceControlCB(),
	getTunerGroupIdCB(),
	getTunerRfFlowIdCB(),
	getTunerStatusCB()
	{
		if ( newTunerTypeGetterCB ) {
			getTunerTypeCB = boost::shared_ptr< CharFromChar >( newTunerTypeGetterCB, null_deleter());
		}
		if ( newTunerDeviceControlGetterCB ) {
			getTunerDeviceControlCB = boost::shared_ptr< BooleanFromChar >( newTunerDeviceControlGetterCB, null_deleter());
		}
		if ( newTunerGroupIdGetterCB ) {
			getTunerGroupIdCB = boost::shared_ptr< CharFromChar >( newTunerGroupIdGetterCB, null_deleter());
		}
		if ( newTunerRfFlowIdGetterCB ) {
			getTunerRfFlowIdCB = boost::shared_ptr< CharFromChar >( newTunerRfFlowIdGetterCB, null_deleter());
		}
		if ( newTunerStatusGetterCB ) {
			getTunerStatusCB = boost::shared_ptr< PropFromChar >( newTunerStatusGetterCB, null_deleter());
		}
	}

	InFrontendTunerPort::InFrontendTunerPort(std::string port_name,
                        LOGGER_PTR logger,
			CharFromChar *newTunerTypeGetterCB,
			BooleanFromChar *newTunerDeviceControlGetterCB,
			CharFromChar *newTunerGroupIdGetterCB,
			CharFromChar *newTunerRfFlowIdGetterCB,
			PropFromChar *newTunerStatusGetterCB):
	Port_Provides_base_impl(port_name),
        logger(logger),
	getTunerTypeCB(),
	getTunerDeviceControlCB(),
	getTunerGroupIdCB(),
	getTunerRfFlowIdCB(),
	getTunerStatusCB()
	{
		if ( newTunerTypeGetterCB ) {
			getTunerTypeCB = boost::shared_ptr< CharFromChar >( newTunerTypeGetterCB, null_deleter());
		}
		if ( newTunerDeviceControlGetterCB ) {
			getTunerDeviceControlCB = boost::shared_ptr< BooleanFromChar >( newTunerDeviceControlGetterCB, null_deleter());
		}
		if ( newTunerGroupIdGetterCB ) {
			getTunerGroupIdCB = boost::shared_ptr< CharFromChar >( newTunerGroupIdGetterCB, null_deleter());
		}
		if ( newTunerRfFlowIdGetterCB ) {
			getTunerRfFlowIdCB = boost::shared_ptr< CharFromChar >( newTunerRfFlowIdGetterCB, null_deleter());
		}
		if ( newTunerStatusGetterCB ) {
			getTunerStatusCB = boost::shared_ptr< PropFromChar >( newTunerStatusGetterCB, null_deleter());
		}
	}

	InFrontendTunerPort::~InFrontendTunerPort()
	{
	}

	void InFrontendTunerPort::setLogger(LOGGER_PTR newLogger){
            logger = newLogger;
        }

	char* InFrontendTunerPort::getTunerType(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerTypeCB ) return (*getTunerTypeCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerType(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return CORBA::string_dup(parent->tunerChannels[tuner_id].frontend_status->tuner_type.c_str());
	}

	CORBA::Boolean InFrontendTunerPort::getTunerDeviceControl(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerDeviceControlCB ) return (*getTunerDeviceControlCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerDeviceControl(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) == parent->tunerChannels[tuner_id].control_allocation_id)
	//		return true;
	//	return false;
	}

	char* InFrontendTunerPort::getTunerGroupId(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerGroupIdCB ) return (*getTunerGroupIdCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerGroupId(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return CORBA::string_dup(parent->tunerChannels[tuner_id].frontend_status->group_id.c_str());
	}

	char* InFrontendTunerPort::getTunerRfFlowId(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerRfFlowIdCB ) return (*getTunerRfFlowIdCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerRfFlowId(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return CORBA::string_dup(parent->tunerChannels[tuner_id].frontend_status->rf_flow_id.c_str());
	}

	CF::Properties* InFrontendTunerPort::getTunerStatus(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerStatusCB ) return (*getTunerStatusCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerStatus(const char* id) IS NOT CURRENTLY SUPPORTED");
	//    CF::Properties* tmpVal = new CF::Properties();
	//    long tuner_id = parent->getTunerMapping(id);
	//    if (tuner_id < 0)
	//    	throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//    CORBA::Any prop;
	//    prop <<= *(parent->tunerChannels[tuner_id].frontend_status);
	//    prop >>= tmpVal;
	//
	//    CF::Properties_var tmp = new CF::Properties(*tmpVal);
	//    return tmp._retn();
	}

	//getTunerTypeCB
	void   InFrontendTunerPort::setTunerTypeGetterCB( CharFromChar *newCB ) {
		getTunerTypeCB =  boost::shared_ptr< CharFromChar >(newCB, null_deleter());
	}
	void   InFrontendTunerPort::setTunerTypeGetterCB( CharFromCharFn  newCB ) {
		getTunerTypeCB =  boost::make_shared< StaticCharFromChar >( newCB );
	}

	//getTunerGroupIdCB
	void   InFrontendTunerPort::setTunerGroupIdGetterCB( CharFromChar *newCB ) {
		getTunerGroupIdCB =  boost::shared_ptr< CharFromChar >(newCB, null_deleter());
	}
	void   InFrontendTunerPort::setTunerGroupIdGetterCB( CharFromCharFn  newCB ) {
		getTunerGroupIdCB =  boost::make_shared< StaticCharFromChar >( newCB );
	}

	//getTunerRfFlowIdCB
	void   InFrontendTunerPort::setTunerRfFlowIdGetterCB( CharFromChar *newCB ) {
		getTunerRfFlowIdCB =  boost::shared_ptr< CharFromChar >(newCB, null_deleter());
	}
	void   InFrontendTunerPort::setTunerRfFlowIdGetterCB( CharFromCharFn  newCB ) {
		getTunerRfFlowIdCB =  boost::make_shared< StaticCharFromChar >( newCB );
	}

	//getTunerDeviceControlCB
	void   InFrontendTunerPort::setTunerDeviceControlGetterCB( BooleanFromChar *newCB ) {
		getTunerDeviceControlCB =  boost::shared_ptr< BooleanFromChar >(newCB, null_deleter());
	}
	void   InFrontendTunerPort::setTunerDeviceControlGetterCB( BooleanFromCharFn  newCB ) {
		getTunerDeviceControlCB =  boost::make_shared< StaticBooleanFromChar >( newCB );
	}

	//getTunerStatusCB
	void   InFrontendTunerPort::setTunerStatusGetterCB( PropFromChar *newCB ) {
		getTunerStatusCB =  boost::shared_ptr< PropFromChar >( newCB, null_deleter());
	}
	void   InFrontendTunerPort::setTunerStatusGetterCB( PropFromCharFn  newCB ) {
		getTunerStatusCB =  boost::make_shared< StaticPropFromChar >( newCB );
	}

	// ----------------------------------------------------------------------------------------
	// InAnalogTunerPort definition
	// ----------------------------------------------------------------------------------------
	InAnalogTunerPort::InAnalogTunerPort(std::string port_name,
			CharFromChar *newTunerTypeGetterCB,
			BooleanFromChar *newTunerDeviceControlGetterCB,
			CharFromChar *newTunerGroupIdGetterCB,
			CharFromChar *newTunerRfFlowIdGetterCB,
			PropFromChar *newTunerStatusGetterCB,
			DoubleFromChar *newTunerCenterFrequencyGetterCB,
			VoidFromCharDouble *newTunerCenterFrequencySetterCB,
			DoubleFromChar *newTunerBandwidthGetterCB,
			VoidFromCharDouble *newTunerBandwidthSetterCB,
			BooleanFromChar *newTunerAgcEnableGetterCB,
			VoidFromCharBoolean *newTunerAgcEnableSetterCB,
			FloatFromChar *newTunerGainGetterCB,
			VoidFromCharFloat *newTunerGainSetterCB,
			LongFromChar *newTunerReferenceSourceGetterCB,
			VoidFromCharLong *newTunerReferenceSourceSetterCB,
			BooleanFromChar *newTunerEnableGetterCB,
			VoidFromCharBoolean *newTunerEnableSetterCB):
	InFrontendTunerPort(port_name,
			newTunerTypeGetterCB,
			newTunerDeviceControlGetterCB,
			newTunerGroupIdGetterCB,
			newTunerRfFlowIdGetterCB,
			newTunerStatusGetterCB),
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
	setTunerEnableCB()
	{
		if ( newTunerCenterFrequencyGetterCB ) {
			getTunerCenterFrequencyCB = boost::shared_ptr< DoubleFromChar >( newTunerCenterFrequencyGetterCB, null_deleter());
		}
		if ( newTunerCenterFrequencySetterCB ) {
			setTunerCenterFrequencyCB = boost::shared_ptr< VoidFromCharDouble >( newTunerCenterFrequencySetterCB, null_deleter());
		}
		if ( newTunerBandwidthGetterCB ) {
			getTunerBandwidthCB = boost::shared_ptr< DoubleFromChar >( newTunerBandwidthGetterCB, null_deleter());
		}
		if ( newTunerBandwidthSetterCB ) {
			setTunerBandwidthCB = boost::shared_ptr< VoidFromCharDouble >( newTunerBandwidthSetterCB, null_deleter());
		}
		if ( newTunerAgcEnableGetterCB ) {
			getTunerAgcEnableCB = boost::shared_ptr< BooleanFromChar >( newTunerAgcEnableGetterCB, null_deleter());
		}
		if ( newTunerAgcEnableSetterCB ) {
			setTunerAgcEnableCB = boost::shared_ptr< VoidFromCharBoolean >( newTunerAgcEnableSetterCB, null_deleter());
		}
		if ( newTunerGainGetterCB ) {
			getTunerGainCB = boost::shared_ptr< FloatFromChar >( newTunerGainGetterCB, null_deleter());
		}
		if ( newTunerGainSetterCB ) {
			setTunerGainCB = boost::shared_ptr< VoidFromCharFloat >( newTunerGainSetterCB, null_deleter());
		}
		if ( newTunerReferenceSourceGetterCB ) {
			getTunerReferenceSourceCB = boost::shared_ptr< LongFromChar >( newTunerReferenceSourceGetterCB, null_deleter());
		}
		if ( newTunerReferenceSourceSetterCB ) {
			setTunerReferenceSourceCB = boost::shared_ptr< VoidFromCharLong >( newTunerReferenceSourceSetterCB, null_deleter());
		}
		if ( newTunerEnableGetterCB ) {
			getTunerEnableCB = boost::shared_ptr< BooleanFromChar >( newTunerEnableGetterCB, null_deleter());
		}
		if ( newTunerEnableSetterCB ) {
			setTunerEnableCB = boost::shared_ptr< VoidFromCharBoolean >( newTunerEnableSetterCB, null_deleter());
		}
	}

	InAnalogTunerPort::InAnalogTunerPort(std::string port_name,
                        LOGGER_PTR logger,
			CharFromChar *newTunerTypeGetterCB,
			BooleanFromChar *newTunerDeviceControlGetterCB,
			CharFromChar *newTunerGroupIdGetterCB,
			CharFromChar *newTunerRfFlowIdGetterCB,
			PropFromChar *newTunerStatusGetterCB,
			DoubleFromChar *newTunerCenterFrequencyGetterCB,
			VoidFromCharDouble *newTunerCenterFrequencySetterCB,
			DoubleFromChar *newTunerBandwidthGetterCB,
			VoidFromCharDouble *newTunerBandwidthSetterCB,
			BooleanFromChar *newTunerAgcEnableGetterCB,
			VoidFromCharBoolean *newTunerAgcEnableSetterCB,
			FloatFromChar *newTunerGainGetterCB,
			VoidFromCharFloat *newTunerGainSetterCB,
			LongFromChar *newTunerReferenceSourceGetterCB,
			VoidFromCharLong *newTunerReferenceSourceSetterCB,
			BooleanFromChar *newTunerEnableGetterCB,
			VoidFromCharBoolean *newTunerEnableSetterCB):
	InFrontendTunerPort(port_name,
                        logger,
			newTunerTypeGetterCB,
			newTunerDeviceControlGetterCB,
			newTunerGroupIdGetterCB,
			newTunerRfFlowIdGetterCB,
			newTunerStatusGetterCB),
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
	setTunerEnableCB()
	{
		if ( newTunerCenterFrequencyGetterCB ) {
			getTunerCenterFrequencyCB = boost::shared_ptr< DoubleFromChar >( newTunerCenterFrequencyGetterCB, null_deleter());
		}
		if ( newTunerCenterFrequencySetterCB ) {
			setTunerCenterFrequencyCB = boost::shared_ptr< VoidFromCharDouble >( newTunerCenterFrequencySetterCB, null_deleter());
		}
		if ( newTunerBandwidthGetterCB ) {
			getTunerBandwidthCB = boost::shared_ptr< DoubleFromChar >( newTunerBandwidthGetterCB, null_deleter());
		}
		if ( newTunerBandwidthSetterCB ) {
			setTunerBandwidthCB = boost::shared_ptr< VoidFromCharDouble >( newTunerBandwidthSetterCB, null_deleter());
		}
		if ( newTunerAgcEnableGetterCB ) {
			getTunerAgcEnableCB = boost::shared_ptr< BooleanFromChar >( newTunerAgcEnableGetterCB, null_deleter());
		}
		if ( newTunerAgcEnableSetterCB ) {
			setTunerAgcEnableCB = boost::shared_ptr< VoidFromCharBoolean >( newTunerAgcEnableSetterCB, null_deleter());
		}
		if ( newTunerGainGetterCB ) {
			getTunerGainCB = boost::shared_ptr< FloatFromChar >( newTunerGainGetterCB, null_deleter());
		}
		if ( newTunerGainSetterCB ) {
			setTunerGainCB = boost::shared_ptr< VoidFromCharFloat >( newTunerGainSetterCB, null_deleter());
		}
		if ( newTunerReferenceSourceGetterCB ) {
			getTunerReferenceSourceCB = boost::shared_ptr< LongFromChar >( newTunerReferenceSourceGetterCB, null_deleter());
		}
		if ( newTunerReferenceSourceSetterCB ) {
			setTunerReferenceSourceCB = boost::shared_ptr< VoidFromCharLong >( newTunerReferenceSourceSetterCB, null_deleter());
		}
		if ( newTunerEnableGetterCB ) {
			getTunerEnableCB = boost::shared_ptr< BooleanFromChar >( newTunerEnableGetterCB, null_deleter());
		}
		if ( newTunerEnableSetterCB ) {
			setTunerEnableCB = boost::shared_ptr< VoidFromCharBoolean >( newTunerEnableSetterCB, null_deleter());
		}
	}

	InAnalogTunerPort::~InAnalogTunerPort()
	{
	}

	void InAnalogTunerPort::setTunerCenterFrequency(const char* id, CORBA::Double freq)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerCenterFrequencyCB ) (*setTunerCenterFrequencyCB)(id,freq);
		else throw FRONTEND::NotSupportedException("setTunerCenterFrequency(const char* id, CORBA::Double freq) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tuner_id].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tuner_id);
	//	newParams.allocation_id = std::string(id);
	//	newParams.center_frequency = freq;
	//	try {
	//		parent->setupTuner(tuner_id, newParams);
	//	} catch (std::exception& e) {
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Double InAnalogTunerPort::getTunerCenterFrequency(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerCenterFrequencyCB ) return (*getTunerCenterFrequencyCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerCenterFrequency(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tuner_id].frontend_status->center_frequency;
	}

	void InAnalogTunerPort::setTunerBandwidth(const char* id, CORBA::Double bw)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerBandwidthCB ) (*setTunerBandwidthCB)(id,bw);
		else throw FRONTEND::NotSupportedException("setTunerBandwidth(const char* id, CORBA::Double bw) IS NOT CURRENTLY SUPPORTED");
	//
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tuner_id].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tuner_id);
	//	newParams.allocation_id = std::string(id);
	//	newParams.bandwidth = bw;
	//	try {
	//		parent->setupTuner(tuner_id, newParams);
	//	} catch (std::exception& e) {
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Double InAnalogTunerPort::getTunerBandwidth(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerBandwidthCB ) return (*getTunerBandwidthCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerBandwidth(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tuner_id].frontend_status->bandwidth;
	}

	void InAnalogTunerPort::setTunerAgcEnable(const char* id, CORBA::Boolean enable)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerAgcEnableCB ) (*setTunerAgcEnableCB)(id,enable);
		else throw FRONTEND::NotSupportedException("setTunerAgcEnable(const char* id, CORBA::Boolean enable) IS NOT CURRENTLY SUPPORTED");
	}

	CORBA::Boolean InAnalogTunerPort::getTunerAgcEnable(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerAgcEnableCB ) return (*getTunerAgcEnableCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerAgcEnable(const char* id) IS NOT CURRENTLY SUPPORTED");
	}

	void InAnalogTunerPort::setTunerGain(const char* id, CORBA::Float gain)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerGainCB ) (*setTunerGainCB)(id,gain);
		else throw FRONTEND::NotSupportedException("setTunerGain(const char* id, CORBA::Float gain) IS NOT CURRENTLY SUPPORTED");
	//
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tuner_id].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	//double orig_gain = parent->tunerChannels[tuner_id].frontend_status->gain;
	//	parent->tunerChannels[tuner_id].frontend_status->gain = gain;
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tuner_id);
	//	newParams.allocation_id = std::string(id);
	//	try {
	//		parent->setupTuner(tuner_id, newParams);
	//	} catch (FRONTEND::BadParameterException &e) {
	//		// invalid gain, so undo whatever we did above and reset gain value to what is accurate
	//		//parent->tunerChannels[tuner_id].frontend_status->gain = orig_gain;
	//		size_t usrp_channel_number = parent->myDevice_channel_seq[tuner_id].chan_num;
	//		double actual_gain = parent->usrpDevice->get_rx_gain(usrp_channel_number);
	//		parent->tunerChannels[tuner_id].frontend_status->gain = actual_gain;
	//		throw e;
	//	} catch (std::exception& e) {
	//		// error occurred, reset gain value to what is accurate
	//		size_t usrp_channel_number = parent->myDevice_channel_seq[tuner_id].chan_num;
	//		double actual_gain = parent->usrpDevice->get_rx_gain(usrp_channel_number);
	//		parent->tunerChannels[tuner_id].frontend_status->gain = actual_gain;
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Float InAnalogTunerPort::getTunerGain(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerGainCB ) return (*getTunerGainCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerGain(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tuner_id].frontend_status->gain;
	}

	void InAnalogTunerPort::setTunerReferenceSource(const char* id, CORBA::Long source)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerReferenceSourceCB ) (*setTunerReferenceSourceCB)(id,source);
		else throw FRONTEND::NotSupportedException("setTunerReferenceSource(const char* id, CORBA::Long source) IS NOT CURRENTLY SUPPORTED");
	}

	CORBA::Long InAnalogTunerPort::getTunerReferenceSource(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerReferenceSourceCB ) return (*getTunerReferenceSourceCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerReferenceSource(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//
	//	CORBA::Long ref = 1;
	//	if (parent->clock_ref == "INTERNAL")
	//		ref = 0;
	//	return ref;
	}

	void InAnalogTunerPort::setTunerEnable(const char* id, CORBA::Boolean enable)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerEnableCB ) (*setTunerEnableCB)(id,enable);
		else throw FRONTEND::NotSupportedException("setTunerEnable(const char* id, CORBA::Boolean enable) IS NOT CURRENTLY SUPPORTED");
	//
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tuner_id].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	parent->tunerChannels[tuner_id].frontend_status->enabled = enable;
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tuner_id);
	//	newParams.allocation_id = std::string(id);
	//	try {
	//		parent->setupTuner(tuner_id, newParams);
	//	} catch (std::exception& e) {
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Boolean InAnalogTunerPort::getTunerEnable(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerEnableCB ) return (*getTunerEnableCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerEnable(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tuner_id].frontend_status->enabled;
	}

	//getTunerCenterFrequencyCB
	void   InAnalogTunerPort::setTunerCenterFrequencyGetterCB( DoubleFromChar *newCB ) {
		getTunerCenterFrequencyCB =  boost::shared_ptr< DoubleFromChar >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerCenterFrequencyGetterCB( DoubleFromCharFn  newCB ) {
		getTunerCenterFrequencyCB =  boost::make_shared< StaticDoubleFromChar >( newCB );
	}

	//setTunerCenterFrequencyCB
	void   InAnalogTunerPort::setTunerCenterFrequencySetterCB( VoidFromCharDouble *newCB ) {
		setTunerCenterFrequencyCB =  boost::shared_ptr< VoidFromCharDouble >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerCenterFrequencySetterCB( VoidFromCharDoubleFn  newCB ) {
		setTunerCenterFrequencyCB =  boost::make_shared< StaticVoidFromCharDouble >( newCB );
	}

	//getTunerBandwidthCB
	void   InAnalogTunerPort::setTunerBandwidthGetterCB( DoubleFromChar *newCB ) {
		getTunerBandwidthCB =  boost::shared_ptr< DoubleFromChar >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerBandwidthGetterCB( DoubleFromCharFn  newCB ) {
		getTunerBandwidthCB =  boost::make_shared< StaticDoubleFromChar >( newCB );
	}

	//setTunerBandwidthCB
	void   InAnalogTunerPort::setTunerBandwidthSetterCB( VoidFromCharDouble *newCB ) {
		setTunerBandwidthCB =  boost::shared_ptr< VoidFromCharDouble >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerBandwidthSetterCB( VoidFromCharDoubleFn  newCB ) {
		setTunerBandwidthCB =  boost::make_shared< StaticVoidFromCharDouble >( newCB );
	}

	//getTunerAgcEnableCB
	void   InAnalogTunerPort::setTunerAgcEnableGetterCB( BooleanFromChar *newCB ) {
		getTunerAgcEnableCB =  boost::shared_ptr< BooleanFromChar >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerAgcEnableGetterCB( BooleanFromCharFn  newCB ) {
		getTunerAgcEnableCB =  boost::make_shared< StaticBooleanFromChar >( newCB );
	}

	//setTunerAgcEnableCB
	void   InAnalogTunerPort::setTunerAgcEnableSetterCB( VoidFromCharBoolean *newCB ) {
		setTunerAgcEnableCB =  boost::shared_ptr< VoidFromCharBoolean >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerAgcEnableSetterCB( VoidFromCharBooleanFn  newCB ) {
		setTunerAgcEnableCB =  boost::make_shared< StaticVoidFromCharBoolean >( newCB );
	}

	//getTunerGainCB
	void   InAnalogTunerPort::setTunerGainGetterCB( FloatFromChar *newCB ) {
		getTunerGainCB =  boost::shared_ptr< FloatFromChar >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerGainGetterCB( FloatFromCharFn  newCB ) {
		getTunerGainCB =  boost::make_shared< StaticFloatFromChar >( newCB );
	}

	//setTunerGainCB
	void   InAnalogTunerPort::setTunerGainSetterCB( VoidFromCharFloat *newCB ) {
		setTunerGainCB =  boost::shared_ptr< VoidFromCharFloat >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerGainSetterCB( VoidFromCharFloatFn  newCB ) {
		setTunerGainCB =  boost::make_shared< StaticVoidFromCharFloat >( newCB );
	}

	//getTunerReferenceSourceCB
	void   InAnalogTunerPort::setTunerReferenceSourceGetterCB( LongFromChar *newCB ) {
		getTunerReferenceSourceCB =  boost::shared_ptr< LongFromChar >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerReferenceSourceGetterCB( LongFromCharFn  newCB ) {
		getTunerReferenceSourceCB =  boost::make_shared< StaticLongFromChar >( newCB );
	}

	//setTunerReferenceSourceCB
	void   InAnalogTunerPort::setTunerReferenceSourceSetterCB( VoidFromCharLong *newCB ) {
		setTunerReferenceSourceCB =  boost::shared_ptr< VoidFromCharLong >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerReferenceSourceSetterCB( VoidFromCharLongFn  newCB ) {
		setTunerReferenceSourceCB =  boost::make_shared< StaticVoidFromCharLong >( newCB );
	}

	//getTunerEnableCB
	void   InAnalogTunerPort::setTunerEnableGetterCB( BooleanFromChar *newCB ) {
		getTunerEnableCB =  boost::shared_ptr< BooleanFromChar >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerEnableGetterCB( BooleanFromCharFn  newCB ) {
		getTunerEnableCB =  boost::make_shared< StaticBooleanFromChar >( newCB );
	}

	//setTunerEnableCB
	void   InAnalogTunerPort::setTunerEnableSetterCB( VoidFromCharBoolean *newCB ) {
		setTunerEnableCB =  boost::shared_ptr< VoidFromCharBoolean >( newCB, null_deleter());
	}
	void   InAnalogTunerPort::setTunerEnableSetterCB( VoidFromCharBooleanFn  newCB ) {
		setTunerEnableCB =  boost::make_shared< StaticVoidFromCharBoolean >( newCB );
	}


	// ----------------------------------------------------------------------------------------
	// InDigitalTunerPort definition
	// ----------------------------------------------------------------------------------------
	InDigitalTunerPort::InDigitalTunerPort(std::string port_name,
			CharFromChar *newTunerTypeGetterCB,
			BooleanFromChar *newTunerDeviceControlGetterCB,
			CharFromChar *newTunerGroupIdGetterCB,
			CharFromChar *newTunerRfFlowIdGetterCB,
			PropFromChar *newTunerStatusGetterCB,
			DoubleFromChar *newTunerCenterFrequencyGetterCB,
			VoidFromCharDouble *newTunerCenterFrequencySetterCB,
			DoubleFromChar *newTunerBandwidthGetterCB,
			VoidFromCharDouble *newTunerBandwidthSetterCB,
			BooleanFromChar *newTunerAgcEnableGetterCB,
			VoidFromCharBoolean *newTunerAgcEnableSetterCB,
			FloatFromChar *newTunerGainGetterCB,
			VoidFromCharFloat *newTunerGainSetterCB,
			LongFromChar *newTunerReferenceSourceGetterCB,
			VoidFromCharLong *newTunerReferenceSourceSetterCB,
			BooleanFromChar *newTunerEnableGetterCB,
			VoidFromCharBoolean *newTunerEnableSetterCB,
			DoubleFromChar *newTunerOutputSampleRateGetterCB,
			VoidFromCharDouble *newTunerOutputSampleRateSetterCB):
	InAnalogTunerPort(port_name,
			newTunerTypeGetterCB,
			newTunerDeviceControlGetterCB,
			newTunerGroupIdGetterCB,
			newTunerRfFlowIdGetterCB,
			newTunerStatusGetterCB,
			newTunerCenterFrequencyGetterCB,
			newTunerCenterFrequencySetterCB,
			newTunerBandwidthGetterCB,
			newTunerBandwidthSetterCB,
			newTunerAgcEnableGetterCB,
			newTunerAgcEnableSetterCB,
			newTunerGainGetterCB,
			newTunerGainSetterCB,
			newTunerReferenceSourceGetterCB,
			newTunerReferenceSourceSetterCB,
			newTunerEnableGetterCB,
			newTunerEnableSetterCB),
	getTunerOutputSampleRateCB(),
	setTunerOutputSampleRateCB()
	{
		if ( newTunerOutputSampleRateGetterCB ) {
			getTunerOutputSampleRateCB = boost::shared_ptr< DoubleFromChar >( newTunerOutputSampleRateGetterCB, null_deleter());
		}
		if ( newTunerOutputSampleRateSetterCB ) {
			setTunerOutputSampleRateCB = boost::shared_ptr< VoidFromCharDouble >( newTunerOutputSampleRateSetterCB, null_deleter());
		}
	}

	InDigitalTunerPort::InDigitalTunerPort(std::string port_name,
                        LOGGER_PTR logger,
			CharFromChar *newTunerTypeGetterCB,
			BooleanFromChar *newTunerDeviceControlGetterCB,
			CharFromChar *newTunerGroupIdGetterCB,
			CharFromChar *newTunerRfFlowIdGetterCB,
			PropFromChar *newTunerStatusGetterCB,
			DoubleFromChar *newTunerCenterFrequencyGetterCB,
			VoidFromCharDouble *newTunerCenterFrequencySetterCB,
			DoubleFromChar *newTunerBandwidthGetterCB,
			VoidFromCharDouble *newTunerBandwidthSetterCB,
			BooleanFromChar *newTunerAgcEnableGetterCB,
			VoidFromCharBoolean *newTunerAgcEnableSetterCB,
			FloatFromChar *newTunerGainGetterCB,
			VoidFromCharFloat *newTunerGainSetterCB,
			LongFromChar *newTunerReferenceSourceGetterCB,
			VoidFromCharLong *newTunerReferenceSourceSetterCB,
			BooleanFromChar *newTunerEnableGetterCB,
			VoidFromCharBoolean *newTunerEnableSetterCB,
			DoubleFromChar *newTunerOutputSampleRateGetterCB,
			VoidFromCharDouble *newTunerOutputSampleRateSetterCB):
	InAnalogTunerPort(port_name,
                        logger,
			newTunerTypeGetterCB,
			newTunerDeviceControlGetterCB,
			newTunerGroupIdGetterCB,
			newTunerRfFlowIdGetterCB,
			newTunerStatusGetterCB,
			newTunerCenterFrequencyGetterCB,
			newTunerCenterFrequencySetterCB,
			newTunerBandwidthGetterCB,
			newTunerBandwidthSetterCB,
			newTunerAgcEnableGetterCB,
			newTunerAgcEnableSetterCB,
			newTunerGainGetterCB,
			newTunerGainSetterCB,
			newTunerReferenceSourceGetterCB,
			newTunerReferenceSourceSetterCB,
			newTunerEnableGetterCB,
			newTunerEnableSetterCB),
	getTunerOutputSampleRateCB(),
	setTunerOutputSampleRateCB()
	{
		if ( newTunerOutputSampleRateGetterCB ) {
			getTunerOutputSampleRateCB = boost::shared_ptr< DoubleFromChar >( newTunerOutputSampleRateGetterCB, null_deleter());
		}
		if ( newTunerOutputSampleRateSetterCB ) {
			setTunerOutputSampleRateCB = boost::shared_ptr< VoidFromCharDouble >( newTunerOutputSampleRateSetterCB, null_deleter());
		}
	}

	InDigitalTunerPort::~InDigitalTunerPort()
	{
	}

	void InDigitalTunerPort::setTunerOutputSampleRate(const char* id, CORBA::Double sr)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setTunerOutputSampleRateCB ) (*setTunerOutputSampleRateCB)(id,sr);
		else throw FRONTEND::NotSupportedException("setTunerOutputSampleRate(const char* id, CORBA::Double sr) IS NOT CURRENTLY SUPPORTED");
	//
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	if(std::string(id) != parent->tunerChannels[tuner_id].control_allocation_id)
	//		throw FRONTEND::FrontendException(("ERROR:: ID: " + std::string(id) + " DOES NOT HAVE AUTHORIZATION TO MODIFY TUNER!").c_str());
	//
	//	frontend_tuner_allocation_struct newParams = parent->feAlloc_from_feStatus(tuner_id);
	//	newParams.allocation_id = std::string(id);
	//	newParams.sample_rate = sr;
	//	try {
	//		parent->setupTuner(tuner_id, newParams);
	//	} catch (std::exception& e) {
	//		throw FRONTEND::FrontendException(("WARNING: Exception Caught during setupTuner: " + std::string(e.what())).c_str());
	//	}
	}

	CORBA::Double InDigitalTunerPort::getTunerOutputSampleRate(const char* id)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getTunerOutputSampleRateCB ) return (*getTunerOutputSampleRateCB)(id);
		else throw FRONTEND::NotSupportedException("getTunerOutputSampleRate(const char* id) IS NOT CURRENTLY SUPPORTED");
	//	long tuner_id = parent->getTunerMapping(id);
	//	if (tuner_id < 0)
	//		throw FRONTEND::FrontendException(("ERROR: ID: " + std::string(id) + " IS NOT ASSOCIATED WITH ANY TUNER!").c_str());
	//	return parent->tunerChannels[tuner_id].frontend_status->sample_rate;
	}

	//getTunerOutputSampleRateCB
	void   InDigitalTunerPort::setTunerOutputSampleRateGetterCB( DoubleFromChar *newCB ) {
		getTunerOutputSampleRateCB =  boost::shared_ptr< DoubleFromChar >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerOutputSampleRateGetterCB( DoubleFromCharFn  newCB ) {
		getTunerOutputSampleRateCB =  boost::make_shared< StaticDoubleFromChar >( newCB );
	}

	//setTunerOutputSampleRateCB
	void   InDigitalTunerPort::setTunerOutputSampleRateSetterCB( VoidFromCharDouble *newCB ) {
		setTunerOutputSampleRateCB =  boost::shared_ptr< VoidFromCharDouble >( newCB, null_deleter());
	}
	void   InDigitalTunerPort::setTunerOutputSampleRateSetterCB( VoidFromCharDoubleFn  newCB ) {
		setTunerOutputSampleRateCB =  boost::make_shared< StaticVoidFromCharDouble >( newCB );
	}

	// ----------------------------------------------------------------------------------------
	// OutFrontendTunerPort definition
	// ----------------------------------------------------------------------------------------
	OutFrontendTunerPort::OutFrontendTunerPort(std::string port_name) :
		OutFrontendPort<FRONTEND::FrontendTuner_var,FRONTEND::FrontendTuner>::OutFrontendPort(port_name)
	{
	}

	OutFrontendTunerPort::OutFrontendTunerPort(std::string port_name,
                                                   LOGGER_PTR logger) :
		OutFrontendPort<FRONTEND::FrontendTuner_var,FRONTEND::FrontendTuner>::OutFrontendPort(port_name,
                                                                                                      logger)
	{
	}

	OutFrontendTunerPort::~OutFrontendTunerPort()
	{
	}

	void OutFrontendTunerPort::setLogger(LOGGER_PTR newLogger){
            logger = newLogger;
        }

	char* OutFrontendTunerPort::getTunerType(const char* id)
	{
	    char* retval;
	    std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerType(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_FrontendTuner_Out_i,"Call to getTunerType by FRONTEND_FrontendTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	CORBA::Boolean OutFrontendTunerPort::getTunerDeviceControl(const char* id)
	{
	    CORBA::Boolean retval;
	    std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerDeviceControl(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_FrontendTuner_Out_i,"Call to getTunerDeviceControl by FRONTEND_FrontendTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	char* OutFrontendTunerPort::getTunerGroupId(const char* id)
	{
	    char* retval;
	    std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerGroupId(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_FrontendTuner_Out_i,"Call to getTunerGroupId by FRONTEND_FrontendTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	char* OutFrontendTunerPort::getTunerRfFlowId(const char* id)
	{
	    char* retval;
	    std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerRfFlowId(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_FrontendTuner_Out_i,"Call to getTunerRfFlowId by FRONTEND_FrontendTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	CF::Properties* OutFrontendTunerPort::getTunerStatus(const char* id)
	{
	    CF::Properties* retval;
	    std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerStatus(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_FrontendTuner_Out_i,"Call to getTunerStatus by FRONTEND_FrontendTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	// ----------------------------------------------------------------------------------------
	// OutAnalogTunerPort definition
	// ----------------------------------------------------------------------------------------
	OutAnalogTunerPort::OutAnalogTunerPort(std::string port_name) :
		OutFrontendPort<FRONTEND::AnalogTuner_var,FRONTEND::AnalogTuner>::OutFrontendPort(port_name)
	{
	}

	OutAnalogTunerPort::OutAnalogTunerPort(std::string port_name,
                                               LOGGER_PTR logger) :
		OutFrontendPort<FRONTEND::AnalogTuner_var,FRONTEND::AnalogTuner>::OutFrontendPort(port_name,
                                                                                                  logger)
	{
	}

	OutAnalogTunerPort::~OutAnalogTunerPort()
	{
	}

	char* OutAnalogTunerPort::getTunerType(const char* id)
	{
	    char* retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerType(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerType by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	CORBA::Boolean OutAnalogTunerPort::getTunerDeviceControl(const char* id)
	{
	    CORBA::Boolean retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerDeviceControl(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerDeviceControl by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	char* OutAnalogTunerPort::getTunerGroupId(const char* id)
	{
	    char* retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerGroupId(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerGroupId by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	char* OutAnalogTunerPort::getTunerRfFlowId(const char* id)
	{
	    char* retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerRfFlowId(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerRfFlowId by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	CF::Properties* OutAnalogTunerPort::getTunerStatus(const char* id)
	{
	    CF::Properties* retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerStatus(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerStatus by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutAnalogTunerPort::setTunerCenterFrequency(const char* id, CORBA::Double freq)
	{
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerCenterFrequency(id, freq);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to setTunerCenterFrequency by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Double OutAnalogTunerPort::getTunerCenterFrequency(const char* id)
	{
	    CORBA::Double retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerCenterFrequency(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerCenterFrequency by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutAnalogTunerPort::setTunerBandwidth(const char* id, CORBA::Double bw)
	{
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerBandwidth(id, bw);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to setTunerBandwidth by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Double OutAnalogTunerPort::getTunerBandwidth(const char* id)
	{
	    CORBA::Double retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerBandwidth(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerBandwidth by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutAnalogTunerPort::setTunerAgcEnable(const char* id, CORBA::Boolean enable)
	{
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerAgcEnable(id, enable);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to setTunerAgcEnable by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Boolean OutAnalogTunerPort::getTunerAgcEnable(const char* id)
	{
	    CORBA::Boolean retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerAgcEnable(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerAgcEnable by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutAnalogTunerPort::setTunerGain(const char* id, CORBA::Float gain)
	{
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerGain(id, gain);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to setTunerGain by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Float OutAnalogTunerPort::getTunerGain(const char* id)
	{
	    CORBA::Float retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerGain(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerGain by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutAnalogTunerPort::setTunerReferenceSource(const char* id, CORBA::Long source)
	{
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerReferenceSource(id, source);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to setTunerReferenceSource by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Long OutAnalogTunerPort::getTunerReferenceSource(const char* id)
	{
	    CORBA::Long retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerReferenceSource(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerReferenceSource by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutAnalogTunerPort::setTunerEnable(const char* id, CORBA::Boolean enable)
	{
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerEnable(id, enable);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to setTunerEnable by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Boolean OutAnalogTunerPort::getTunerEnable(const char* id)
	{
	    CORBA::Boolean retval;
	    std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerEnable(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_AnalogTuner_Out_i,"Call to getTunerEnable by FRONTEND_AnalogTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	// ----------------------------------------------------------------------------------------
	// OutDigitalTunerPort definition
	// ----------------------------------------------------------------------------------------
	OutDigitalTunerPort::OutDigitalTunerPort(std::string port_name) :
		OutFrontendPort<FRONTEND::DigitalTuner_var,FRONTEND::DigitalTuner>::OutFrontendPort(port_name)
	{
	}

	OutDigitalTunerPort::OutDigitalTunerPort(std::string port_name,
                                                 LOGGER_PTR logger) :
		OutFrontendPort<FRONTEND::DigitalTuner_var,FRONTEND::DigitalTuner>::OutFrontendPort(port_name,
                                                                                                    logger)
	{
	}

	OutDigitalTunerPort::~OutDigitalTunerPort()
	{
	}

	char* OutDigitalTunerPort::getTunerType(const char* id)
	{
	    char* retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerType(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerType by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	CORBA::Boolean OutDigitalTunerPort::getTunerDeviceControl(const char* id)
	{
	    CORBA::Boolean retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerDeviceControl(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerDeviceControl by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	char* OutDigitalTunerPort::getTunerGroupId(const char* id)
	{
	    char* retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerGroupId(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerGroupId by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	char* OutDigitalTunerPort::getTunerRfFlowId(const char* id)
	{
	    char* retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerRfFlowId(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerRfFlowId by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	CF::Properties* OutDigitalTunerPort::getTunerStatus(const char* id)
	{
	    CF::Properties* retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerStatus(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerStatus by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutDigitalTunerPort::setTunerCenterFrequency(const char* id, CORBA::Double freq)
	{
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerCenterFrequency(id, freq);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to setTunerCenterFrequency by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Double OutDigitalTunerPort::getTunerCenterFrequency(const char* id)
	{
	    CORBA::Double retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerCenterFrequency(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerCenterFrequency by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutDigitalTunerPort::setTunerBandwidth(const char* id, CORBA::Double bw)
	{
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerBandwidth(id, bw);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to setTunerBandwidth by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Double OutDigitalTunerPort::getTunerBandwidth(const char* id)
	{
	    CORBA::Double retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerBandwidth(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerBandwidth by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutDigitalTunerPort::setTunerAgcEnable(const char* id, CORBA::Boolean enable)
	{
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerAgcEnable(id, enable);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to setTunerAgcEnable by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Boolean OutDigitalTunerPort::getTunerAgcEnable(const char* id)
	{
	    CORBA::Boolean retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerAgcEnable(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerAgcEnable by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutDigitalTunerPort::setTunerGain(const char* id, CORBA::Float gain)
	{
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerGain(id, gain);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to setTunerGain by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Float OutDigitalTunerPort::getTunerGain(const char* id)
	{
	    CORBA::Float retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerGain(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerGain by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutDigitalTunerPort::setTunerReferenceSource(const char* id, CORBA::Long source)
	{
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerReferenceSource(id, source);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to setTunerReferenceSource by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Long OutDigitalTunerPort::getTunerReferenceSource(const char* id)
	{
	    CORBA::Long retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerReferenceSource(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerReferenceSource by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutDigitalTunerPort::setTunerEnable(const char* id, CORBA::Boolean enable)
	{
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerEnable(id, enable);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to setTunerEnable by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Boolean OutDigitalTunerPort::getTunerEnable(const char* id)
	{
	    CORBA::Boolean retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerEnable(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerEnable by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

	void OutDigitalTunerPort::setTunerOutputSampleRate(const char* id, CORBA::Double sr)
	{
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->setTunerOutputSampleRate(id, sr);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to setTunerOutputSampleRate by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return;
	}

	CORBA::Double OutDigitalTunerPort::getTunerOutputSampleRate(const char* id)
	{
	    CORBA::Double retval;
	    std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->getTunerOutputSampleRate(id);
	            } catch(...) {
	                //LOG_ERROR(FRONTEND_DigitalTuner_Out_i,"Call to getTunerOutputSampleRate by FRONTEND_DigitalTuner_Out_i failed");
	            }
	        }
	    }

	    return retval;
	}

} // end of frontend namespace
