package frontend;

import FRONTEND.GpsTimePos;
import FRONTEND.GPSInfo;
import frontend.GPSDelegate;
public class InGPSPort extends FRONTEND.GPSPOA {

    protected String name;
 
    protected Object portAccess = null;

    protected GPSDelegate delegate = null;    

    public InGPSPort( String portName,
                         GPSDelegate d) {
        this.name = portName;
        this.delegate = d;
        this.portAccess = new Object();
    }

    public GPSInfo gps_info() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null ) {
                    return delegate.fe_getGPSInfo();
                }
            }catch(Exception e){
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
                }
            }catch(Exception e){
                System.out.println("InGPSPort gps_info(GPSInfo data) exception " + e.getMessage());
            }
        }
    }

    public GpsTimePos gps_time_pos() {
        synchronized(this.portAccess){
            try{
                if ( delegate != null) {
                    return (delegate.fe_getGpsTimePos());
                }
            }catch(Exception e){
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
                }
            }catch(Exception e){
                System.out.println("InGPSPort gps_time_pos(GpsTimePos data) exception " + e.getMessage());
            }
        }
    }

    public void setDelegate( GPSDelegate d ) {
        delegate = d;
    }
}
