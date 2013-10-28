#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include "../../library/imebra/include/imebra.h"

#import "objc_image.h"

/**
 * This class calls the C++ methods in imebra.
 *
 */
@interface ImebraDataSet : NSObject
  puntoexe::ptr<puntoexe::imebra::dataSet> m_dataSet;

- initWithDataSet: (puntoexe::ptr<puntoexe::imebra::dataSet>) dataSet;

/**
 * Load a file. Call this method before the other ones.
 */
- (void) loadFile: (NSString *)fileName;
- (void) loadFile: (NSString *)fileName withMaximumSize:(imbxUint32)maxSize;

/**
 * Retrieve a tag as string value.
 */
- (NSString*) getStringFromGroup:(imbxUint16)group inTag:(imbxUint16)tag inPosition:(imbxUint32)position;
- (NSString*) getStringFromGroup:(imbxUint16)group inTag:(imbxUint16)tag;


/**
 * Retrieve a tag as an integer value.
 */
- (long) getLongFromGroup:(imbxUint16)group inTag:(imbxUint16) tag inPosition:(imbxUint32)position;
- (long) getLongFromGroup:(imbxUint16)group inTag:(imbxUint16) tag;

/**
 * Retrieve a tag as a double floating point value.
 */
- (double) getDoubleFromGroup:(imbxUint16)group inTag:(imbxUint16) tag inPosition:(imbxUint32)position;
- (double) getDoubleFromGroup:(imbxUint16)group inTag:(imbxUint16) tag;

/**
 * Retrieve a sequence item
 */
- (ImebraDataSet*) getSequenceFromGroup:(imbxUint16)group inTag:(imbxUint16)tag inPosition:(imbxUint32)position;


- (ImebraImage*) getImage:(imbxUint32)frameNumber;
- (ImebraImage*) getModalityImage:(imbxUint32)frameNumber;
@end

