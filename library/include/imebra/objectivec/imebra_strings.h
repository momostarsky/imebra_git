#if !defined(imebraObjcStrings__INCLUDED_)
#define imebraObjcStrings__INCLUDED_

#import <Foundation/Foundation.h>
#include <string>
#include "../definitions.h"

/**
 * @brief Convert an NSString to a std::string accepted by imebra.
 * @param str an NSString
 * @return a std::string
 */
IMEBRA_API std::string NSStringToString ( NSString* str );


/**
 * @brief Convert a std::string to an NSString.
 * @param str an std::string
 * @return a NSString
 */
IMEBRA_API NSString* stringToNSString ( const std::string& str );

#endif // imebraObjcStrings__INCLUDED_
