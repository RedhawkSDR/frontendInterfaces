package frontend;

import org.apache.log4j.Logger;
import frontend.DigitalTunerListener;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public class InDigitalTunerPort extends FRONTEND.DigitalTunerPOA {

    protected String name;

    protected Logger logger = null;

    protected Object portAccess = null;

    protected DigitalTunerListener digitalTunerListener = null;

    public InDigitalTunerPort( String portName) {
        this( portName, null, null);
    }

    public InDigitalTunerPort( String portName,
                                DigitalTunerListener listener) {
        this( portName, listener, null);
    }

    public InDigitalTunerPort( String portName,
                                DigitalTunerListener listener,
                                Logger logger) {
        this.name = portName;
        this.digitalTunerListener = listener;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public String getTunerType(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerType(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerType(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerType(String id) callback listener not defined");
            }
        }
    }

    public boolean getTunerDeviceControl(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerDeviceControl(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerDeviceControl(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerDeviceControl(String id) callback listener not defined");
            }
        }
    }

    public String getTunerGroupId(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerGroupId(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGroupId(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerGroupId(String id) callback listener not defined");
            }
        }
    }

    public String getTunerRfFlowId(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerRfFlowId(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerRfFlowId(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerRfFlowId(String id) callback listener not defined");
            }
        }
    }

    public CF.DataType[] getTunerStatus(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerStatus(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerStatus(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerStatus(String id) callback listener not defined");
            }
        }
    }

    public void setTunerCenterFrequency(String id, double freq) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                digitalTunerListener.setTunerCenterFrequency(id, freq);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) callback listener not defined");
            }
        }
    }

    public double getTunerCenterFrequency(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerCenterFrequency(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerCenterFrequency(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerCenterFrequency(String id) callback listener not defined");
            }
        }
    }

    public void setTunerBandwidth(String id, double bw) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                digitalTunerListener.setTunerBandwidth(id, bw);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerBandwidth(String id, double bw) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort setTunerBandwidth(String id, double bw) callback listener not defined");
            }
        }
    }

    public double getTunerBandwidth(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerBandwidth(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerBandwidth(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerBandwidth(String id) callback listener not defined");
            }
        }
    }

    public void setTunerAgcEnable(String id, boolean enable) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                digitalTunerListener.setTunerAgcEnable(id, enable);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) callback listener not defined");
            }
        }
    }

    public boolean getTunerAgcEnable(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerAgcEnable(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerAgcEnable(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerAgcEnable(String id) callback listener not defined");
            }
        }
    }

    public void setTunerGain(String id, float gain) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                digitalTunerListener.setTunerGain(id, gain);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerGain(String id, float gain) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort setTunerGain(String id, float gain) callback listener not defined");
            }
        }
    }

    public float getTunerGain(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerGain(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGain(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerGain(String id) callback listener not defined");
            }
        }
    }

    public void setTunerReferenceSource(String id, int source) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                digitalTunerListener.setTunerReferenceSource(id, source);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerReferenceSource(String id, int source) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort setTunerReferenceSource(String id, int source) callback listener not defined");
            }
        }
    }

    public int getTunerReferenceSource(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerReferenceSource(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerReferenceSource(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerReferenceSource(String id) callback listener not defined");
            }
        }
    }

    public void setTunerEnable(String id, boolean enable) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                digitalTunerListener.setTunerEnable(id, enable);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerEnable(String id, boolean enable) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort setTunerEnable(String id, boolean enable) callback listener not defined");
            }
        }
    }

    public boolean getTunerEnable(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerEnable(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerEnable(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerEnable(String id) callback listener not defined");
            }
        }
    }

    public void setTunerOutputSampleRate(String id, double sr) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                digitalTunerListener.setTunerOutputSampleRate(id, sr);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) callback listener not defined");
            }
        }
    }

    public double getTunerOutputSampleRate(String id) throws FRONTEND.FrontendException, FRONTEND.BadParameterException, FRONTEND.NotSupportedException {
        synchronized(this.portAccess){
            if ( digitalTunerListener != null ){
                return digitalTunerListener.getTunerOutputSampleRate(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerOutputSampleRate(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerOutputSampleRate(String id) callback listener not defined");
            }
        }
    }

    public void setDigitalTunerListener( DigitalTunerListener newListener ) {
        digitalTunerListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
