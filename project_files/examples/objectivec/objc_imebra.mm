/**
 * This is a simple objective-c class that calls some method on the imebra library.
 *
 * The most problematic part is the conversion from NSString to wstring and viceversa.
 *
 * Other data types can be used natively (e.g. int, imbxInt16, double, etc).
 *
 */

#include "../../library/imebra/include/imebra.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>


/**
 * This class calls the C++ methods in imebra.
 *
 */
@interface LoadDicom : NSObject
  puntoexe::ptr<puntoexe::imebra::dataSet> m_dicomDataSet;

/**
 * Load a file. Call this method before the other ones.
 */
- (void) loadFile: (NSString *)fileName;

/**
 * Retrieve a tag as string value.
 */
- (NSString*) getTagString:(imbxUint16)tag forGroup:(imbxUint16) group;

/**
 * Retrieve a tag as an integer value.
 */
- (long) getTagLong:(imbxUint16)tag forGroup:(imbxUint16) group;

/**
 * Retrieve a tag as a double floating point value.
 */
- (double) getTagDouble:(imbxUint16)tag forGroup:(imbxUint16) group;
@end


/**
 * @brief Convert an NSString to a std::wstring accepted by imebra.
 * @param str an NSString
 * @return a std::wstring
 */
std::wstring NSStringToStringW ( NSString* str )
{
    const char* wstr = [str cStringUsingEncoding:NSUTF32LittleEndianStringEncoding];
    if(wstr == 0)
    {
        return L"";
    }
    return std::wstring((wchar_t*)wstr);
}


/**
 * @brief Convert a std::wstring to an NSString.
 * @param str an std::wstring
 * @return a NSString
 */
NSString* StringWToNSString ( const std::wstring& str )
{
    NSString* pString = [[NSString alloc] initWithBytes:str.data()
            length:str.size() * sizeof(wchar_t)
          encoding:NSUTF32LittleEndianStringEncoding];
    return [pString autorelease];
}


@implementation LoadDicom
- (void) loadFile: (NSString *)fileName
{
    // Allocate a stream for the dicom file
    puntoexe::ptr<puntoexe::stream> stream(new puntoexe::stream());

    stream->openFile(NSStringToStringW(fileName), std::ios_base::in);

    // Allocate a reader that will read the stream. Several readers can be connected to the
    //  same stream in different threads
    ///////////////////////////////////////////////////////////////////////////////////////
    puntoexe::ptr<puntoexe::streamReader> reader(new puntoexe::streamReader(stream));

    // Load the Dicom dataset in memory. Tags larger than 2048 bytes will be loaded from
    //  the file only when needed. Therefore m_dicomDataSet will keep the file open until
    //  it goes out of scope (the file is closed automatically).
    /////////////////////////////////////////////////////////////////////////////////////
    m_dicomDataSet = puntoexe::imebra::codecs::codecFactory::getCodecFactory()->load(reader, 2048);
}

- (NSString*) getTagString:(imbxUint16)tag forGroup:(imbxUint16) group
{
    std::wstring tagValue = m_dicomDataSet->getUnicodeString(group, 0, tag, 0);
    return StringWToNSString(tagValue);
}

- (long) getTagLong:(imbxUint16)tag forGroup:(imbxUint16) group
{
    return m_dicomDataSet->getSignedLong(group, 0, tag, 0);
}

- (double) getTagDouble:(imbxUint16)tag forGroup:(imbxUint16) group
{
    return m_dicomDataSet->getDouble(group, 0, tag, 0);
}


@end




