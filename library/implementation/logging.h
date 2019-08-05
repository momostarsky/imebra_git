/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file logging.h
    \brief Defines the classes and the macros used to handle logging.

*/

#if !defined(CImbxLogging_F1BAF067_21DE_466b_AEA1_6CC4F006FAFA__INCLUDED_)
#define CImbxLogging_F1BAF067_21DE_466b_AEA1_6CC4F006FAFA__INCLUDED_

#include "../include/imebra/definitions.h"
#include <iostream>
#include <sstream>
#include <string>

namespace imebra
{

namespace implementation
{

#if defined(IMEBRA_ANDROID)
#include <android/log.h>

#define IMEBRA_LOG_FATAL_IMPLEMENTATION(message) __android_log_write(ANDROID_LOG_ASSERT, "Imebra", message.c_str());

#define IMEBRA_LOG_ERROR_IMPLEMENTATION(message) __android_log_write(ANDROID_LOG_ERROR, "Imebra", message.c_str());

#define IMEBRA_LOG_WARNING_IMPLEMENTATION(message) __android_log_write(ANDROID_LOG_WARN, "Imebra", message.c_str());

#define IMEBRA_LOG_INFO_IMPLEMENTATION(message) __android_log_write(ANDROID_LOG_INFO, "Imebra", message.c_str());

#define IMEBRA_LOG_DEBUG_IMPLEMENTATION(message) __android_log_write(ANDROID_LOG_DEBUG, "Imebra", message.c_str());

#define IMEBRA_LOG_TRACE_IMPLEMENTATION(message) __android_log_write(ANDROID_LOG_VERBOSE, "Imebra", message.c_str());

#elif defined(__APPLE__)

void appleLog(const std::string& format, const std::string& message);

#define IMEBRA_LOG_FATAL_IMPLEMENTATION(message) imebra::implementation::appleLog("FATAL: %@", message.c_str());

#define IMEBRA_LOG_ERROR_IMPLEMENTATION(message) imebra::implementation::appleLog("ERROR: %@", message.c_str());

#define IMEBRA_LOG_WARNING_IMPLEMENTATION(message) imebra::implementation::appleLog("WARNING: %@", message.c_str());

#define IMEBRA_LOG_INFO_IMPLEMENTATION(message) imebra::implementation::appleLog("INFO: %@", message.c_str());

#define IMEBRA_LOG_DEBUG_IMPLEMENTATION(message) imebra::implementation::appleLog("DEBUG: %@", message.c_str());

#define IMEBRA_LOG_TRACE_IMPLEMENTATION(message) imebra::implementation::appleLog("TRACE: %@", message.c_str());


#elif defined(IMEBRA_POSIX)
#include <syslog.h>

#define IMEBRA_LOG_FATAL_IMPLEMENTATION(message) syslog(LOG_CRIT, "%s", message.c_str());

#define IMEBRA_LOG_ERROR_IMPLEMENTATION(message) syslog(LOG_ERR, "%s", message.c_str());

#define IMEBRA_LOG_WARNING_IMPLEMENTATION(message) syslog(LOG_WARNING, "%s", message.c_str());

#define IMEBRA_LOG_INFO_IMPLEMENTATION(message) syslog(LOG_INFO, "%s", message.c_str());

#define IMEBRA_LOG_DEBUG_IMPLEMENTATION(message) syslog(LOG_DEBUG, "%s", message.c_str());

#define IMEBRA_LOG_TRACE_IMPLEMENTATION(message) syslog(LOG_DEBUG, "%s", message.c_str());


#else


///
/// \brief Returns a string with the current time.
///
/// \return the current time
///
///////////////////////////////////////////////////////////
std::string getCurrentTime();

#define IMEBRA_LOG_FATAL_IMPLEMENTATION(message) std::cout << "Imebra FATAL " << getCurrentTime() << " " << message << std::endl;
#define IMEBRA_LOG_ERROR_IMPLEMENTATION(message) std::cout << "Imebra ERROR " << getCurrentTime() << " " << message << std::endl;
#define IMEBRA_LOG_WARNING_IMPLEMENTATION(message) std::cout << "Imebra WARNING " << getCurrentTime() << " " << message << std::endl;
#define IMEBRA_LOG_INFO_IMPLEMENTATION(message) std::cout << "Imebra INFO " << getCurrentTime() << " " << message << std::endl;
#define IMEBRA_LOG_DEBUG_IMPLEMENTATION(message) std::cout << "Imebra DEBUG " << getCurrentTime() << " " << message << std::endl;
#define IMEBRA_LOG_TRACE_IMPLEMENTATION(message) std::cout << "Imebra TRACE " << getCurrentTime() << " " << message << std::endl;

#endif



} // namespace implementation

} // namespace imebra



// Logging macros used by Imebra functions
//
///////////////////////////////////////////////////////////

#if IMEBRA_LOG_LEVEL >= IMEBRA_LOG_LEVEL_FATAL
#define IMEBRA_LOG_FATAL(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    IMEBRA_LOG_FATAL_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define IMEBRA_LOG_FATAL(message)
#endif

#if IMEBRA_LOG_LEVEL >= IMEBRA_LOG_LEVEL_ERROR
#define IMEBRA_LOG_ERROR(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    IMEBRA_LOG_ERROR_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define IMEBRA_LOG_ERROR(message)
#endif

#if IMEBRA_LOG_LEVEL >= IMEBRA_LOG_LEVEL_WARNING
#define IMEBRA_LOG_WARNING(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    IMEBRA_LOG_WARNING_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define IMEBRA_LOG_WARNING(message)
#endif

#if IMEBRA_LOG_LEVEL >= IMEBRA_LOG_LEVEL_INFO
#define IMEBRA_LOG_INFO(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    IMEBRA_LOG_INFO_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define IMEBRA_LOG_INFO(message)
#endif

#if IMEBRA_LOG_LEVEL >= IMEBRA_LOG_LEVEL_DEBUG
#define IMEBRA_LOG_DEBUG(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    IMEBRA_LOG_DEBUG_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define IMEBRA_LOG_DEBUG(message)
#endif

#if IMEBRA_LOG_LEVEL >= IMEBRA_LOG_LEVEL_TRACE
#define IMEBRA_LOG_TRACE(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    IMEBRA_LOG_TRACE_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define IMEBRA_LOG_TRACE(message)
#endif


#endif // CImbxLogging_F1BAF067_21DE_466b_AEA1_6CC4F006FAFA__INCLUDED_
