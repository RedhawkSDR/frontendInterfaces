package frontend;

import FRONTEND.NavigationPacket;
import frontend.NavDataDelegate;

// ----------------------------------------------------------------------------------------
// InNavDataPort definition
// ----------------------------------------------------------------------------------------
public class InNavDataPort extends FRONTEND.NavDataPOA{

    protected String name;

    protected Object portAccess = null;

    protected NavDataDelegate delegate = null;

    public InNavDataPort( String portName) {
        this(portName, null);
    }

    public InNavDataPort( String portName,
                          NavDataDelegate d){
        this.name = portName;
        this.delegate = d;
        this.portAccess = new Object();
    }

    public NavigationPacket nav_packet() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ) {
                    return delegate.get_nav_packet(this.name);
                }
            }catch(Exception e){
                System.out.println("InNavDataPort nav_packet() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void nav_packet(NavigationPacket data){
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    delegate.set_nav_packet(this.name, data);
                }
            }catch(Exception e){
                System.out.println("InNavDataPort nav_packet(NavigationPacket data) exception " + e.getMessage());
            }
        }
    }

    public void setDelegate( NavDataDelegate d ) {
        delegate = d;
    }
}
