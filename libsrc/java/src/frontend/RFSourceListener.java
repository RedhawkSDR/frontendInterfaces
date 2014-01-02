package frontend;

import FRONTEND.RFInfoPkt;

public interface RFSourceListener {

    public RFInfoPkt[] getAvailableRFInputs();

    public void setAvailableRFInputs(RFInfoPkt[] data);

    public RFInfoPkt getCurrentRFInput();

    public void setCurrentRFInput(RFInfoPkt data);

}
