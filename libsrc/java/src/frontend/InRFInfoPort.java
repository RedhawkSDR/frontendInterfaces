package frontend;

import frontend.RFInfoDelegate;
import FRONTEND.RFInfoPkt;
import org.apache.log4j.Logger;

public class InRFInfoPort extends FRONTEND.RFInfoPOA {

    protected String name;
 
    protected Logger logger = null;

    protected Object portAccess = null;

    protected RFInfoDelegate delegate = null;    

    public InRFInfoPort( String portName) {
        this( portName, null, null);
    }

    public InRFInfoPort( String portName,
                         RFInfoDelegate d) {
        this( portName, d, null);
    }

    public InRFInfoPort( String portName,
                         RFInfoDelegate d,
                         Logger logger) {
        this.name = portName;
        this.delegate = d;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public String rf_flow_id() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){ 
                    return delegate.fe_getRFFlowId();
                } else { 
                    if (this.logger != null){
                        logger.error("InRFInfoPort rf_flow_id() callback delegate not defined.");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InRFInfoPort rf_flow_id() exception " + e.getMessage());
                }
                System.out.println("InRFInfoPort rf_flow_id() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void rf_flow_id(String data) {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    delegate.fe_setRFFlowId(data);
                } else { 
                    if (this.logger != null){
                        logger.error("InRFInfoPort rf_flow_id(String data) callback delegate not defined.");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InRFInfoPort rf_flow_id(String data) exception " + e.getMessage());
                }
                System.out.println("InRFInfoPort rf_flow_id(String data) exception " + e.getMessage());
            }
        }
    }

    public RFInfoPkt rfinfo_pkt() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    return (delegate.fe_getRFInfoPkt());
                } else { 
                    if (this.logger != null){
                        logger.error("InRFInfoPort rfinfo_pkt() callback delegate not defined.");
                    }
                    return null;
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InRFInfoPort rfinfo_pkt() exception " + e.getMessage());
                }
                System.out.println("InRFInfoPort rfinfo_pkt() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void rfinfo_pkt(RFInfoPkt data) {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    delegate.fe_setRFInfoPkt(data);
                } else { 
                    if (this.logger != null){
                        logger.error("InRFInfoPort rfinfo_pkt(RFInfoPkt data) callback delegate not defined.");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InRFInfoPort rfinfo_pkt(RFInfoPkt data) exception " + e.getMessage());
                }
                System.out.println("InRFInfoPort rfinfo_pkt(RFInfoPkt data) exception " + e.getMessage());
            }
        }
    }

    public void setDelegate( RFInfoDelegate d ) {
        delegate = d;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
