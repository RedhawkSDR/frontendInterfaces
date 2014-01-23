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

    public String getTunerType(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerType(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerType(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerType(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerType(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerType(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public boolean getTunerDeviceControl(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerDeviceControl(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerDeviceControl(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerDeviceControl(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerDeviceControl(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerDeviceControl(String id) exception " + e.getMessage());
            }
            return false;
        }
    }

    public String getTunerGroupId(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerGroupId(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerGroupId(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerGroupId(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGroupId(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerGroupId(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public String getTunerRfFlowId(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerRfFlowId(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerRfFlowId(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerRfFlowId(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerRfFlowId(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerRfFlowId(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public CF.DataType[] getTunerStatus(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerStatus(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerStatus(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerStatus(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerStatus(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerStatus(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public void setTunerCenterFrequency(String id, double freq)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    digitalTunerListener.fe_setTunerCenterFrequency(id, freq);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) exception " + e.getMessage());
            }
        }
    }

    public double getTunerCenterFrequency(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerCenterFrequency(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerCenterFrequency(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerCenterFrequency(String id) callback listener not defined");
                }
            }catch(Exception e){ 
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerCenterFrequency(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerCenterFrequency(String id) exception " + e.getMessage());
            }
            return -1.0;
        }
    }

    public void setTunerBandwidth(String id, double bw)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    digitalTunerListener.fe_setTunerBandwidth(id, bw);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerBandwidth(String id, double bw) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerBandwidth(String id, double bw) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerBandwidth(String id, double bw) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort setTunerBandwidth(String id, double bw) exception " + e.getMessage());
            }
        }
    }

    public double getTunerBandwidth(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerBandwidth(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerBandwidth(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerBandwidth(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerBandwidth(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerBandwidth(String id) exception " + e.getMessage());
            }
            return -1.0;
        }
    }

    public void setTunerAgcEnable(String id, boolean enable)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    digitalTunerListener.fe_setTunerAgcEnable(id, enable);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) exception " + e.getMessage());
            }
        }
    }

    public boolean getTunerAgcEnable(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerAgcEnable(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerAgcEnable(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerAgcEnable(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerAgcEnable(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerAgcEnable(String id) exception " + e.getMessage());
            }
            return false;
        }
    }

    public void setTunerGain(String id, float gain)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    digitalTunerListener.fe_setTunerGain(id, gain);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerGain(String id, float gain) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerGain(String id, float gain) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerGain(String id, float gain) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort setTunerGain(String id, float gain) exception " + e.getMessage());
            }
        }
    }

    public float getTunerGain(String id)  {
        synchronized(this.portAccess){
            try{
            if ( digitalTunerListener != null ){
                return digitalTunerListener.fe_getTunerGain(id);
            } else {
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGain(String id) callback listener not defined");
                }
                throw new FrontendException("InDigitalTunerPort getTunerGain(String id) callback listener not defined");
            }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGain(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerGain(String id) exception " + e.getMessage());
            }
            return (float)-1.0;
        }
    }

    public void setTunerReferenceSource(String id, int source)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    digitalTunerListener.fe_setTunerReferenceSource(id, source);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerReferenceSource(String id, int source) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerReferenceSource(String id, int source) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerReferenceSource(String id, int source) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort setTunerReferenceSource(String id, int source) exception " + e.getMessage());
            }
        }
    }

    public int getTunerReferenceSource(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerReferenceSource(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerReferenceSource(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerReferenceSource(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerReferenceSource(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerReferenceSource(String id) exception " + e.getMessage());
            }
            return -1;
        }
    }

    public void setTunerEnable(String id, boolean enable)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    digitalTunerListener.fe_setTunerEnable(id, enable);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerEnable(String id, boolean enable) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerEnable(String id, boolean enable) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerEnable(String id, boolean enable) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort setTunerEnable(String id, boolean enable) exception " + e.getMessage());
            }
        }
    }

    public boolean getTunerEnable(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerEnable(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerEnable(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerEnable(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerEnable(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerEnable(String id) exception " + e.getMessage());
            }
            return false;
        }
    }

    public void setTunerOutputSampleRate(String id, double sr)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    digitalTunerListener.fe_setTunerOutputSampleRate(id, sr);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) exception " + e.getMessage());
            }
        }
    }

    public double getTunerOutputSampleRate(String id)  {
        synchronized(this.portAccess){
            try{
                if ( digitalTunerListener != null ){
                    return digitalTunerListener.fe_getTunerOutputSampleRate(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerOutputSampleRate(String id) callback listener not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerOutputSampleRate(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerOutputSampleRate(String id) exception " + e.getMessage());
                }
                System.out.println("InDigitalTunerPort getTunerOutputSampleRate(String id) exception " + e.getMessage());
            }
            return -1.0;
        }
    }

    public void setDigitalTunerListener( DigitalTunerListener newListener ) {
        digitalTunerListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
