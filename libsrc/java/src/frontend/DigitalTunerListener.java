package frontend;

import frontend.AnalogTunerListener;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface DigitalTunerListener extends AnalogTunerListener {

    public void fe_setTunerOutputSampleRate(String id, double sr) throws FrontendException, BadParameterException, NotSupportedException;

    public double fe_getTunerOutputSampleRate(String id) throws FrontendException, BadParameterException, NotSupportedException;
}
