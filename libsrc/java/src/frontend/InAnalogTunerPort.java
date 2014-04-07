package frontend;

import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;
import frontend.AnalogTunerDelegate;

public class InAnalogTunerPort extends FRONTEND.AnalogTunerPOA {

    protected String name;

    protected Object portAccess = null;

    protected AnalogTunerDelegate delegate = null;

    public InAnalogTunerPort(String portName,
                             AnalogTunerDelegate d){
        this.name = portName;
        this.delegate = d;
        this.portAccess = new Object();
    }

    public String getTunerType(String id) throws BadParameterException, FrontendException, NotSupportedException {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerType(id);
                } else {
                    throw new FrontendException("InAnalogTunerPort getTunerType(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerDeviceControl(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerGroupId(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerRfFlowId(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerStatus(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort setTunerCenterFrequency(String id, double freq) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerCenterFrequency(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort setTunerBandwidth(String id, double bw) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerBandwidth(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort setTunerAgcEnable(String id, boolean enable) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerAgcEnable(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort setTunerGain(String id, float gain) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerGain(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort setTunerReferenceSource(String id, int source) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerReferenceSource(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort setTunerEnable(String id, boolean enable) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
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
                    throw new FrontendException("InAnalogTunerPort getTunerEnable(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                throw e;
            }catch(FrontendException e){
                throw e;
            }catch(NotSupportedException e){
                throw e;
            }
        }
    }

    public void setDelegate( AnalogTunerDelegate d ) {
        delegate = d;
    }
}
