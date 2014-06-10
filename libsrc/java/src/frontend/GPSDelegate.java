package frontend;

import FRONTEND.GPSInfo;
import FRONTEND.GpsTimePos;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface GPSDelegate {

    public GPSInfo get_gps_info(String port_name) throws FrontendException, BadParameterException, NotSupportedException;

    public void set_gps_info(String port_name, GPSInfo data) throws FrontendException, BadParameterException, NotSupportedException;

    public GpsTimePos get_gps_time_pos(String port_name) throws FrontendException, BadParameterException, NotSupportedException;

    public void set_gps_time_pos(String port_name, GpsTimePos data) throws FrontendException, BadParameterException, NotSupportedException;

}
