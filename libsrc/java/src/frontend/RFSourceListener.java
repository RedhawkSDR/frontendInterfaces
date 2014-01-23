package frontend;

import FRONTEND.RFInfoPkt;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface RFSourceListener {

    public RFInfoPkt[] fe_getAvailableRFInputs() throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setAvailableRFInputs(RFInfoPkt[] data) throws FrontendException, BadParameterException, NotSupportedException;

    public RFInfoPkt fe_getCurrentRFInput() throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setCurrentRFInput(RFInfoPkt data) throws FrontendException, BadParameterException, NotSupportedException;

}
