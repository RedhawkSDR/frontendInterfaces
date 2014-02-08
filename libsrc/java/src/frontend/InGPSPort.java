package frontend;

import FRONTEND.GpsTimePos;
import FRONTEND.GPSInfo;
import frontend.GPSDelegate;
import org.apache.log4j.Logger;

public class InGPSPort extends FRONTEND.GPSPOA {

    protected String name;
 
    protected Logger logger = null;

    protected Object portAccess = null;

    protected GPSDelegate delegate = null;    

    public InGPSPort( String portName) {
        this( portName, null, null);
    }

    public InGPSPort( String portName,
                         GPSDelegate d) {
        this( portName, d, null);
    }

    public InGPSPort( String portName,
                         GPSDelegate d,
                         Logger logger) {
        this.name = portName;
        this.delegate = d;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public GPSInfo gps_info() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ) {
                    return delegate.fe_getGPSInfo();
                } else {
                    if (this.logger != null){
                        logger.error("InGPSPort gps_info() callback delegate not defined");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InGPSPort gps_info() exception " + e.getMessage());
                }
                System.out.println("InGPSPort gps_info() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void gps_info(GPSInfo data) {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    delegate.fe_setGPSInfo(data);
                } else {
                    if (this.logger != null){
                        logger.error("InGPSPort gps_info(GPSInfo data) callback delegate not defined");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InGPSPort gps_info(GPSInfo data) exception " + e.getMessage());
                }
                System.out.println("InGPSPort gps_info(GPSInfo data) exception " + e.getMessage());
            }
        }
    }

    public GpsTimePos gps_time_pos() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    return (delegate.fe_getGpsTimePos());
                } else {
                    if (this.logger != null){
                        logger.error("InGPSPort gps_time_pos() callback delegate not defined");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InGPSPort gps_time_pos() exception " + e.getMessage());
                }
                System.out.println("InGPSPort gps_time_pos() exception " + e.getMessage());
            }
            return null;
        }
    }

    public void gps_time_pos(GpsTimePos data) {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    delegate.fe_setGpsTimePos(data);
                } else {
                    if (this.logger != null){
                        logger.error("InGPSPort gps_time_pos(GpsTimePos data) callback delegate not defined");
                    }
                }
            }catch(Exception e){
                if (this.logger != null){
                    logger.error("InGPSPort gps_time_pos(GpsTimePos data) exception " + e.getMessage());
                }
                System.out.println("InGPSPort gps_time_pos(GpsTimePos data) exception " + e.getMessage());
            }
        }
    }

    public void setDelegate( GPSDelegate d ) {
        delegate = d;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
