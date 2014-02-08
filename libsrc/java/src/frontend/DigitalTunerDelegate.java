package frontend;

import frontend.AnalogTunerDelegate;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface DigitalTunerDelegate extends AnalogTunerDelegate {

    public void fe_setTunerOutputSampleRate(String id, double sr) throws FrontendException, BadParameterException, NotSupportedException;

    public double fe_getTunerOutputSampleRate(String id) throws FrontendException, BadParameterException, NotSupportedException;
}
