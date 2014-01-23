package frontend;

import FRONTEND.NavigationPacket;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface NavDataListener {

    public NavigationPacket fe_getNavPkt() throws FrontendException, BadParameterException, NotSupportedException; 

    public void fe_setNavPkt(NavigationPacket data) throws FrontendException, BadParameterException, NotSupportedException;

}
