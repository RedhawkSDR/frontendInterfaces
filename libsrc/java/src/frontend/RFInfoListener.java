package frontend;

import FRONTEND.RFInfoPkt;

public interface RFInfoListener {

    public String getRFFlowId();

    public void setRFFlowId(String data);

    public RFInfoPkt getRFInfoPkt();

    public void setRFInfoPkt(RFInfoPkt data);

}
