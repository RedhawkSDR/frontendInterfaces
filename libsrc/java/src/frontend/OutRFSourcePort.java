package frontend;

import java.util.HashMap;
import java.util.Map;
import org.ossie.component.QueryableUsesPort;
import FRONTEND.RFSourceOperations;
import FRONTEND.RFSourceHelper;
import FRONTEND.RFInfoPkt;


public class OutRFSourcePort extends QueryableUsesPort<RFSourceOperations> implements RFSourceOperations {

    protected String name;
 
    protected Object updatingPortsLock;

    /**
     * Map of connection Ids to port objects
     */
    protected Map<String, RFSourceOperations> outConnections = new HashMap<String, RFSourceOperations>();

    public OutRFSourcePort( String portName) {
        super(portName);
        this.name = portName;
        this.outConnections = new HashMap<String, RFSourceOperations>();
    }

    protected RFSourceOperations narrow(org.omg.CORBA.Object connection) {
        RFSourceOperations ops = RFSourceHelper.narrow(connection);
        return ops;
    }

    public void connectPort(final org.omg.CORBA.Object connection, final String connectionId) throws CF.PortPackage.InvalidPort, CF.PortPackage.OccupiedPort {
        try {
            synchronized (this.updatingPortsLock) {
                super.connectPort(connection, connectionId);
                final RFSourceOperations port = RFSourceHelper.narrow(connection);
                this.outConnections.put(connectionId, port);
                this.active = true;
            }
        } catch (final Throwable t) {
            t.printStackTrace();
        }

    }

    public void disconnectPort(final String connectionId) {
        synchronized (this.updatingPortsLock) {
            super.disconnectPort(connectionId);
            this.outConnections.remove(connectionId);
            this.active = (this.outConnections.size() != 0);
        }
    }

    public RFInfoPkt[] available_rf_inputs() {
        RFInfoPkt[] retval = null;

        synchronized(updatingPortsLock){
            if (this.active) {
                for (RFSourceOperations p : this.outConnections.values()) {
                    retval = p.available_rf_inputs();
                }
            }
        }
        return retval;
    }

    public void available_rf_inputs(RFInfoPkt[] data) {
        synchronized(updatingPortsLock){
            if (this.active) {
                for (RFSourceOperations p : this.outConnections.values()) {
                    p.available_rf_inputs(data);
                }
            }
        }
    }

    public RFInfoPkt current_rf_input() {
        RFInfoPkt retval = null;

        synchronized(updatingPortsLock){
            if (this.active) {
                for (RFSourceOperations p : this.outConnections.values()) {
                    retval = p.current_rf_input();
                }
            }
        }
        return retval;
    }

    public void current_rf_input(RFInfoPkt data) {
        synchronized(updatingPortsLock){
            if (this.active) {
                for (RFSourceOperations p : this.outConnections.values()) {
                    p.current_rf_input(data);
                }
            }
        }
    }
}

