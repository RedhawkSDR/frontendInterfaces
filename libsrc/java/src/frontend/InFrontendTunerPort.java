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


    public String getTunerType(String id) {
        synchronized(this.portAccess){
            try{
                if ( frontendTunerListener != null ){
                    return frontendTunerListener.fe_getTunerType(id);
                } else {
                    if (this.logger != null){
                        logger.error("InFrontendTunerPort getTunerType(String id) callback listener not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerType(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerType(String id) exception " + e.getMessage());
                }
                System.out.println("InFrontendTunerPort getTunerType(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public boolean getTunerDeviceControl(String id) {
        synchronized(this.portAccess){
            try{
                if ( frontendTunerListener != null ){
                    return frontendTunerListener.fe_getTunerDeviceControl(id);
                } else {
                    if (this.logger != null){
                        logger.error("InFrontendTunerPort getTunerDeviceControl(String id) callback listener not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerDeviceControl(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerDeviceControl(String id) exception " + e.getMessage());
                }
                System.out.println("InFrontendTunerPort getTunerDeviceControl(String id) exception " + e.getMessage());
            }
            return false;
        }
    }

    public String getTunerGroupId(String id) {
        synchronized(this.portAccess){
            try{
                if ( frontendTunerListener != null ){
                    return frontendTunerListener.fe_getTunerGroupId(id);
                } else {
                    if (this.logger != null){
                        logger.error("InFrontendTunerPort getTunerGroupId(String id) callback listener not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerGroupId(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerGroupId(String id) exception " + e.getMessage());
                }
                System.out.println("InFrontendTunerPort getTunerGroupId(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public String getTunerRfFlowId(String id) {
        synchronized(this.portAccess){
            try{
                if ( frontendTunerListener != null ){
                    return frontendTunerListener.fe_getTunerRfFlowId(id);
                } else {
                    if (this.logger != null){
                        logger.error("InFrontendTunerPort getTunerRfFlowId(String id) callback listener not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerRfFlowId(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerRfFlowId(String id) exception " + e.getMessage());
                }
                System.out.println("InFrontendTunerPort getTunerRfFlowId(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public CF.DataType[] getTunerStatus(String id) {
        synchronized(this.portAccess){
            try{
                if ( frontendTunerListener != null ){
                    return frontendTunerListener.fe_getTunerStatus(id);
                } else {
                    if (this.logger != null){
                        logger.error("InFrontendTunerPort getTunerStatus(String id) callback listener not defined");
                    }
                    throw new FrontendException("InFrontendTunerPort getTunerStatus(String id) callback listener not defined");
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InFrontendTunerPort getTunerStatus(String id) exception " + e.getMessage());
                }
                System.out.println("InFrontendTunerPort getTunerStatus(String id) exception " + e.getMessage());
            }
            return null;
        }
    }

    public void setFrontendTunerListener( FrontendTunerListener newListener ) {
        frontendTunerListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
