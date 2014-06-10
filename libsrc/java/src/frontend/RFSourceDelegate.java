package frontend;

import FRONTEND.RFInfoPkt;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface RFSourceDelegate {

    public RFInfoPkt[] get_available_rf_inputs(String port_name) throws FrontendException, BadParameterException, NotSupportedException;

    public void set_available_rf_inputs(String port_name, RFInfoPkt[] data) throws FrontendException, BadParameterException, NotSupportedException;

    public RFInfoPkt get_current_rf_input(String port_name) throws FrontendException, BadParameterException, NotSupportedException;

    public void set_current_rf_input(String port_name, RFInfoPkt data) throws FrontendException, BadParameterException, NotSupportedException;

}
