package frontend;

import org.apache.log4j.Logger;
import java.util.HashMap;
import java.util.Map;
import org.ossie.component.QueryableUsesPort;
import FRONTEND.NavDataOperations;
import FRONTEND.NavDataHelper;
import FRONTEND.NavigationPacket;


public class OutNavDataPort extends QueryableUsesPort<NavDataOperations> implements NavDataOperations {

    protected String name;
 
    protected Logger logger = null;

    protected Object updatingPortsLock;

    /**
     * Map of connection Ids to port objects
     */
    protected Map<String, NavDataOperations> outConnections = new HashMap<String, NavDataOperations>();

    public OutNavDataPort( String portName) {
        this( portName, null);
    }

    public OutNavDataPort( String portName,
                         Logger logger) {
        super(portName);
        this.name = portName;
        this.logger = logger;
        this.outConnections = new HashMap<String, NavDataOperations>();
    }

    protected NavDataOperations narrow(org.omg.CORBA.Object connection)
    {
        NavDataOperations ops = NavDataHelper.narrow(connection);
        return ops;
    }

    public void connectPort(final org.omg.CORBA.Object connection, final String connectionId) throws CF.PortPackage.InvalidPort, CF.PortPackage.OccupiedPort
    {
        try {
            synchronized (this.updatingPortsLock) {
                super.connectPort(connection, connectionId);
                final NavDataOperations port = NavDataHelper.narrow(connection);
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

    public NavigationPacket nav_packet()
    {
        NavigationPacket retval = null;

        synchronized(updatingPortsLock){
            if (this.active) {
                for (NavDataOperations p : this.outConnections.values()) {
                    retval = p.nav_packet();
                }
            }
        }
        return retval;
    }

    public void nav_packet(NavigationPacket data)
    {
        synchronized(updatingPortsLock){
            if (this.active) {
                for (NavDataOperations p : this.outConnections.values()) {
                    p.nav_packet(data);
                }
            }
        }
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}

