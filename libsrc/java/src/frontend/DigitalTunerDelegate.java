package frontend;

import frontend.AnalogTunerDelegate;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface DigitalTunerDelegate extends AnalogTunerDelegate {

    public void setTunerOutputSampleRate(String id, double sr) throws FrontendException, BadParameterException, NotSupportedException;

    public double getTunerOutputSampleRate(String id) throws FrontendException, BadParameterException, NotSupportedException;
}
