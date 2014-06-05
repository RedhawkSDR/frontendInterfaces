package frontend;

import FRONTEND.RFInfoPkt;
import frontend.RFSourceDelegate;

public class InRFSourcePort extends FRONTEND.RFSourcePOA {

    protected String name;
 
    protected Object portAccess = null;

    protected RFSourceDelegate delegate = null;    

    public InRFSourcePort( String portName) {
        this(portName, null);
    }

    public InRFSourcePort( String portName,
                         RFSourceDelegate d) {
        this.name = portName;
        this.delegate = d;
        this.portAccess = new Object();
    }

    public RFInfoPkt[] available_rf_inputs() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ){ 
                    return delegate.fe_getAvailableRFInputs();
                }
            }catch(Exception e){
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
                }
            }catch(Exception e){
                System.out.println("InRFSourcePort available_rf_inputs(RFInfoPkt[] data) exception " + e.getMessage());
            }
        }
    }

    public RFInfoPkt current_rf_input() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null){
                    return (delegate.fe_getCurrentRFInput());
                }
            }catch(Exception e){
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
                }
            }catch(Exception e){
                System.out.println("InRFSourcePort current_rf_input(RFInfoPkt data) exception " + e.getMessage());
            }
        }
    }

    public void setDelegate( RFSourceDelegate d ) {
        delegate = d;
    }
}
