package frontend;

import org.apache.log4j.Logger;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;
import frontend.FrontendTunerDelegate;

public class InFrontendTunerPort extends FRONTEND.FrontendTunerPOA {

    protected String name;

    protected Logger logger = null;

    protected Object portAccess = null;

    protected FrontendTunerDelegate delegate = null;

    public InFrontendTunerPort( String portName) {
        this( portName, null, null);
    }

    public InFrontendTunerPort( String portName,
                                FrontendTunerDelegate d) {
        this( portName, d, null);
    }

    public InFrontendTunerPort( String portName,
                                FrontendTunerDelegate d,
                                Logger logger) {
        this.name = portName;
        this.delegate = d;
        this.logger = logger;
        this.portAccess = new Object();
    }


    public String getTunerType(String id) throws BadParameterException, FrontendException, NotSupportedException{
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){
                    return delegate.fe_getTunerType(id);
                } else {
                    if (this.logger != null){
                        logger.error("InFrontendTunerPort getTunerType(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerType(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerType(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerType(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerType(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InFrontendTunerPort getTunerDeviceControl(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerDeviceControl(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerDeviceControl(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerDeviceControl(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerDeviceControl(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InFrontendTunerPort getTunerGroupId(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerGroupId(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerGroupId(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerGroupId(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerGroupId(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InFrontendTunerPort getTunerRfFlowId(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerRfFlowId(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerRfFlowId(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerRfFlowId(String id) FrontendException " + e.getMessage());
                }   
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerRfFlowId(String id) NotSupportedException " + e.getMessage());
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
                        logger.error("InFrontendTunerPort getTunerStatus(String id) callback delegate not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerStatus(String id) callback delegate not defined");
                }
            }catch(BadParameterException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerStatus(String id) BadParameterException " + e.getMessage());
                }
                throw e;
            }catch(FrontendException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerStatus(String id) FrontendException " + e.getMessage());
                }
                throw e;
            }catch(NotSupportedException e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerStatus(String id) NotSupportedException " + e.getMessage());
                }
                throw e;
            }
        }
    }

    public void setDelegate( FrontendTunerDelegate d ) {
        delegate = d;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
