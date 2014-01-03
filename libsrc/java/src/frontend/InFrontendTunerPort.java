package frontend;

import org.apache.log4j.Logger;
import frontend.FrontendTunerListener;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public class InFrontendTunerPort extends FRONTEND.FrontendTunerPOA {

    protected String name;

    protected Logger logger = null;

    protected Object portAccess = null;

    protected FrontendTunerListener frontendTunerListener = null;

    public InFrontendTunerPort( String portName) {
        this( portName, null, null);
    }

    public InFrontendTunerPort( String portName,
                                FrontendTunerListener listener) {
        this( portName, listener, null);
    }

    public InFrontendTunerPort( String portName,
                                FrontendTunerListener listener,
                                Logger logger) {
        this.name = portName;
        this.frontendTunerListener = listener;
        this.logger = logger;
        this.portAccess = new Object();
    }


    public String getTunerType(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( frontendTunerListener != null ){
                return frontendTunerListener.getTunerType(id);
            } else {
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerType(String id) callback listener not defined");
                }
                throw new FrontendException("InFrontendTunerPort getTunerType(String id) callback listener not defined");
            }
        }
    }

    public boolean getTunerDeviceControl(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( frontendTunerListener != null ){
                return frontendTunerListener.getTunerDeviceControl(id);
            } else {
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerDeviceControl(String id) callback listener not defined");
                }
                throw new FrontendException("InFrontendTunerPort getTunerDeviceControl(String id) callback listener not defined");
            }
        }
    }

    public String getTunerGroupId(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( frontendTunerListener != null ){
                return frontendTunerListener.getTunerGroupId(id);
            } else {
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerGroupId(String id) callback listener not defined");
                }
                throw new FrontendException("InFrontendTunerPort getTunerGroupId(String id) callback listener not defined");
            }
        }
    }

    public String getTunerRfFlowId(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( frontendTunerListener != null ){
                return frontendTunerListener.getTunerRfFlowId(id);
            } else {
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerRfFlowId(String id) callback listener not defined");
                }
                throw new FrontendException("InFrontendTunerPort getTunerRfFlowId(String id) callback listener not defined");
            }
        }
    }

    public CF.DataType[] getTunerStatus(String id) throws FrontendException, BadParameterException, NotSupportedException {
        synchronized(this.portAccess){
            if ( frontendTunerListener != null ){
                return frontendTunerListener.getTunerStatus(id);
            } else {
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerStatus(String id) callback listener not defined");
                }
                throw new FrontendException("InFrontendTunerPort getTunerStatus(String id) callback listener not defined");
            }
        }
    }

    public void setFrontendTunerListener( FrontendTunerListener newListener ) {
        frontendTunerListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
