package frontend;

import frontend.FrontendTunerDelegate;
import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface AnalogTunerDelegate extends FrontendTunerDelegate {

    public void fe_setTunerCenterFrequency(String id, double freq) throws FrontendException, BadParameterException, NotSupportedException;

    public double fe_getTunerCenterFrequency(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setTunerBandwidth(String id, double bw) throws FrontendException, BadParameterException, NotSupportedException;

    public double fe_getTunerBandwidth(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setTunerAgcEnable(String id, boolean enable) throws FrontendException, BadParameterException, NotSupportedException;

    public boolean fe_getTunerAgcEnable(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setTunerGain(String id, float gain) throws FrontendException, BadParameterException, NotSupportedException;

    public float fe_getTunerGain(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setTunerReferenceSource(String id, int source) throws FrontendException, BadParameterException, NotSupportedException;

    public int fe_getTunerReferenceSource(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public void fe_setTunerEnable(String id, boolean enable) throws FrontendException, BadParameterException, NotSupportedException;

    public boolean fe_getTunerEnable(String id) throws FrontendException, BadParameterException, NotSupportedException;
}
