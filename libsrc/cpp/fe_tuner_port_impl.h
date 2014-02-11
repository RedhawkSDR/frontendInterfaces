#ifndef FE_TUNER_PORT_H
#define FE_TUNER_PORT_H

#include "fe_port_impl.h"
#include "fe_base.h"

#include <FRONTEND/TunerControl.h>


namespace frontend {
    
    class tuner_delegation {
        public:
            virtual std::string getTunerType(std::string& id) = 0;
            virtual bool getTunerDeviceControl(std::string& id) = 0;
            virtual std::string getTunerGroupId(std::string& id) = 0;
            virtual std::string getTunerRfFlowId(std::string& id) = 0;
            virtual CF::Properties* getTunerStatus(std::string& id) = 0;
    };
    class analog_tuner_delegation : public virtual tuner_delegation {
        public:
            virtual void setTunerCenterFrequency(std::string& id, double freq) = 0;
            virtual double getTunerCenterFrequency(std::string& id) = 0;
            virtual void setTunerBandwidth(std::string& id, double bw) = 0;
            virtual double getTunerBandwidth(std::string& id) = 0;
            virtual void setTunerAgcEnable(std::string& id, bool enable) = 0;
            virtual bool getTunerAgcEnable(std::string& id) = 0;
            virtual void setTunerGain(std::string& id, float gain) = 0;
            virtual float getTunerGain(std::string& id) = 0;
            virtual void setTunerReferenceSource(std::string& id, long source) = 0;
            virtual long getTunerReferenceSource(std::string& id) = 0;
            virtual void setTunerEnable(std::string& id, bool enable) = 0;
            virtual bool getTunerEnable(std::string& id) = 0;
    };
    class digital_tuner_delegation : public virtual analog_tuner_delegation {
        public:
            virtual void setTunerOutputSampleRate(std::string& id, double sr) = 0;
            virtual double getTunerOutputSampleRate(std::string& id) = 0;
    };
    
    class InFrontendTunerPort : public virtual POA_FRONTEND::FrontendTuner, public Port_Provides_base_impl
    {
        public:
            InFrontendTunerPort(std::string port_name, tuner_delegation *_parent): 
            Port_Provides_base_impl(port_name)
            {
                parent = _parent;
            };
            ~InFrontendTunerPort() {};
            char* getTunerType(const char* id) {
                boost::mutex::scoped_lock lock(portAccess);
                std::string _id(id);
                return (CORBA::string_dup(this->parent->getTunerType(_id).c_str()));
            };
            CORBA::Boolean getTunerDeviceControl(const char* id) {
                boost::mutex::scoped_lock lock(portAccess);
                std::string _id(id);
                return (this->parent->getTunerDeviceControl(_id));
            };
            char* getTunerGroupId(const char* id) {
                boost::mutex::scoped_lock lock(portAccess);
                std::string _id(id);
                return (CORBA::string_dup(this->parent->getTunerGroupId(_id).c_str()));
            };
            char* getTunerRfFlowId(const char* id) {
                boost::mutex::scoped_lock lock(portAccess);
                std::string _id(id);
                return (CORBA::string_dup(this->parent->getTunerRfFlowId(_id).c_str()));
            };
            CF::Properties* getTunerStatus(const char* id) {
                boost::mutex::scoped_lock lock(portAccess);
                std::string _id(id);
                return (this->parent->getTunerStatus(_id));
            };
        protected:
            boost::mutex portAccess;
        private:
            tuner_delegation *parent;
    };
    
    class InAnalogTunerPort : public virtual POA_FRONTEND::AnalogTuner, public InFrontendTunerPort
    {
        public:
            typedef InFrontendTunerPort super;
            InAnalogTunerPort(std::string port_name, analog_tuner_delegation *_parent):super(port_name, _parent)
            {
                parent = _parent;
            };
            ~InAnalogTunerPort() {};
            void setTunerCenterFrequency(const char* id, CORBA::Double freq) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                this->parent->setTunerCenterFrequency(_id, freq);
            };
            CORBA::Double getTunerCenterFrequency(const char* id) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                return (this->parent->getTunerCenterFrequency(_id));
            };
            void setTunerBandwidth(const char* id, CORBA::Double bw) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                this->parent->setTunerBandwidth(_id, bw);
            };
            CORBA::Double getTunerBandwidth(const char* id) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                return (this->parent->getTunerBandwidth(_id));
            };
            void setTunerAgcEnable(const char* id, CORBA::Boolean enable) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                this->parent->setTunerAgcEnable(_id, enable);
            };
            CORBA::Boolean getTunerAgcEnable(const char* id) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                return (this->parent->getTunerAgcEnable(_id));
            };
            void setTunerGain(const char* id, CORBA::Float gain) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                this->parent->setTunerGain(_id, gain);
            };
            CORBA::Float getTunerGain(const char* id) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                return (this->parent->getTunerGain(_id));
            };
            void setTunerReferenceSource(const char* id, CORBA::Long source) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                this->parent->setTunerReferenceSource(_id, source);
            };
            CORBA::Long getTunerReferenceSource(const char* id) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                return (this->parent->getTunerReferenceSource(_id));
            };
            void setTunerEnable(const char* id, CORBA::Boolean enable) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                this->parent->setTunerEnable(_id, enable);
            };
            CORBA::Boolean getTunerEnable(const char* id) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                return (this->parent->getTunerEnable(_id));
            };
        private:
            analog_tuner_delegation *parent;
    };
    
    class InDigitalTunerPort : public virtual POA_FRONTEND::DigitalTuner, public InAnalogTunerPort
    {
        public:
            typedef InAnalogTunerPort super;
            InDigitalTunerPort(std::string port_name, digital_tuner_delegation *_parent):super(port_name, _parent)
            {
                parent = _parent;
            };
            ~InDigitalTunerPort() {};
            void setTunerOutputSampleRate(const char* id, CORBA::Double sr) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                this->parent->setTunerOutputSampleRate(_id, sr);
            };
            CORBA::Double getTunerOutputSampleRate(const char* id) {
                boost::mutex::scoped_lock lock(this->portAccess);
                std::string _id(id);
                return (this->parent->getTunerOutputSampleRate(_id));
            };
        private:
            digital_tuner_delegation *parent;
    };
    
    
    template<typename PortType_var, typename PortType>
    class OutFrontendTunerPortT : public OutFrontendPort<PortType_var, PortType>
    {
        public:
            OutFrontendTunerPortT(std::string port_name) : OutFrontendPort<PortType_var, PortType>(port_name)
            {};
            OutFrontendTunerPortT(std::string port_name, LOGGER_PTR logger) : OutFrontendPort<PortType_var, PortType>(port_name, logger)
            {};
            ~OutFrontendTunerPortT(){};
            
            std::string getTunerType(std::string &id) {
                CORBA::String_var retval;
                std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerType(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutFrontendTunerPortT,"Call to getTunerType by OutFrontendTunerPort failed");
                        }
                    }
                }
                std::string str_retval = ossie::corba::returnString(retval);
                return str_retval;
            };
            bool getTunerDeviceControl(std::string &id) {
                CORBA::Boolean retval;
                std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerDeviceControl(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutFrontendTunerPortT,"Call to getTunerDeviceControl by OutFrontendTunerPort failed");
                        }
                    }
                }
                return retval;
            };
            std::string getTunerGroupId(std::string &id) {
                CORBA::String_var retval;
                std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerGroupId(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutFrontendTunerPortT,"Call to getTunerGroupId by OutFrontendTunerPort failed");
                        }
                    }
                }
                std::string str_retval = ossie::corba::returnString(retval);
                return str_retval;
            };
            std::string getTunerRfFlowId(std::string &id) {
                CORBA::String_var retval;
                std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerRfFlowId(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutFrontendTunerPortT,"Call to getTunerRfFlowId by OutFrontendTunerPort failed");
                        }
                    }
                }
                std::string str_retval = ossie::corba::returnString(retval);
                return str_retval;
            };
            CF::Properties* getTunerStatus(std::string &id) {
                CF::Properties* retval;
                std::vector < std::pair < FRONTEND::FrontendTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerStatus(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutFrontendTunerPortT,"Call to getTunerStatus by OutFrontendTunerPort failed");
                        }
                    }
                }
                return retval;
            };
            void setLogger(LOGGER_PTR newLogger) {
                logger = newLogger;
            };
            
        protected:
            LOGGER_PTR logger;
    };
 
    template<typename PortType_var, typename PortType>
    class OutAnalogTunerPortT : public OutFrontendTunerPortT<PortType_var, PortType>
    {
        public:
            OutAnalogTunerPortT(std::string port_name) : OutFrontendTunerPortT<PortType_var, PortType>(port_name)
            {};
            OutAnalogTunerPortT(std::string port_name, LOGGER_PTR logger) : OutFrontendTunerPortT<PortType_var, PortType>(port_name, logger)
            {};
            ~OutAnalogTunerPortT(){};
            
            void setTunerCenterFrequency(std::string &id, double freq) {
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            ((*i).first)->setTunerCenterFrequency(id.c_str(), freq);
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to setTunerCenterFrequency by OutAnalogTunerPort failed");
                        }
                    }
                }
                return;
            };
            double getTunerCenterFrequency(std::string &id) {
                CORBA::Double retval;
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerCenterFrequency(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to getTunerCenterFrequency by OutAnalogTunerPort failed");
                        }
                    }
                }
                return retval;
            };
            void setTunerBandwidth(std::string &id, double bw) {
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            ((*i).first)->setTunerBandwidth(id.c_str(), bw);
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to setTunerBandwidth by OutAnalogTunerPort failed");
                        }
                    }
                }
                return;
            };
            double getTunerBandwidth(std::string &id) {
                CORBA::Double retval;
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerBandwidth(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to getTunerBandwidth by OutAnalogTunerPort failed");
                        }
                    }
                }
                return retval;
            };
            void setTunerAgcEnable(std::string &id, bool enable) {
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            ((*i).first)->setTunerAgcEnable(id.c_str(), enable);
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to setTunerAgcEnable by OutAnalogTunerPort failed");
                        }
                    }
                }
                return;
            };
            bool getTunerAgcEnable(std::string &id) {
                CORBA::Boolean retval;
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerAgcEnable(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to getTunerAgcEnable by OutAnalogTunerPort failed");
                        }
                    }
                }
                return retval;
            };
            void setTunerGain(std::string &id, float gain) {
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            ((*i).first)->setTunerGain(id.c_str(), gain);
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to setTunerGain by OutAnalogTunerPort failed");
                        }
                    }
                }
                return;
            };
            float getTunerGain(std::string &id) {
                CORBA::Float retval;
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerGain(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to getTunerGain by OutAnalogTunerPort failed");
                        }
                    }
                }
                return retval;
            };
            void setTunerReferenceSource(std::string &id, int source) {
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            ((*i).first)->setTunerReferenceSource(id.c_str(), source);
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to setTunerReferenceSource by OutAnalogTunerPort failed");
                        }
                    }
                }
                return;
            };
            int getTunerReferenceSource(std::string &id) {
                CORBA::Long retval;
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerReferenceSource(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to getTunerReferenceSource by OutAnalogTunerPort failed");
                        }
                    }
                }
                return retval;
            };
            void setTunerEnable(std::string &id, bool enable) {
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            ((*i).first)->setTunerEnable(id.c_str(), enable);
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to setTunerEnable by OutAnalogTunerPort failed");
                        }
                    }
                }
                return;
            };
            bool getTunerEnable(std::string &id) {
                CORBA::Boolean retval;
                std::vector < std::pair < FRONTEND::AnalogTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerEnable(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutAnalogTunerPortT,"Call to getTunerEnable by OutAnalogTunerPort failed");
                        }
                    }
                }
                return retval;
            };
    };
    
    template<typename PortType_var, typename PortType>
    class OutDigitalTunerPortT : public OutAnalogTunerPortT<PortType_var, PortType>
    {
        public:
            OutDigitalTunerPortT(std::string port_name) : OutAnalogTunerPortT<PortType_var, PortType>(port_name)
            {};
            OutDigitalTunerPortT(std::string port_name, LOGGER_PTR logger) : OutAnalogTunerPortT<PortType_var, PortType>(port_name, logger)
            {};
            ~OutDigitalTunerPortT(){};
            
            void setTunerOutputSampleRate(std::string &id, double sr) {
                std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            ((*i).first)->setTunerOutputSampleRate(id.c_str(), sr);
                        } catch(...) {
                            LOG_ERROR(OutDigitalTunerPortT,"Call to setTunerOutputSampleRate by OutDigitalTunerPort failed");
                        }
                    }
                }
                return;
            };
            double getTunerOutputSampleRate(std::string &id) {
                CORBA::Double retval;
                std::vector < std::pair < FRONTEND::DigitalTuner_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            retval = ((*i).first)->getTunerOutputSampleRate(id.c_str());
                        } catch(...) {
                            LOG_ERROR(OutDigitalTunerPortT,"Call to getTunerOutputSampleRate by OutDigitalTunerPort failed");
                        }
                    }
                }
                return retval;
            };
    };
    
    // ----------------------------------------------------------------------------------------
    // OutFrontendTunerPort declaration
    // ----------------------------------------------------------------------------------------
    class OutFrontendTunerPort : public OutFrontendTunerPortT<FRONTEND::FrontendTuner_var,FRONTEND::FrontendTuner> {
        public:
            OutFrontendTunerPort(std::string port_name) : OutFrontendTunerPortT<FRONTEND::FrontendTuner_var,FRONTEND::FrontendTuner>(port_name)
            {};
            OutFrontendTunerPort(std::string port_name, LOGGER_PTR logger) : OutFrontendTunerPortT<FRONTEND::FrontendTuner_var,FRONTEND::FrontendTuner>(port_name, logger)
            {};
    };

    // ----------------------------------------------------------------------------------------
    // OutAnalogTunerPort declaration
    // ----------------------------------------------------------------------------------------
    class OutAnalogTunerPort : public OutAnalogTunerPortT<FRONTEND::AnalogTuner_var,FRONTEND::AnalogTuner> {
        public:
            OutAnalogTunerPort(std::string port_name) : OutAnalogTunerPortT<FRONTEND::AnalogTuner_var,FRONTEND::AnalogTuner>(port_name)
            {};
            OutAnalogTunerPort(std::string port_name, LOGGER_PTR logger) : OutAnalogTunerPortT<FRONTEND::AnalogTuner_var,FRONTEND::AnalogTuner>(port_name, logger)
            {};
    };

    // ----------------------------------------------------------------------------------------
    // OutDigitalTunerPort declaration
    // ----------------------------------------------------------------------------------------
    class OutDigitalTunerPort : public OutDigitalTunerPortT<FRONTEND::DigitalTuner_var,FRONTEND::DigitalTuner> {
        public:
            OutDigitalTunerPort(std::string port_name) : OutDigitalTunerPortT<FRONTEND::DigitalTuner_var,FRONTEND::DigitalTuner>(port_name)
            {};
            OutDigitalTunerPort(std::string port_name, LOGGER_PTR logger) : OutDigitalTunerPortT<FRONTEND::DigitalTuner_var,FRONTEND::DigitalTuner>(port_name, logger)
            {};
    };

} // end of frontend namespace


#endif
