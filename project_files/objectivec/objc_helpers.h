#import <Foundation/Foundation.h>
#include <string>

/**
 * @brief Convert an NSString to a std::wstring accepted by imebra.
 * @param str an NSString
 * @return a std::wstring
 */
std::wstring NSStringToStringW ( NSString* str );


/**
 * @brief Convert a std::wstring to an NSString.
 * @param str an std::wstring
 * @return a NSString
 */
NSString* StringWToNSString ( const std::wstring& str );
