
#include "fe_tuner_port_impl.h"
#include "fe_log.h"

namespace frontend {
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
