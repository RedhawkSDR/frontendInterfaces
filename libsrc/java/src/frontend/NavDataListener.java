package frontend;

import FRONTEND.NavigationPacket;

public interface NavDataListener {

    public NavigationPacket getNavPkt();

    public void setNavPkt(NavigationPacket data);

}
