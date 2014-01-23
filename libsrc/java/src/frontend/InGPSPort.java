package frontend;

import FRONTEND.GPSInfo;
import FRONTEND.GpsTimePos;
import org.apache.log4j.Logger;
import frontend.GPSListener;

public class InGPSPort extends FRONTEND.GPSPOA {

    protected String name;
 
    protected Logger logger = null;

    protected Object portAccess = null;

    protected GPSListener gpsListener = null;    

    public InGPSPort( String portName) {
        this( portName, null, null);
    }

    public InGPSPort( String portName,
                         GPSListener listener) {
        this( portName, listener, null);
    }

    public InGPSPort( String portName,
                         GPSListener listener,
                         Logger logger) {
        this.name = portName;
        this.gpsListener = listener;
        this.logger = logger;
        this.portAccess = new Object();
    }

    public GPSInfo gps_info() {
        synchronized(this.portAccess){
            try{
                if ( gpsListener != null ) {
                    return gpsListener.fe_getGPSInfo();
                } else {
                    if (this.logger != null){
                        logger.error("InGPSPort gps_info() callback listener not defined");
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
                if ( gpsListener != null) {
                    gpsListener.fe_setGPSInfo(data);
                } else {
                    if (this.logger != null){
                        logger.error("InGPSPort gps_info(GPSInfo data) callback listener not defined");
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
                if ( gpsListener != null) {
                    return (gpsListener.fe_getGpsTimePos());
                } else {
                    if (this.logger != null){
                        logger.error("InGPSPort gps_time_pos() callback listener not defined");
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
                if ( gpsListener != null) {
                    gpsListener.fe_setGpsTimePos(data);
                } else {
                    if (this.logger != null){
                        logger.error("InGPSPort gps_time_pos(GpsTimePos data) callback listener not defined");
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

    public void setGPSListener( GPSListener newListener ) {
        gpsListener = newListener;
    }

    public void setLogger( Logger newLogger ) {
        logger = newLogger;
    }
}
