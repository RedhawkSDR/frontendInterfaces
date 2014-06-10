package frontend;

import FRONTEND.RFInfoPkt;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface RFInfoDelegate {

    public String get_rf_flow_id(String port_name) throws FrontendException, BadParameterException, NotSupportedException;

    public void set_rf_flow_id(String port_name, String data) throws FrontendException, BadParameterException, NotSupportedException;

    public RFInfoPkt get_rfinfo_pkt(String port_name) throws FrontendException, BadParameterException, NotSupportedException;

    public void set_rfinfo_pkt(String port_name, RFInfoPkt data) throws FrontendException, BadParameterException, NotSupportedException;

}
