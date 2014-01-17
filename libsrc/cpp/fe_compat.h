#ifndef __frontend_compat_h
#define __frontend_compat_h

//
// Compatibility aliases mapping FRONTEND base classes to legacy generated class
// names. This header should only be included in projects that are migrating to
// FRONTEND base classes from pre-1.9.1 code generators.
//
// For forward-compatibility with future releases, references to the old names
// should be replaced with the corresponding base class.
//

#warning "This project uses deprecated interfaces; FRONTEND class references should be updated to frontend namespace"

#include "frontend.h"

typedef frontend::InFrontendTunerPort   FRONTEND_FrontendTuner_In_i;
typedef frontend::InAnalogTunerPort     FRONTEND_AnalogTuner_In_i;
typedef frontend::InDigitalTunerPort    FRONTEND_DigitalTuner_In_i;
typedef frontend::InGPSPort             FRONTEND_GPS_In_i;
typedef frontend::InRFInfoPort          FRONTEND_RFInfo_In_i;
typedef frontend::InRFSourcePort        FRONTEND_RFSource_In_i;
typedef frontend::InNavDataPort         FRONTEND_NavData_In_i;

typedef frontend::OutFrontendTunerPort   FRONTEND_FrontendTuner_Out_i;
typedef frontend::OutAnalogTunerPort     FRONTEND_AnalogTuner_Out_i;
typedef frontend::OutDigitalTunerPort    FRONTEND_DigitalTuner_Out_i;
typedef frontend::OutGPSPort             FRONTEND_GPS_Out_i;
typedef frontend::OutRFInfoPort          FRONTEND_RFInfo_Out_i;
typedef frontend::OutRFSourcePort        FRONTEND_RFSource_Out_i;
typedef frontend::OutNavDataPort         FRONTEND_NavData_Out_i;

#endif
