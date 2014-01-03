package frontend;

import FRONTEND.RFInfoPkt;
import org.apache.log4j.Logger;
import frontend.RFInfoListener;

public class InRFInfoPort extends FRONTEND.RFInfoPOA {

    protected String name;
 
    protected Logger logger = null;

    protected Object portAccess = null;

    protected RFInfoListener rfInfoListener = null;    

    public InRFInfoPort( String portName) {
        this( portName, null, null);
    }

    public InRFInfoPort( String portName,
                         RFInfoListener listener) {
        this( portName, listener, null);
    }

    public InRFInfoPort( String portName,
                         RFInfoListener listener,
                         Logger logger) {
        this.name = portName;
        this.rfInfoListener = listener;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public String rf_flow_id() {
        synchronized(this.portAccess){
            if ( rfInfoListener != null ){ 
                return rfInfoListener.getRFFlowId();
            } else { 
                if (this.logger != null){
                    logger.error("InRFInfoPort rf_flow_id() callback listener not defined.");
                }
                return null;
            }
        }
    }

    public void rf_flow_id(String data) {
        synchronized(this.portAccess){
            if ( rfInfoListener != null) {
                rfInfoListener.setRFFlowId(data);
            } else { 
                if (this.logger != null){
                    logger.error("InRFInfoPort rf_flow_id(String data) callback listener not defined.");
                }
            }
        }
    }

    public RFInfoPkt rfinfo_pkt() {
        synchronized(this.portAccess){
            if ( rfInfoListener != null) {
                return (rfInfoListener.getRFInfoPkt());
            } else { 
                if (this.logger != null){
                    logger.error("InRFInfoPort rfinfo_pkt() callback listener not defined.");
                }
                return null;
            }
        }
    }

    public void rfinfo_pkt(RFInfoPkt data) {
        synchronized(this.portAccess){
            if ( rfInfoListener != null) {
                rfInfoListener.setRFInfoPkt(data);
            } else { 
                if (this.logger != null){
                    logger.error("InRFInfoPort rfinfo_pkt(RFInfoPkt data) callback listener not defined.");
                }
            }
        }
    }

    public void setRFInfoListener( RFInfoListener newListener ) {
        rfInfoListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
