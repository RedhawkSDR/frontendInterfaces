package frontend;

import FRONTEND.NavigationPacket;
import frontend.NavDataListener;
import org.apache.log4j.Logger;

// ----------------------------------------------------------------------------------------
// InNavDataPort definition
// ----------------------------------------------------------------------------------------
public class InNavDataPort extends FRONTEND.NavDataPOA{

    protected String name;

    protected Logger logger = null; 

    protected Object portAccess = null;

    protected NavDataListener navDataListener = null;

    public InNavDataPort( String portName){
        this( portName, null, null);
    }

    public InNavDataPort( String portName,
                          NavDataListener listener){
        this( portName, listener, null);
    }

    public InNavDataPort( String portName,
                          NavDataListener listener,
                          Logger logger){
        this.name = portName;
        this.navDataListener = listener;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public NavigationPacket nav_packet() {
        synchronized(this.portAccess){
            try{
                if ( navDataListener != null ) {
                    return navDataListener.fe_getNavPkt();
                } else {
                    if (this.logger != null){
                        logger.error("InNavDataPort nav_packet() callback listener not defined");
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
                if ( navDataListener != null) {
                    navDataListener.fe_setNavPkt(data);
                } else {
                    if (this.logger != null){
                        logger.error("InNavDataPort nav_packet(NavigationPacket data) callback listener not defined");
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

    public void setNavDataListener( NavDataListener newListener ) {
        navDataListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
