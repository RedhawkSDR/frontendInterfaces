package frontend;

import FRONTEND.RFInfoPkt;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface RFInfoDelegate {

    public String fe_getRFFlowId() throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setRFFlowId(String data) throws FrontendException, BadParameterException, NotSupportedException;

    public RFInfoPkt fe_getRFInfoPkt() throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setRFInfoPkt(RFInfoPkt data) throws FrontendException, BadParameterException, NotSupportedException;

}
