package frontend;

import org.apache.log4j.Logger;
import frontend.AnalogTunerListener;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public class InAnalogTunerPort extends FRONTEND.AnalogTunerPOA {

    protected String name;

    protected Logger logger = null;

    protected Object portAccess = null;

    protected AnalogTunerListener analogTunerListener = null;

    public InAnalogTunerPort(String portName){
        this( portName, null, null);
    }

    public InAnalogTunerPort(String portName,
                             AnalogTunerListener listener){
        this( portName, listener, null);
    }

    public InAnalogTunerPort(String portName,
                             AnalogTunerListener listener,
                             Logger logger){
        this.name = portName;
        this.analogTunerListener = listener;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public String getTunerType(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerType(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerType(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerType(String id) callback listener not defined");
            }
        }
    }

    public boolean getTunerDeviceControl(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerDeviceControl(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerDeviceControl(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerDeviceControl(String id) callback listener not defined");
            }
        }
    }

    public String getTunerGroupId(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerGroupId(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGroupId(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerGroupId(String id) callback listener not defined");
            }
        }
    }

    public String getTunerRfFlowId(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerRfFlowId(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerRfFlowId(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerRfFlowId(String id) callback listener not defined");
            }
        }
    }

    public CF.DataType[] getTunerStatus(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerStatus(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerStatus(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerStatus(String id) callback listener not defined");
            }
        }
    }

    public void setTunerCenterFrequency(String id, double freq) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                analogTunerListener.setTunerCenterFrequency(id, freq);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) callback listener not defined");
            }
        }
    }

    public double getTunerCenterFrequency(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerCenterFrequency(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerCenterFrequency(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerCenterFrequency(String id) callback listener not defined");
            }
        }
    }

    public void setTunerBandwidth(String id, double bw) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                analogTunerListener.setTunerBandwidth(id, bw);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerBandwidth(String id, double bw) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort setTunerBandwidth(String id, double bw) callback listener not defined");
            }
        }
    }

    public double getTunerBandwidth(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerBandwidth(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerBandwidth(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerBandwidth(String id) callback listener not defined");
            }
        }
    }

    public void setTunerAgcEnable(String id, boolean enable) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                analogTunerListener.setTunerAgcEnable(id, enable);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) callback listener not defined");
            }
        }
    }

    public boolean getTunerAgcEnable(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerAgcEnable(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerAgcEnable(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerAgcEnable(String id) callback listener not defined");
            }
        }
    }

    public void setTunerGain(String id, float gain) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                analogTunerListener.setTunerGain(id, gain);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerGain(String id, float gain) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort setTunerGain(String id, float gain) callback listener not defined");
            }
        }
    }

    public float getTunerGain(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerGain(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGain(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerGain(String id) callback listener not defined");
            }
        }
    }

    public void setTunerReferenceSource(String id, int source) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                analogTunerListener.setTunerReferenceSource(id, source);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerReferenceSource(String id, int source) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort setTunerReferenceSource(String id, int source) callback listener not defined");
            }
        }
    }

    public int getTunerReferenceSource(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerReferenceSource(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerReferenceSource(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerReferenceSource(String id) callback listener not defined");
            }
        }
    }

    public void setTunerEnable(String id, boolean enable) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                analogTunerListener.setTunerEnable(id, enable);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerEnable(String id, boolean enable) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort setTunerEnable(String id, boolean enable) callback listener not defined");
            }
        }
    }

    public boolean getTunerEnable(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( analogTunerListener != null ){
                return analogTunerListener.getTunerEnable(id);
            } else {
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerEnable(String id) callback listener not defined");
                }
                throw new FrontendException("InAnalogTunerPort getTunerEnable(String id) callback listener not defined");
            }
        }
    }

    public void setAnalogTunerListener( AnalogTunerListener newListener ) {
        analogTunerListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
