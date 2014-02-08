package frontend;

import FRONTEND.RFInfoPkt;
import frontend.RFSourceDelegate;
import org.apache.log4j.Logger;

public class InRFSourcePort extends FRONTEND.RFSourcePOA {

    protected String name;
 
    protected Logger logger = null;

    protected Object portAccess = null;

    protected RFSourceDelegate delegate = null;    

    public InRFSourcePort( String portName) {
        this( portName, null, null);
    }

    public InRFSourcePort( String portName,
                         RFSourceDelegate d) {
        this( portName, d, null);
    }

    public InRFSourcePort( String portName,
                         RFSourceDelegate d,
                         Logger logger) {
        this.name = portName;
        this.delegate = d;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public RFInfoPkt[] available_rf_inputs() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){ 
                    return delegate.fe_getAvailableRFInputs();
                } else {
                    if (this.logger != null){
                        logger.error("InRFSourcePort available_rf_inputs() callback delegate not defined.");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InRFSourcePort available_rf_inputs() exception " + e.getMessage());
                }
                System.out.println("InRFSourcePort available_rf_inputs() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void available_rf_inputs(RFInfoPkt[] data) {
        synchronized(this.portAccess){
            try{
                if ( delegate != null){ 
                    delegate.fe_setAvailableRFInputs(data);
                } else {
                    if (this.logger != null){
                        logger.error("InRFSourcePort available_rf_inputs(RFInfoPkt[] data) callback delegate not defined.");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InRFSourcePort available_rf_inputs(RFInfoPkt[] data) exception " + e.getMessage());
                }
                System.out.println("InRFSourcePort available_rf_inputs(RFInfoPkt[] data) exception " + e.getMessage());
            }
        }
    }

    public RFInfoPkt current_rf_input() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null){
                    return (delegate.fe_getCurrentRFInput());
                } else {
                    if (this.logger != null){
                        logger.error("InRFSourcePort current_rf_input() callback delegate not defined.");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InRFSourcePort current_rf_input() exception " + e.getMessage());
                }
                System.out.println("InRFSourcePort current_rf_input() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void current_rf_input(RFInfoPkt data) {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    delegate.fe_setCurrentRFInput(data);
                } else {
                    if (this.logger != null){
                        logger.error("InRFSourcePort current_rf_input(RFInfoPkt data) callback delegate not defined.");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InRFSourcePort current_rf_input(RFInfoPkt data) exception " + e.getMessage());
                }
                System.out.println("InRFSourcePort current_rf_input(RFInfoPkt data) exception " + e.getMessage());
            }
        }
    }

    public void setDelegate( RFSourceDelegate d ) {
        delegate = d;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
