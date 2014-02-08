package frontend;

import org.apache.log4j.Logger;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;
import frontend.AnalogTunerDelegate;

public class InAnalogTunerPort extends FRONTEND.AnalogTunerPOA {

    protected String name;

    protected Logger logger = null;

    protected Object portAccess = null;

    protected AnalogTunerDelegate delegate = null;

    public InAnalogTunerPort(String portName){
        this( portName, null, null);
    }

    public InAnalogTunerPort(String portName,
                             AnalogTunerDelegate d){
        this( portName, d, null);
    }

    public InAnalogTunerPort(String portName,
                             AnalogTunerDelegate d,
                             Logger logger){
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
                        logger.error("InAnalogTunerPort getTunerType(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerType(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerType(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerType(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerType(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerDeviceControl(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerDeviceControl(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerDeviceControl(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerDeviceControl(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerDeviceControl(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerGroupId(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerGroupId(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGroupId(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGroupId(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGroupId(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerRfFlowId(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerRfFlowId(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerRfFlowId(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerRfFlowId(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerRfFlowId(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerStatus(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerStatus(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerStatus(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerStatus(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerStatus(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerCenterFrequency(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerCenterFrequency(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerCenterFrequency(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerCenterFrequency(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerCenterFrequency(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort setTunerBandwidth(String id, double bw) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerBandwidth(String id, double bw) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerBandwidth(String id, double bw) BadParameterException " + e.getMessage());
                }   
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerBandwidth(String id, double bw) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerBandwidth(String id, double bw) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerBandwidth(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerBandwidth(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerBandwidth(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerBandwidth(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerBandwidth(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerAgcEnable(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerAgcEnable(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerAgcEnable(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerAgcEnable(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerAgcEnable(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort setTunerGain(String id, float gain) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerGain(String id, float gain) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerGain(String id, float gain) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerGain(String id, float gain) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerGain(String id, float gain) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerGain(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerGain(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGain(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGain(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerGain(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort setTunerReferenceSource(String id, int source) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerReferenceSource(String id, int source) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerReferenceSource(String id, int source) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerReferenceSource(String id, int source) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerReferenceSource(String id, int source) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerReferenceSource(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerReferenceSource(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerReferenceSource(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerReferenceSource(String id) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerReferenceSource(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort setTunerEnable(String id, boolean enable) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort setTunerEnable(String id, boolean enable) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerEnable(String id, boolean enable) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerEnable(String id, boolean enable) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort setTunerEnable(String id, boolean enable) NotSupportedException " + e.getMessage());
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
                        logger.error("InAnalogTunerPort getTunerEnable(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InAnalogTunerPort getTunerEnable(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerEnable(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerEnable(String id) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InAnalogTunerPort getTunerEnable(String id) NotSupportedException " + e.getMessage());
                }   
                throw e;
            }
        }
    }

    public void setDelegate( AnalogTunerDelegate d ) {
        delegate = d;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
