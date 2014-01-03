package frontend;

import frontend.AnalogTunerListener;

public interface DigitalTunerListener extends AnalogTunerListener {

    public void setTunerOutputSampleRate(String id, double sr);

    public double getTunerOutputSampleRate(String id);
}
