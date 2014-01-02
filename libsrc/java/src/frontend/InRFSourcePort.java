package frontend;

import FRONTEND.RFInfoPkt;
import org.apache.log4j.Logger;
import frontend.RFSourceListener;

public class InRFSourcePort extends FRONTEND.RFSourcePOA {

    protected String name;
 
    protected Logger logger = null;

    protected Object portAccess = null;

    protected RFSourceListener rfSourceListener = null;    

    public InRFSourcePort( String portName) {
        this( portName, null, null);
    }

    public InRFSourcePort( String portName,
                         RFSourceListener listener) {
        this( portName, listener, null);
    }

    public InRFSourcePort( String portName,
                         RFSourceListener listener,
                         Logger logger) {
        this.name = portName;
        this.rfSourceListener = listener;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public RFInfoPkt[] available_rf_inputs()
    {
        synchronized(this.portAccess){
            if ( rfSourceListener != null ){ 
                return rfSourceListener.getAvailableRFInputs();
            } else {
                return null;
            }
        }
    }

    public void available_rf_inputs(RFInfoPkt[] data)
    {
        synchronized(this.portAccess){
            if ( rfSourceListener != null){ 
                rfSourceListener.setAvailableRFInputs(data);
            }
        }
    }

    public RFInfoPkt current_rf_input()
    {
        synchronized(this.portAccess){
            if ( rfSourceListener != null){
                return (rfSourceListener.getCurrentRFInput());
            } else {
                return null;
            }
        }
    }

    public void current_rf_input(RFInfoPkt data)
    {
        synchronized(this.portAccess){
            if ( rfSourceListener != null) {
                rfSourceListener.setCurrentRFInput(data);
            }
        }
    }

    public void setRFSourceListener( RFSourceListener newListener ) {
        rfSourceListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
