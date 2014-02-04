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
    
	// ----------------------------------------------------------------------------------------
	// OutFrontendTunerPort declaration
	// ----------------------------------------------------------------------------------------
	class OutFrontendTunerPort : public OutFrontendPort<FRONTEND::FrontendTuner_var,FRONTEND::FrontendTuner>
	{
	    public:
			OutFrontendTunerPort(std::string port_name);
			OutFrontendTunerPort(std::string port_name,
                                             LOGGER_PTR logger);
	        ~OutFrontendTunerPort();

	        char* getTunerType(const char* id);
	        CORBA::Boolean getTunerDeviceControl(const char* id);
	        char* getTunerGroupId(const char* id);
	        char* getTunerRfFlowId(const char* id);
	        CF::Properties* getTunerStatus(const char* id);
                void setLogger(LOGGER_PTR newLogger);

            protected:
                LOGGER_PTR logger;
	};

	// ----------------------------------------------------------------------------------------
	// OutAnalogTunerPort declaration
	// ----------------------------------------------------------------------------------------
	class OutAnalogTunerPort : public OutFrontendPort<FRONTEND::AnalogTuner_var,FRONTEND::AnalogTuner>
	{
	    public:
                OutAnalogTunerPort(std::string port_name);
                OutAnalogTunerPort(std::string port_name,
                                   LOGGER_PTR logger);
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
			OutDigitalTunerPort(std::string port_name,
                                            LOGGER_PTR logger);
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
