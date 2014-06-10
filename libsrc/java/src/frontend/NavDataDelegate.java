package frontend;

import FRONTEND.NavigationPacket;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface NavDataDelegate {

    public NavigationPacket get_nav_packet(String port_name) throws FrontendException, BadParameterException, NotSupportedException; 

    public void set_nav_packet(String port_name, NavigationPacket data) throws FrontendException, BadParameterException, NotSupportedException;

}
