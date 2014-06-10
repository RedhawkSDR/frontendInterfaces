package frontend;

import frontend.FrontendTunerDelegate;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface AnalogTunerDelegate extends FrontendTunerDelegate {

    public void setTunerCenterFrequency(String id, double freq) throws FrontendException, BadParameterException, NotSupportedException;

    public double getTunerCenterFrequency(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void setTunerBandwidth(String id, double bw) throws FrontendException, BadParameterException, NotSupportedException;

    public double getTunerBandwidth(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void setTunerAgcEnable(String id, boolean enable) throws FrontendException, BadParameterException, NotSupportedException;

    public boolean getTunerAgcEnable(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void setTunerGain(String id, float gain) throws FrontendException, BadParameterException, NotSupportedException;

    public float getTunerGain(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void setTunerReferenceSource(String id, int source) throws FrontendException, BadParameterException, NotSupportedException;

    public int getTunerReferenceSource(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void setTunerEnable(String id, boolean enable) throws FrontendException, BadParameterException, NotSupportedException;

    public boolean getTunerEnable(String id) throws FrontendException, BadParameterException, NotSupportedException;
}
