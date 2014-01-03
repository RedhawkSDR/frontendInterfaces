package frontend;

public interface FrontendTunerListener {

    public String getTunerType(String id);

    public boolean getTunerDeviceControl(String id);

    public String getTunerGroupId(String id);

    public String getTunerRfFlowId(String id);

    public CF.DataType[] getTunerStatus(String id);

}
