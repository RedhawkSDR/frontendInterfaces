package frontend;

import java.util.HashMap;
import java.util.Map;
import org.ossie.component.QueryableUsesPort;
import FRONTEND.GPSOperations;
import FRONTEND.GPSHelper;
import FRONTEND.GPSInfo;
import FRONTEND.GpsTimePos;


public class OutGPSPort extends QueryableUsesPort<GPSOperations> implements GPSOperations {

    protected String name;
 
    protected Object updatingPortsLock;

    /**
     * Map of connection Ids to port objects
     */
    protected Map<String, GPSOperations> outConnections = new HashMap<String, GPSOperations>();

    public OutGPSPort( String portName) {
        super(portName);
        this.name = portName;
        this.outConnections = new HashMap<String, GPSOperations>();
    }

    protected GPSOperations narrow(org.omg.CORBA.Object connection)
    {
        GPSOperations ops = GPSHelper.narrow(connection);
        return ops;
    }

    public void connectPort(final org.omg.CORBA.Object connection, final String connectionId) throws CF.PortPackage.InvalidPort, CF.PortPackage.OccupiedPort
    {
        try {
            synchronized (this.updatingPortsLock) {
                super.connectPort(connection, connectionId);
                final GPSOperations port = GPSHelper.narrow(connection);
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

    public GPSInfo gps_info()
    {
        GPSInfo retval = null;

        synchronized(updatingPortsLock){
            if (this.active) {
                for (GPSOperations p : this.outConnections.values()) {
                    retval = p.gps_info();
                }
            }
        }
        return retval;
    }

    public void gps_info(GPSInfo data)
    {
        synchronized(updatingPortsLock){
            if (this.active) {
                for (GPSOperations p : this.outConnections.values()) {
                    p.gps_info(data);
                }
            }
        }
    }

    public GpsTimePos gps_time_pos()
    {
        GpsTimePos retval = null;

        synchronized(this.updatingPortsLock) { 
            if (this.active) {
                for (GPSOperations p : this.outConnections.values()) {
                    retval = p.gps_time_pos();
                }
            }
        }
        return retval;
    }

    public void gps_time_pos(GpsTimePos data)
    {
        synchronized(this.updatingPortsLock) {
            if (this.active) {
                for (GPSOperations p : this.outConnections.values()) {
                    p.gps_time_pos(data);
                }
            }
        }
    }
}

