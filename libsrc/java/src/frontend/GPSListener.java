package frontend;

import FRONTEND.GPSInfo;
import FRONTEND.GpsTimePos;

public interface GPSListener {

    public GPSInfo getGPSInfo();

    public void setGPSInfo(GPSInfo data);

    public GpsTimePos getGpsTimePos();

    public void setGpsTimePos(GpsTimePos data);

}
