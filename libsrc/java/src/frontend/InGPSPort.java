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
            if ( gpsListener != null ) {
                return gpsListener.getGPSInfo();
            } else {
                if (this.logger != null){
                    logger.error("InGPSPort gps_info() callback listener not defined");
                }
                return null;
            }
        }
    }

    public void gps_info(GPSInfo data) {
        synchronized(this.portAccess){
            if ( gpsListener != null) {
                gpsListener.setGPSInfo(data);
            } else {
                if (this.logger != null){
                    logger.error("InGPSPort gps_info(GPSInfo data) callback listener not defined");
                }
            }
        }
    }

    public GpsTimePos gps_time_pos() {
        synchronized(this.portAccess){
            if ( gpsListener != null) {
                return (gpsListener.getGpsTimePos());
            } else {
                if (this.logger != null){
                    logger.error("InGPSPort gps_time_pos() callback listener not defined");
                }
                return null;
            }
        }
    }

    public void gps_time_pos(GpsTimePos data) {
        synchronized(this.portAccess){
            if ( gpsListener != null) {
                gpsListener.setGpsTimePos(data);
            } else {
                if (this.logger != null){
                    logger.error("InGPSPort gps_time_pos(GpsTimePos data) callback listener not defined");
                }
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
