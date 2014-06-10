package frontend;

import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;
import frontend.FrontendTunerDelegate;

public class InFrontendTunerPort extends FRONTEND.FrontendTunerPOA {

    protected String name;

    protected Object portAccess = null;

    protected FrontendTunerDelegate delegate = null;

    public InFrontendTunerPort( String portName) {
        this(portName, null);
    }

    public InFrontendTunerPort( String portName,
                                FrontendTunerDelegate d) {
        this.name = portName;
        this.delegate = d;
        this.portAccess = new Object();
    }


    public String getTunerType(String id) throws BadParameterException, FrontendException, NotSupportedException{
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.getTunerType(id);
                } else {
                    throw new FrontendException("InFrontendTunerPort getTunerType(String id) callback delegate not defined");
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
                    return delegate.getTunerDeviceControl(id);
                } else {
                    throw new FrontendException("InFrontendTunerPort getTunerDeviceControl(String id) callback delegate not defined");
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
                    return delegate.getTunerGroupId(id);
                } else {
                    throw new FrontendException("InFrontendTunerPort getTunerGroupId(String id) callback delegate not defined");
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
                    return delegate.getTunerRfFlowId(id);
                } else {
                    throw new FrontendException("InFrontendTunerPort getTunerRfFlowId(String id) callback delegate not defined");
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
                    return delegate.getTunerStatus(id);
                } else {
                    throw new FrontendException("InFrontendTunerPort getTunerStatus(String id) callback delegate not defined");
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

    public void setDelegate( FrontendTunerDelegate d ) {
        delegate = d;
    }
}
