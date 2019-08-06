#if defined(__APPLE__)

#include "logging.h"
#import <Foundation/Foundation.h>

namespace imebra
{

namespace implementation
{

void appleLog(const std::string& format, const std::string& message)
{
    ::NSLog([[ NSString alloc] initWithUTF8String: format.c_str()], [[ NSString alloc] initWithUTF8String: message.c_str()]);
}

}

}

#endif
