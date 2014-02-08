#ifndef FE_LOG_H
#define FE_LOG_H

#ifdef LOGGING
#undef LOG_INFO
#undef LOG_ERROR
#undef LOG_WARN
#undef LOG_FATAL
#undef LOG_DEBUG
#undef LOG_TRACE
#undef TRACE_ENTER
#undef TRACE_EXIT

#define LOG_INFO(logger, expr )   if ( logger ) LOG4CXX_INFO(logger, expr );
#define LOG_ERROR(logger, expr )  if ( logger ) LOG4CXX_ERROR(logger, expr );
#define LOG_WARN(logger, expr )  if ( logger ) LOG4CXX_WARN(logger, expr );
#define LOG_FATAL(logger, expr )  if ( logger ) LOG4CXX_FATAL(logger, expr );
#define LOG_DEBUG(logger, expr )  if ( logger ) LOG4CXX_DEBUG(logger, expr );
#define LOG_TRACE(logger, expr )  if ( logger ) LOG4CXX_TRACE(logger, expr );

#ifdef TRACE_ENABLE
#define TRACE_ENTER(logger, method)                                             \
    LOG_TRACE(logger, "ENTER frontend::" << method << " [" << __FILE__ << ":" << __LINE__ << "]")
#define TRACE_EXIT(logger, method)                                              \
    LOG_TRACE(logger, "EXIT frontend::" << method << " [" << __FILE__ << ":" << __LINE__ << "]")
#else
#define TRACE_ENTER(logger, method )
#define TRACE_EXIT(logger, method )
#endif

#else
#define LOG_INFO(logger, expr )  
#define LOG_ERROR(logger, expr ) 
#define LOG_WARN(logger, expr )  
#define LOG_FATAL(logger, expr ) 
#define LOG_DEBUG(logger, expr ) 
#define LOG_TRACE(logger, expr ) 
#define TRACE_ENTER(logger, method )
#define TRACE_EXIT(logger, method )

#endif


#endif
