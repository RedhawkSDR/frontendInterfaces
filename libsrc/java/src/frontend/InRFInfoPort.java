package frontend;

import frontend.RFInfoDelegate;
import FRONTEND.RFInfoPkt;

public class InRFInfoPort extends FRONTEND.RFInfoPOA {

    protected String name;
 
    protected Object portAccess = null;

    protected RFInfoDelegate delegate = null;    

    public InRFInfoPort( String portName) {
        this(portName, null);
    }

    public InRFInfoPort( String portName,
                         RFInfoDelegate d) {
        this.name = portName;
        this.delegate = d;
        this.portAccess = new Object();
    }

    public String rf_flow_id() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){ 
                    return delegate.get_rf_flow_id(this.name);
                }
            }catch(Exception e){
                System.out.println("InRFInfoPort rf_flow_id() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void rf_flow_id(String data) {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    delegate.set_rf_flow_id(this.name, data);
                }
            }catch(Exception e){
                System.out.println("InRFInfoPort rf_flow_id(String data) exception " + e.getMessage());
            }
        }
    }

    public RFInfoPkt rfinfo_pkt() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    return (delegate.get_rfinfo_pkt(this.name));
                } else { 
                    return null;
                }
            }catch(Exception e){
                System.out.println("InRFInfoPort rfinfo_pkt() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void rfinfo_pkt(RFInfoPkt data) {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    delegate.set_rfinfo_pkt(this.name, data);
                }
            }catch(Exception e){
                System.out.println("InRFInfoPort rfinfo_pkt(RFInfoPkt data) exception " + e.getMessage());
            }
        }
    }

    public void setDelegate( RFInfoDelegate d ) {
        delegate = d;
    }
}
