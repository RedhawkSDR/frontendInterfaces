package frontend;

import frontend.FrontendTunerListener;

public interface AnalogTunerListener extends FrontendTunerListener {

    public void setTunerCenterFrequency(String id, double freq);

    public double getTunerCenterFrequency(String id);

    public void setTunerBandwidth(String id, double bw);

    public double getTunerBandwidth(String id);

    public void setTunerAgcEnable(String id, boolean enable);

    public boolean getTunerAgcEnable(String id);

    public void setTunerGain(String id, float gain);

    public float getTunerGain(String id);

    public void setTunerReferenceSource(String id, int source);

    public int getTunerReferenceSource(String id);

    public void setTunerEnable(String id, boolean enable);

    public boolean getTunerEnable(String id);
}
