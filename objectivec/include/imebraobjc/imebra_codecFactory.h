/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcCodecFactory__INCLUDED_)
#define imebraObjcCodecFactory__INCLUDED_

#import <Foundation/Foundation.h>

@class ImebraDataSet;
@class ImebraStreamReader;
@class ImebraStreamWriter;

typedef NS_ENUM(unsigned short, ImebraCodecType_t)
{
    ImebraCodecTypeDicom = 0, ///< DICOM codec
    ImebraCodecTypeJpeg  = 1  ///< JPEG codec
};

///
/// \brief The ImebraCodecFactory class can load or save a DataSet or an Image
///        object using one of the codecs supplied by the Imebra library.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraCodecFactory: NSObject


    /// \brief Parses the content of the input file and returns a ImebraDataSet
    ///        representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the file's
    /// content then set the NSError and returns nil
    ///
    /// \param fileName          the name of the input file
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return a ImebraDataSet object representing the input file's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(ImebraDataSet*)loadFromFile:(NSString*)fileName error:(NSError**)pError;

    +(ImebraDataSet*)loadFromFileMaxSize:(NSString*)fileName maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError;

    +(ImebraDataSet*)loadFromStream:(ImebraStreamReader*)pReader error:(NSError**)pError;

    +(ImebraDataSet*)loadFromStreamMaxSize:(ImebraStreamReader*)pReader maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError;

    +(void)saveToFile:(NSString*)fileName dataSet:(ImebraDataSet*) pDataSet codecType:(ImebraCodecType_t) codecType error:(NSError**)pError;

    +(void)saveToStream:(ImebraStreamWriter*)pWriter dataSet:(ImebraDataSet*)pDataSet codecType:(ImebraCodecType_t) codecType error:(NSError**)pError;

    +(void)setMaximumImageSize:(unsigned int)maximumWidth maxHeight:(unsigned int)maximumHeight;

@end

#endif // imebraObjcCodecFactory__INCLUDED_


