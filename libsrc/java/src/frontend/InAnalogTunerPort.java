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

    public String getTunerType(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerType(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerType(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerType(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerType(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerType(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public boolean getTunerDeviceControl(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerDeviceControl(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerDeviceControl(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerDeviceControl(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerDeviceControl(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerDeviceControl(String id) exception " + e.getMessage());
            }
            return false;
        }
    }

    public String getTunerGroupId(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerGroupId(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerGroupId(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerGroupId(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGroupId(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerGroupId(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public String getTunerRfFlowId(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerRfFlowId(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerRfFlowId(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerRfFlowId(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerRfFlowId(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerRfFlowId(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public CF.DataType[] getTunerStatus(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerStatus(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerStatus(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerStatus(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerStatus(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerStatus(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public void setTunerCenterFrequency(String id, double freq)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    analogTunerListener.fe_setTunerCenterFrequency(id, freq);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) exception " + e.getMessage());
            }
        }
    }

    public double getTunerCenterFrequency(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerCenterFrequency(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerCenterFrequency(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerCenterFrequency(String id) callback listener not defined");
                }
            }catch(Exception e){ 
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerCenterFrequency(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerCenterFrequency(String id) exception " + e.getMessage());
            }
            return -1.0;
        }
    }

    public void setTunerBandwidth(String id, double bw)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    analogTunerListener.fe_setTunerBandwidth(id, bw);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort setTunerBandwidth(String id, double bw) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerBandwidth(String id, double bw) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerBandwidth(String id, double bw) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort setTunerBandwidth(String id, double bw) exception " + e.getMessage());
            }
        }
    }

    public double getTunerBandwidth(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerBandwidth(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerBandwidth(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerBandwidth(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerBandwidth(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerBandwidth(String id) exception " + e.getMessage());
            }
            return -1;
        }
    }

    public void setTunerAgcEnable(String id, boolean enable)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    analogTunerListener.fe_setTunerAgcEnable(id, enable);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) exception " + e.getMessage());
            }
        }
    }

    public boolean getTunerAgcEnable(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerAgcEnable(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerAgcEnable(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerAgcEnable(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerAgcEnable(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerAgcEnable(String id) exception " + e.getMessage());
            }
            return false;
        }
    }

    public void setTunerGain(String id, float gain)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    analogTunerListener.fe_setTunerGain(id, gain);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort setTunerGain(String id, float gain) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerGain(String id, float gain) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerGain(String id, float gain) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort setTunerGain(String id, float gain) exception " + e.getMessage());
            }
        }
    }

    public float getTunerGain(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerGain(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerGain(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerGain(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGain(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerGain(String id) exception " + e.getMessage());
            }
            return (float)-1;
        }
    }

    public void setTunerReferenceSource(String id, int source)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    analogTunerListener.fe_setTunerReferenceSource(id, source);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort setTunerReferenceSource(String id, int source) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerReferenceSource(String id, int source) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGain(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerGain(String id) exception " + e.getMessage());
            }
        }
    }

    public int getTunerReferenceSource(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerReferenceSource(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerReferenceSource(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerReferenceSource(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerReferenceSource(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort getTunerReferenceSource(String id) exception " + e.getMessage());
            }
            return -1;
        }
    }

    public void setTunerEnable(String id, boolean enable)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    analogTunerListener.fe_setTunerEnable(id, enable);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort setTunerEnable(String id, boolean enable) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerEnable(String id, boolean enable) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerEnable(String id, boolean enable) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort setTunerEnable(String id, boolean enable) exception " + e.getMessage());
            }
        }
    }

    public boolean getTunerEnable(String id)  {
        synchronized(this.portAccess){
            try{
                if ( analogTunerListener != null ){
                    return analogTunerListener.fe_getTunerEnable(id);
                } else {
                    if (this.logger != null){
                        logger.error("InAnalogTunerPort getTunerEnable(String id) callback listener not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerEnable(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerEnable(String id) exception " + e.getMessage());
                }
                System.out.println("InAnalogTunerPort ) getTunerEnable(String id) exception " + e.getMessage());
            }
            return false;
        }
    }

    public void setAnalogTunerListener( AnalogTunerListener newListener ) {
        analogTunerListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
