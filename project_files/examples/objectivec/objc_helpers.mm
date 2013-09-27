#import "objc_helpers.h"

std::wstring NSStringToStringW ( NSString* str )
{
    const char* wstr = [str cStringUsingEncoding:NSUTF32LittleEndianStringEncoding];
    if(wstr == 0)
    {
        return L"";
    }
    return std::wstring((wchar_t*)wstr);
}


NSString* StringWToNSString ( const std::wstring& str )
{
    NSString* pString = [[NSString alloc] initWithBytes:str.data()
            length:str.size() * sizeof(wchar_t)
          encoding:NSUTF32LittleEndianStringEncoding];
    return [pString autorelease];
}


