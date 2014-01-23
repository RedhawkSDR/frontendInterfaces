package frontend;

import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface FrontendTunerListener {

    public String fe_getTunerType(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public boolean fe_getTunerDeviceControl(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public String fe_getTunerGroupId(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public String fe_getTunerRfFlowId(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public CF.DataType[] fe_getTunerStatus(String id) throws FrontendException, BadParameterException, NotSupportedException;

}
