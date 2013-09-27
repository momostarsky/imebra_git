/**
 * This is a simple objective-c class that calls some method on the imebra library.
 *
 * The most problematic part is the conversion from NSString to wstring and viceversa.
 *
 * Other data types can be used natively (e.g. int, imbxInt16, double, etc).
 *
 */

#include "../../library/imebra/include/imebra.h"
#import "objc_dataset.h"
#import "objc_image.h"
#import "objc_helpers.h"

@implementation ImebraDataSet

- initWithDataSet: (puntoexe::ptr<puntoexe::imebra::dataSet>) dataSet
{
    [super init];
    if(self != 0)
    {
        m_dataSet = dataSet;
    }
    return self;
}

- (void) loadFile: (NSString *)fileName
{
    return [self loadFile:fileName withMaximumSize:0xffffffff];
}

- (void) loadFile: (NSString *)fileName withMaximumSize:(imbxUint32)maxSize
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
    m_dataSet = puntoexe::imebra::codecs::codecFactory::getCodecFactory()->load(reader, maxSize);
}

- (NSString*) getStringFromGroup:(imbxUint16)group inTag:(imbxUint16)tag
{
    return [self getStringFromGroup:group inTag:tag inPosition:0];
}


- (NSString*) getStringFromGroup:(imbxUint16)group inTag:(imbxUint16)tag inPosition:(imbxUint32)position
{
    std::wstring tagValue = m_dataSet->getUnicodeString(group, 0, tag, position);
    return StringWToNSString(tagValue);
}


- (long) getLongFromGroup:(imbxUint16)group inTag:(imbxUint16) tag
{
    return [self getLongFromGroup:group inTag:tag inPosition:0];
}

- (long) getLongFromGroup:(imbxUint16)group inTag:(imbxUint16) tag inPosition:(imbxUint32)position
{
    return m_dataSet->getSignedLong(group, 0, tag, position);
}

- (double) getDoubleFromGroup:(imbxUint16)group inTag:(imbxUint16)tag
{
    return [self getDoubleFromGroup:group inTag:tag inPosition:0];
}

- (double) getDoubleFromGroup:(imbxUint16)group inTag:(imbxUint16) tag inPosition:(imbxUint32)position
{
    return m_dataSet->getDouble(group, 0, tag, position);
}

- (ImebraDataSet*) getSequenceFromGroup:(imbxUint16)group inTag:(imbxUint16)tag inPosition:(imbxUint32)position
{
    puntoexe::ptr<puntoexe::imebra::dataSet> dataSet = m_dataSet->getSequenceItem(group, 0, tag, position);

    ImebraDataSet* newDataSet = [[ImebraDataSet alloc] initWithDataSet:dataSet];
    return [newDataSet autorelease];
}


- (ImebraImage*) getImage:(imbxUint32)frameNumber
{
    puntoexe::ptr<puntoexe::imebra::image> image = m_dataSet->getImage(frameNumber);
    if(image == 0)
    {
        return [[NSImage new] autorelease];
    }
    return [[[ImebraImage alloc] initWithImebraImage:image] autorelease];
}


@end
