
#include "fe_rfsource_port_impl.h"
#include "fe_log.h"

namespace frontend {

	// ----------------------------------------------------------------------------------------
	// InRFSourcePort definition
	// ----------------------------------------------------------------------------------------
	InRFSourcePort::InRFSourcePort(std::string port_name,
                LOGGER_PTR logger,
    		RFInfoPktSeqFromVoid *newAvailableRFInputsGetterCB,
    		RFInfoPktFromVoid *newCurrentRFInputGetterCB,
    		VoidFromRFInfoPktSeq *newAvailableRFInputsSetterCB,
    		VoidFromRFInfoPkt *newCurrentRFInputSetterCB) :
	Port_Provides_base_impl(port_name),
        logger(logger),
	getAvailableRFInputsCB(),
	getCurrentRFInputCB(),
	setAvailableRFInputsCB(),
	setCurrentRFInputCB()
	{
		if ( newAvailableRFInputsGetterCB ) {
			getAvailableRFInputsCB = boost::shared_ptr< RFInfoPktSeqFromVoid >( newAvailableRFInputsGetterCB, null_deleter());
		}
		if ( newCurrentRFInputGetterCB ) {
			getCurrentRFInputCB = boost::shared_ptr< RFInfoPktFromVoid >( newCurrentRFInputGetterCB, null_deleter());
		}
		if ( newAvailableRFInputsSetterCB ) {
			setAvailableRFInputsCB = boost::shared_ptr< VoidFromRFInfoPktSeq >( newAvailableRFInputsSetterCB, null_deleter());
		}
		if ( newCurrentRFInputSetterCB ) {
			setCurrentRFInputCB = boost::shared_ptr< VoidFromRFInfoPkt >( newCurrentRFInputSetterCB, null_deleter());
		}
	}

	InRFSourcePort::~InRFSourcePort()
	{
	}

	void InRFSourcePort::setLogger(LOGGER_PTR newLogger)
        {
            logger = newLogger;
        }

    FRONTEND::RFInfoPktSequence* InRFSourcePort::available_rf_inputs()
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getAvailableRFInputsCB ) return (*getAvailableRFInputsCB)();
		else throw FRONTEND::NotSupportedException("available_rf_inputs() IS NOT CURRENTLY SUPPORTED");
	}

	void InRFSourcePort::available_rf_inputs(const FRONTEND::RFInfoPktSequence& data)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setAvailableRFInputsCB ) (*setAvailableRFInputsCB)(data);
		else throw FRONTEND::NotSupportedException("available_rf_inputs(const FRONTEND::RFInfoPktSequence& data) IS NOT CURRENTLY SUPPORTED");
	}

	FRONTEND::RFInfoPkt* InRFSourcePort::current_rf_input()
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( getCurrentRFInputCB ) return (*getCurrentRFInputCB)();
		else throw FRONTEND::NotSupportedException("current_rf_input() IS NOT CURRENTLY SUPPORTED");
	}

	void InRFSourcePort::current_rf_input(const FRONTEND::RFInfoPkt& data)
	{
		boost::mutex::scoped_lock lock(portAccess);
		if ( setCurrentRFInputCB ) (*setCurrentRFInputCB)(data);
		else throw FRONTEND::NotSupportedException("current_rf_input(const ::FRONTEND::RFInfoPkt& data) IS NOT CURRENTLY SUPPORTED");
	}

	//getAvailableRFInputsCB
	void   InRFSourcePort::setAvailableRFInputsGetterCB( RFInfoPktSeqFromVoid *newCB ){
		getAvailableRFInputsCB =  boost::shared_ptr< RFInfoPktSeqFromVoid >(newCB, null_deleter());
	}
	void   InRFSourcePort::setAvailableRFInputsGetterCB( RFInfoPktSeqFromVoidFn  newCB ){
		getAvailableRFInputsCB =  boost::make_shared< StaticRFInfoPktSeqFromVoid >( newCB );
	}

	//setAvailableRFInputsCB
	void   InRFSourcePort::setAvailableRFInputsSetterCB( VoidFromRFInfoPktSeq *newCB ){
		setAvailableRFInputsCB =  boost::shared_ptr< VoidFromRFInfoPktSeq >(newCB, null_deleter());
	}
	void   InRFSourcePort::setAvailableRFInputsSetterCB( VoidFromRFInfoPktSeqFn  newCB ){
		setAvailableRFInputsCB =  boost::make_shared< StaticVoidFromRFInfoPktSeq >( newCB );
	}

	//getCurrentRFInputCB
	void   InRFSourcePort::setCurrentRFInputGetterCB( RFInfoPktFromVoid *newCB ){
		getCurrentRFInputCB =  boost::shared_ptr< RFInfoPktFromVoid >(newCB, null_deleter());
	}
	void   InRFSourcePort::setCurrentRFInputGetterCB( RFInfoPktFromVoidFn  newCB ){
		getCurrentRFInputCB =  boost::make_shared< StaticRFInfoPktFromVoid >( newCB );
	}

	//setCurrentRFInputCB
	void   InRFSourcePort::setCurrentRFInputSetterCB( VoidFromRFInfoPkt *newCB ){
		setCurrentRFInputCB =  boost::shared_ptr< VoidFromRFInfoPkt >(newCB, null_deleter());
	}
	void   InRFSourcePort::setCurrentRFInputSetterCB( VoidFromRFInfoPktFn  newCB ){
		setCurrentRFInputCB =  boost::make_shared< StaticVoidFromRFInfoPkt >( newCB );
	}

	// ----------------------------------------------------------------------------------------
	// OutRFSourcePort definition
	// ----------------------------------------------------------------------------------------
	OutRFSourcePort::OutRFSourcePort(std::string port_name,
                                         LOGGER_PTR logger) :
		OutFrontendPort<FRONTEND::RFSource_var,FRONTEND::RFSource>::OutFrontendPort(port_name,
                                                                                            logger)
	{
	}

	OutRFSourcePort::~OutRFSourcePort()
	{
	}

	FRONTEND::RFInfoPktSequence* OutRFSourcePort::available_rf_inputs()
	{
		FRONTEND::RFInfoPktSequence* retval;
		std::vector < std::pair < FRONTEND::RFSource_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					retval = ((*i).first)->available_rf_inputs();
				} catch(...) {
					//LOG_ERROR(InRFSourcePort,"Call to available_rf_inputs by InRFSourcePort failed");
				}
			}
		}

		return retval;
	}

	void OutRFSourcePort::available_rf_inputs(const FRONTEND::RFInfoPktSequence& data)
	{
		std::vector < std::pair < FRONTEND::RFSource_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					((*i).first)->available_rf_inputs(data);
				} catch(...) {
					//LOG_ERROR(InRFSourcePort,"Call to available_rf_inputs by InRFSourcePort failed");
				}
			}
		}

		return;
	}

	FRONTEND::RFInfoPkt* OutRFSourcePort::current_rf_input()
	{
		FRONTEND::RFInfoPkt* retval;
		std::vector < std::pair < FRONTEND::RFSource_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					retval = ((*i).first)->current_rf_input();
				} catch(...) {
					//LOG_ERROR(InRFSourcePort,"Call to current_rf_input by InRFSourcePort failed");
				}
			}
		}

		return retval;
	}

	void OutRFSourcePort::current_rf_input(const FRONTEND::RFInfoPkt& data)
	{
		std::vector < std::pair < FRONTEND::RFSource_var, std::string > >::iterator i;

		boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

		if (active) {
			for (i = outConnections.begin(); i != outConnections.end(); ++i) {
				try {
					((*i).first)->current_rf_input(data);
				} catch(...) {
					//LOG_ERROR(InRFSourcePort,"Call to current_rf_input by InRFSourcePort failed");
				}
			}
		}

		return;
	}
} // end of frontend namespace
