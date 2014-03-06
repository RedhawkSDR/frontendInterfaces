package frontend;

import org.apache.log4j.Logger;
import java.util.HashMap;
import java.util.Map;
import org.ossie.component.QueryableUsesPort;
import FRONTEND.FrontendTunerOperations;
import FRONTEND.FrontendTunerHelper;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public class OutFrontendTunerPort extends QueryableUsesPort<FrontendTunerOperations> implements FrontendTunerOperations {

    protected String name;

    protected Logger logger = null;

    protected Object updatingPortsLock;

    /**
     * Map of connection Ids to port objects
     */
    protected Map<String, FrontendTunerOperations> outConnections = new HashMap<String, FrontendTunerOperations>();

    public OutFrontendTunerPort(String portName) {
        this( portName, null);
    }

    public OutFrontendTunerPort(String portName,
                                Logger logger) { 
        super(portName);
        this.name = portName;
        this. logger = logger;
        this.outConnections = new HashMap<String, FrontendTunerOperations>();
    }

    protected FrontendTunerOperations narrow(org.omg.CORBA.Object connection) {
        FrontendTunerOperations ops = FrontendTunerHelper.narrow(connection);
        return ops; 
    }

    public void connectPort(final org.omg.CORBA.Object connection, final String connectionId) throws CF.PortPackage.InvalidPort, CF.PortPackage.OccupiedPort {
        try {
            synchronized (this.updatingPortsLock) {
                super.connectPort(connection, connectionId);
                final FrontendTunerOperations port = FrontendTunerHelper.narrow(connection);
                this.outConnections.put(connectionId, port);
                this.active = true;
            }
        } catch (final Throwable t) {
            t.printStackTrace();
        }

    }

    public void disconnectPort(final String connectionId) throws CF.PortPackage.InvalidPort {
        synchronized (this.updatingPortsLock) {
            super.disconnectPort(connectionId);
            this.outConnections.remove(connectionId);
            this.active = (this.outConnections.size() != 0);
        }
    }

    public String getTunerType(String id) throws FrontendException, BadParameterException, NotSupportedException {
        String retval = "";

        synchronized(this.updatingPortsLock) {
            if (this.active) {
                for (FrontendTunerOperations p : this.outConnections.values()) {
                    retval = p.getTunerType(id);
                }
            }
        }
        return retval;
    }
 
    public boolean getTunerDeviceControl(String id) throws FrontendException, BadParameterException, NotSupportedException {
        boolean retval = false;

        synchronized(this.updatingPortsLock) { 
            if (this.active) {
                for (FrontendTunerOperations p : this.outConnections.values()) {
                    retval = p.getTunerDeviceControl(id);
                }
            }
        }
        return retval;
    }
 
    public String getTunerGroupId(String id) throws FrontendException, BadParameterException, NotSupportedException {
        String retval = "";

        synchronized(this.updatingPortsLock) {
            if (this.active) {
                for (FrontendTunerOperations p : this.outConnections.values()) {
                    retval = p.getTunerGroupId(id);
                }
            }
        } 
        return retval;
    }
 
    public String getTunerRfFlowId(String id) throws FrontendException, BadParameterException, NotSupportedException {
        String retval = "";

        synchronized(this.updatingPortsLock) {
            if (this.active) {
                
                for (FrontendTunerOperations p : this.outConnections.values()) {
                    retval = p.getTunerRfFlowId(id);
                }
            }
        } 
        
        return retval;
    }
 
    public CF.DataType[] getTunerStatus(String id) throws FrontendException, BadParameterException, NotSupportedException {
        CF.DataType[] retval = null;

        synchronized(this.updatingPortsLock) { 
            if (this.active) {
                for (FrontendTunerOperations p : this.outConnections.values()) {
                    retval = p.getTunerStatus(id);
                }
            }
        }
        return retval;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
 }
