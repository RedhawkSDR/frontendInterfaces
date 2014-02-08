package frontend;

import org.apache.log4j.Logger;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;
import frontend.DigitalTunerDelegate;

public class InDigitalTunerPort extends FRONTEND.DigitalTunerPOA {

    protected String name;

    protected Logger logger = null;

    protected Object portAccess = null;

    protected DigitalTunerDelegate delegate = null;

    public InDigitalTunerPort( String portName) {
        this( portName, null, null);
    }

    public InDigitalTunerPort( String portName,
                                DigitalTunerDelegate d) {
        this( portName, d, null);
    }

    public InDigitalTunerPort( String portName,
                                DigitalTunerDelegate d,
                                Logger logger) {
        this.name = portName;
        this.delegate = d;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public String getTunerType(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerType(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerType(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerType(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerType(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerType(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerType(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public boolean getTunerDeviceControl(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerDeviceControl(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerDeviceControl(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerDeviceControl(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerDeviceControl(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerDeviceControl(String id) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerDeviceControl(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public String getTunerGroupId(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerGroupId(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerGroupId(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerGroupId(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGroupId(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGroupId(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGroupId(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public String getTunerRfFlowId(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerRfFlowId(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerRfFlowId(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerRfFlowId(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerRfFlowId(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerRfFlowId(String id) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerRfFlowId(String id) NotSupportedException " + e.getMessage());
                }   
                throw e;
            }
        }
    }

    public CF.DataType[] getTunerStatus(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerStatus(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerStatus(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerStatus(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerStatus(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerStatus(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerStatus(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public void setTunerCenterFrequency(String id, double freq) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    delegate.fe_setTunerCenterFrequency(id, freq);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerCenterFrequency(String id, double freq) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public double getTunerCenterFrequency(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerCenterFrequency(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerCenterFrequency(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerCenterFrequency(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerCenterFrequency(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerCenterFrequency(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerCenterFrequency(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public void setTunerBandwidth(String id, double bw) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    delegate.fe_setTunerBandwidth(id, bw);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerBandwidth(String id, double bw) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerBandwidth(String id, double bw) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerBandwidth(String id, double bw) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerBandwidth(String id, double bw) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerBandwidth(String id, double bw) NotSupportedException " + e.getMessage());
                }   
                throw e;
            }
        }
    }

    public double getTunerBandwidth(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerBandwidth(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerBandwidth(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerBandwidth(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerBandwidth(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerBandwidth(String id) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerBandwidth(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public void setTunerAgcEnable(String id, boolean enable) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    delegate.fe_setTunerAgcEnable(id, enable);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerAgcEnable(String id, boolean enable) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public boolean getTunerAgcEnable(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerAgcEnable(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerAgcEnable(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerAgcEnable(String id) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerAgcEnable(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerAgcEnable(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerAgcEnable(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public void setTunerGain(String id, float gain) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    delegate.fe_setTunerGain(id, gain);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerGain(String id, float gain) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerGain(String id, float gain) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerGain(String id, float gain) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerGain(String id, float gain) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerGain(String id, float gain) NotSupportedException " + e.getMessage());
                }   
                throw e;
            }
        }
    }

    public float getTunerGain(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerGain(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerGain(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerGain(String id) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGain(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGain(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerGain(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public void setTunerReferenceSource(String id, int source) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    delegate.fe_setTunerReferenceSource(id, source);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerReferenceSource(String id, int source) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerReferenceSource(String id, int source) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerReferenceSource(String id, int source) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerReferenceSource(String id, int source) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerReferenceSource(String id, int source) NotSupportedException " + e.getMessage());
                }   
                throw e;
            }
        }
    }

    public int getTunerReferenceSource(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerReferenceSource(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerReferenceSource(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerReferenceSource(String id) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerReferenceSource(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerReferenceSource(String id) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerReferenceSource(String id) NotSupportedException " + e.getMessage());
                }   
                throw e;
            }
        }
    }

    public void setTunerEnable(String id, boolean enable) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    delegate.fe_setTunerEnable(id, enable);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerEnable(String id, boolean enable) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerEnable(String id, boolean enable) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerEnable(String id, boolean enable) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerEnable(String id, boolean enable) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerEnable(String id, boolean enable) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public boolean getTunerEnable(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerEnable(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerEnable(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerEnable(String id) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerEnable(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerEnable(String id) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerEnable(String id) NotSupportedException " + e.getMessage());
                }   
                throw e;
            }
        }
    }

    public void setTunerOutputSampleRate(String id, double sr) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    delegate.fe_setTunerOutputSampleRate(id, sr);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort setTunerOutputSampleRate(String id, double sr) NotSupportedException " + e.getMessage());
                }   
                throw e;
            }
        }
    }

    public double getTunerOutputSampleRate(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerOutputSampleRate(id);
                } else {
                    if (this.logger != null){
                        logger.error("InDigitalTunerPort getTunerOutputSampleRate(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InDigitalTunerPort getTunerOutputSampleRate(String id) callback delegate not defined");
                }
           }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerOutputSampleRate(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerOutputSampleRate(String id) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InDigitalTunerPort getTunerOutputSampleRate(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public void setDelegate( DigitalTunerDelegate d ) {
        delegate = d;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
