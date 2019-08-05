#include <imebra/logging.h>
#include <array>
#include <ctime>
#include "imebra_strings.h"

namespace imebra
{

namespace implementation
{

void appleLog(const std::string& format, const std::string& message)
{
    NSLog([[ NSString alloc] initWithUTF8String: format.c_str()], [[ NSString alloc] initWithUTF8String: message.c_str()]);
}

}


}
