package frontend;

import FRONTEND.GPSInfo;
import FRONTEND.GpsTimePos;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface GPSDelegate {

    public GPSInfo fe_getGPSInfo() throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setGPSInfo(GPSInfo data) throws FrontendException, BadParameterException, NotSupportedException;

    public GpsTimePos fe_getGpsTimePos() throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setGpsTimePos(GpsTimePos data) throws FrontendException, BadParameterException, NotSupportedException;

}
