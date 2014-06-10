package frontend;

import FRONTEND.FrontendException;
import FRONTEND.BadParameterException;
import FRONTEND.NotSupportedException;

public interface FrontendTunerDelegate {

    public String getTunerType(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public boolean getTunerDeviceControl(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public String getTunerGroupId(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public String getTunerRfFlowId(String id) throws FrontendException, BadParameterException, NotSupportedException;

    public CF.DataType[] getTunerStatus(String id) throws FrontendException, BadParameterException, NotSupportedException;

}
