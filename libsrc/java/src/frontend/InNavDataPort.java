package frontend;

import FRONTEND.NavigationPacket;
import frontend.NavDataDelegate;
import org.apache.log4j.Logger;

// ----------------------------------------------------------------------------------------
// InNavDataPort definition
// ----------------------------------------------------------------------------------------
public class InNavDataPort extends FRONTEND.NavDataPOA{

    protected String name;

    protected Logger logger = null; 

    protected Object portAccess = null;

    protected NavDataDelegate delegate = null;

    public InNavDataPort( String portName){
        this( portName, null, null);
    }

    public InNavDataPort( String portName,
                          NavDataDelegate d){
        this( portName, d, null);
    }

    public InNavDataPort( String portName,
                          NavDataDelegate d,
                          Logger logger){
        this.name = portName;
        this.delegate = d;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public NavigationPacket nav_packet() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ) {
                    return delegate.fe_getNavPkt();
                } else {
                    if (this.logger != null){
                        logger.error("InNavDataPort nav_packet() callback delegate not defined");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InNavDataPort nav_packet() exception " + e.getMessage());
                }
                System.out.println("InNavDataPort nav_packet() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void nav_packet(NavigationPacket data){
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    delegate.fe_setNavPkt(data);
                } else {
                    if (this.logger != null){
                        logger.error("InNavDataPort nav_packet(NavigationPacket data) callback delegate not defined");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InNavDataPort nav_packet(NavigationPacket data) exception " + e.getMessage());
                }
                System.out.println("InNavDataPort nav_packet(NavigationPacket data) exception " + e.getMessage());
            }
        }
    }

    public void setDelegate( NavDataDelegate d ) {
        delegate = d;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
