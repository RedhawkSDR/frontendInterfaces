
#include "fe_rfinfo_port_impl.h"
#include "fe_log.h"

namespace frontend {
    
    FRONTEND::RFInfoPkt* returnRFInfoPkt(const RFInfoPkt &val) {
        FRONTEND::RFInfoPkt* tmpVal = new FRONTEND::RFInfoPkt();
        tmpVal->rf_flow_id = CORBA::string_dup(val.rf_flow_id.c_str());
        tmpVal->rf_center_freq = val.rf_center_freq;
        tmpVal->rf_bandwidth = val.rf_bandwidth;
        tmpVal->if_center_freq = val.if_center_freq;
        tmpVal->spectrum_inverted = val.spectrum_inverted;
        tmpVal->sensor.collector = CORBA::string_dup(val.sensor.collector.c_str());
        tmpVal->sensor.mission = CORBA::string_dup(val.sensor.mission.c_str());
        tmpVal->sensor.rx = CORBA::string_dup(val.sensor.rx.c_str());
        tmpVal->sensor.antenna.description = CORBA::string_dup(val.sensor.antenna.description.c_str());
        tmpVal->sensor.antenna.name = CORBA::string_dup(val.sensor.antenna.name.c_str());
        tmpVal->sensor.antenna.size = CORBA::string_dup(val.sensor.antenna.size.c_str());
        tmpVal->sensor.antenna.type = CORBA::string_dup(val.sensor.antenna.type.c_str());
        tmpVal->sensor.feed.name = CORBA::string_dup(val.sensor.feed.name.c_str());
        tmpVal->sensor.feed.polarization = CORBA::string_dup(val.sensor.feed.polarization.c_str());
        tmpVal->sensor.feed.freq_range.max_val = val.sensor.feed.freq_range.max_val;
        tmpVal->sensor.feed.freq_range.min_val = val.sensor.feed.freq_range.min_val;
        tmpVal->sensor.feed.freq_range.values.length(val.sensor.feed.freq_range.values.size());
        for (unsigned int i=0; i<val.sensor.feed.freq_range.values.size(); i++) {
            tmpVal->sensor.feed.freq_range.values[i] = val.sensor.feed.freq_range.values[i];
        }
        return tmpVal;
    };
    RFInfoPkt returnRFInfoPkt(const FRONTEND::RFInfoPkt &tmpVal) {
        RFInfoPkt val;
        val.rf_flow_id = ossie::corba::returnString(tmpVal.rf_flow_id);
        val.rf_center_freq = tmpVal.rf_center_freq;
        val.rf_bandwidth = tmpVal.rf_bandwidth;
        val.if_center_freq = tmpVal.if_center_freq;
        val.spectrum_inverted = tmpVal.spectrum_inverted;
        val.sensor.collector = ossie::corba::returnString(tmpVal.sensor.collector);
        val.sensor.mission = ossie::corba::returnString(tmpVal.sensor.mission);
        val.sensor.rx = ossie::corba::returnString(tmpVal.sensor.rx);
        val.sensor.antenna.description = ossie::corba::returnString(tmpVal.sensor.antenna.description);
        val.sensor.antenna.name = ossie::corba::returnString(tmpVal.sensor.antenna.name);
        val.sensor.antenna.size = ossie::corba::returnString(tmpVal.sensor.antenna.size);
        val.sensor.antenna.type = ossie::corba::returnString(tmpVal.sensor.antenna.type);
        val.sensor.feed.name = ossie::corba::returnString(tmpVal.sensor.feed.name);
        val.sensor.feed.polarization = ossie::corba::returnString(tmpVal.sensor.feed.polarization);
        val.sensor.feed.freq_range.max_val = tmpVal.sensor.feed.freq_range.max_val;
        val.sensor.feed.freq_range.min_val = tmpVal.sensor.feed.freq_range.min_val;
        val.sensor.feed.freq_range.values.resize(tmpVal.sensor.feed.freq_range.values.length());
        for (unsigned int i=0; i<val.sensor.feed.freq_range.values.size(); i++) {
            val.sensor.feed.freq_range.values[i] = tmpVal.sensor.feed.freq_range.values[i];
        }
        return val;
    };
    
	// ----------------------------------------------------------------------------------------
	// InRFInfoPort definition
	// ----------------------------------------------------------------------------------------
	/*InRFInfoPort::InRFInfoPort(std::string port_name,
    		CharFromVoid *newRFFlowIdGetterCB,
    		RFInfoPktFromVoid *newRFInfoPktGetterCB,
    		VoidFromChar *newRFFlowIdSetterCB,
    		VoidFromRFInfoPkt *newRFInfoPktSetterCB):
	Port_Provides_base_impl(port_name),
	getRFFlowIdCB(),
	getRFInfoPktCB(),
	setRFFlowIdCB(),
	setRFInfoPktCB()
	{
		if ( newRFFlowIdGetterCB ) {
			getRFFlowIdCB = boost::shared_ptr< CharFromVoid >( newRFFlowIdGetterCB, null_deleter());
		}
		if ( newRFInfoPktGetterCB ) {
			getRFInfoPktCB = boost::shared_ptr< RFInfoPktFromVoid >( newRFInfoPktGetterCB, null_deleter());
		}
		if ( newRFFlowIdSetterCB ) {
			setRFFlowIdCB = boost::shared_ptr< VoidFromChar >( newRFFlowIdSetterCB, null_deleter());
		}
		if ( newRFInfoPktSetterCB ) {
			setRFInfoPktCB = boost::shared_ptr< VoidFromRFInfoPkt >( newRFInfoPktSetterCB, null_deleter());
		}
	}

	InRFInfoPort::InRFInfoPort(std::string port_name,
                LOGGER_PTR logger,
    		CharFromVoid *newRFFlowIdGetterCB,
    		RFInfoPktFromVoid *newRFInfoPktGetterCB,
    		VoidFromChar *newRFFlowIdSetterCB,
    		VoidFromRFInfoPkt *newRFInfoPktSetterCB):
	Port_Provides_base_impl(port_name),
        logger(logger),
	getRFFlowIdCB(),
	getRFInfoPktCB(),
	setRFFlowIdCB(),
	setRFInfoPktCB()
	{
		if ( newRFFlowIdGetterCB ) {
			getRFFlowIdCB = boost::shared_ptr< CharFromVoid >( newRFFlowIdGetterCB, null_deleter());
		}
		if ( newRFInfoPktGetterCB ) {
			getRFInfoPktCB = boost::shared_ptr< RFInfoPktFromVoid >( newRFInfoPktGetterCB, null_deleter());
		}
		if ( newRFFlowIdSetterCB ) {
			setRFFlowIdCB = boost::shared_ptr< VoidFromChar >( newRFFlowIdSetterCB, null_deleter());
		}
		if ( newRFInfoPktSetterCB ) {
			setRFInfoPktCB = boost::shared_ptr< VoidFromRFInfoPkt >( newRFInfoPktSetterCB, null_deleter());
		}
	}

	InRFInfoPort::~InRFInfoPort()
	{
	}

	void InRFInfoPort::setLogger(LOGGER_PTR newLogger)
	{
            logger = newLogger;
        }

	char* InRFInfoPort::rf_flow_id()
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getRFFlowIdCB ) return (*getRFFlowIdCB)();
		else throw FRONTEND::NotSupportedException("rf_flow_id() IS NOT CURRENTLY SUPPORTED");
		//return CORBA::string_dup(parent->rf_flow_id.c_str());
	}

	void InRFInfoPort::rf_flow_id(const char* data)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setRFFlowIdCB ) (*setRFFlowIdCB)(data);
		else throw FRONTEND::NotSupportedException("rf_flow_id(const char* data) IS NOT CURRENTLY SUPPORTED");
		//parent->update_rf_flow_id(std::string(data));
	}

	FRONTEND::RFInfoPkt* InRFInfoPort::rfinfo_pkt()
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getRFInfoPktCB ) return (*getRFInfoPktCB)();
		else throw FRONTEND::NotSupportedException("rfinfo_pkt() IS NOT CURRENTLY SUPPORTED");
		//return parent->rfinfo_pkt;
	}

	void InRFInfoPort::rfinfo_pkt(const FRONTEND::RFInfoPkt& data)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setRFInfoPktCB ) (*setRFInfoPktCB)(data);
		else throw FRONTEND::NotSupportedException("rfinfo_pkt(const ::FRONTEND::RFInfoPkt& data) IS NOT CURRENTLY SUPPORTED");
		//parent->update_rf_flow_id(std::string(data.rf_flow_id));
	}

	//getRFFlowIdCB
	void   InRFInfoPort::setRFFlowIdGetterCB( CharFromVoid *newCB ) {
		getRFFlowIdCB =  boost::shared_ptr< CharFromVoid >(newCB, null_deleter());
	}
	void   InRFInfoPort::setRFFlowIdGetterCB( CharFromVoidFn  newCB ) {
		getRFFlowIdCB =  boost::make_shared< StaticCharFromVoid >( newCB );
	}

	//setRFFlowIdCB
	void   InRFInfoPort::setRFFlowIdSetterCB( VoidFromChar *newCB ) {
		setRFFlowIdCB =  boost::shared_ptr< VoidFromChar >(newCB, null_deleter());
	}
	void   InRFInfoPort::setRFFlowIdSetterCB( VoidFromCharFn  newCB ) {
		setRFFlowIdCB =  boost::make_shared< StaticVoidFromChar >( newCB );
	}

	//getRFInfoPktCB
	void   InRFInfoPort::setRFInfoPktGetterCB( RFInfoPktFromVoid *newCB ) {
		getRFInfoPktCB =  boost::shared_ptr< RFInfoPktFromVoid >(newCB, null_deleter());
	}
	void   InRFInfoPort::setRFInfoPktGetterCB( RFInfoPktFromVoidFn  newCB ) {
		getRFInfoPktCB =  boost::make_shared< StaticRFInfoPktFromVoid >( newCB );
	}

	//setRFInfoPktCB
	void   InRFInfoPort::setRFInfoPktSetterCB( VoidFromRFInfoPkt *newCB ) {
		setRFInfoPktCB =  boost::shared_ptr< VoidFromRFInfoPkt >(newCB, null_deleter());
	}
	void   InRFInfoPort::setRFInfoPktSetterCB( VoidFromRFInfoPktFn  newCB ) {
		setRFInfoPktCB =  boost::make_shared< StaticVoidFromRFInfoPkt >( newCB );
	}*/

	// ----------------------------------------------------------------------------------------
	// OutRFInfoPort definition
	// ----------------------------------------------------------------------------------------
	OutRFInfoPort::OutRFInfoPort(std::string port_name) :
		OutFrontendPort<FRONTEND::RFInfo_var,FRONTEND::RFInfo>::OutFrontendPort(port_name){
	}

	OutRFInfoPort::OutRFInfoPort(std::string port_name,
                                     LOGGER_PTR logger) :
		OutFrontendPort<FRONTEND::RFInfo_var,FRONTEND::RFInfo>::OutFrontendPort(port_name,
                                                                                        logger){
	}

	OutRFInfoPort::~OutRFInfoPort(){
	}

	void OutRFInfoPort::setLogger(LOGGER_PTR newLogger)
	{
            logger = newLogger;
        }

	char* OutRFInfoPort::rf_flow_id(){
	    char* retval;
	    std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->rf_flow_id();
	            } catch(...) {
	                //LOG_ERROR(OutRFInfoPort,"Call to rf_flow_id by OutRFInfoPort failed");
	            }
	        }
	    }

	    return retval;
	}
	void OutRFInfoPort::rf_flow_id(char* data){
	    std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->rf_flow_id(data);
	            } catch(...) {
	                //LOG_ERROR(OutRFInfoPort,"Call to rf_flow_id by OutRFInfoPort failed");
	            }
	        }
	    }
	}
	FRONTEND::RFInfoPkt* OutRFInfoPort::rfinfo_pkt(){
	    FRONTEND::RFInfoPkt* retval;
	    std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                retval = ((*i).first)->rfinfo_pkt();
	            } catch(...) {
	                //LOG_ERROR(OutRFInfoPort,"Call to rfinfo_pkt by OutRFInfoPort failed");
	            }
	        }
	    }

	    return retval;
	}
	void OutRFInfoPort::rfinfo_pkt(FRONTEND::RFInfoPkt data){
	    std::vector < std::pair < FRONTEND::RFInfo_var, std::string > >::iterator i;

	    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

	    if (active) {
	        for (i = outConnections.begin(); i != outConnections.end(); ++i) {
	            try {
	                ((*i).first)->rfinfo_pkt(data);
	            } catch(...) {
	                //LOG_ERROR(OutRFInfoPort,"Call to rfinfo_pkt by OutRFInfoPort failed");
	            }
	        }
	    }
	}

} // end of frontend namespace


