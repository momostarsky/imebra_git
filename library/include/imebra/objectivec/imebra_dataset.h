/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcDataSet__INCLUDED_)
#define imebraObjcDataSet__INCLUDED_

#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
    class DataSet;
}
#endif

@class ImebraImage;
@class ImebraAge;
@class ImebraDate;
@class ImebraReadingDataHandler;
@class ImebraWritingDataHandler;
@class ImebraTagId;

typedef NS_ENUM(unsigned short, ImebraTagVR_t)
{
    ImebraAE = 0x4145, ///< Application Entity
    ImebraAS = 0x4153, ///< Age String
    ImebraAT = 0x4154, ///< Attribute Tag
    ImebraCS = 0x4353, ///< Code String
    ImebraDA = 0x4441, ///< Date
    ImebraDS = 0x4453, ///< Decimal String
    ImebraDT = 0x4454, ///< Date Time
    ImebraFL = 0x464c, ///< Floating Point Single
    ImebraFD = 0x4644, ///< Floating Point Double
    ImebraIS = 0x4953, ///< Integer String
    ImebraLO = 0x4c4f, ///< Long String
    ImebraLT = 0x4c54, ///< Long Text
    ImebraOB = 0x4f42, ///< Other Byte String
    ImebraSB = 0x5342, ///< Non standard. Used internally for signed bytes
    ImebraOD = 0x4f44, ///< Other Double String
    ImebraOF = 0x4f46, ///< Other Float String
    ImebraOL = 0x4f4c, ///< Other Long String
    ImebraOW = 0x4f57, ///< Other Word String
    ImebraPN = 0x504e, ///< Person Name
    ImebraSH = 0x5348, ///< Short String
    ImebraSL = 0x534c, ///< Signed Long
    ImebraSQ = 0x5351, ///< Sequence of Items
    ImebraSS = 0x5353, ///< Signed Short
    ImebraST = 0x5354, ///< Short Text
    ImebraTM = 0x544d, ///< Time
    ImebraUC = 0x5543, ///< Unlimited characters
    ImebraUI = 0x5549, ///< Unique Identifier
    ImebraUL = 0x554c, ///< Unsigned Long
    ImebraUN = 0x554e, ///< Unknown
    ImebraUR = 0x5552, ///< Unified Resource Identifier
    ImebraUS = 0x5553, ///< Unsigned Short
    ImebraUT = 0x5554  ///< Unlimited Text
};

typedef NS_ENUM(unsigned int, ImebraImageQuality_t)
{
    ImebraQualityVeryHigh = 0,      ///< the image is saved with very high quality. No subsampling is performed and no quantization
    ImebraQualityHigh = 100,        ///< the image is saved with high quality. No subsampling is performed. Quantization ratios are low
    ImebraQualityAboveMedium = 200, ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are low
    ImebraQualityMedium = 300,      ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are medium
    ImebraQualityBelowMedium = 400, ///< the image is saved in medium quality. Horizontal and vertical subsampling are applied. Quantization ratios are medium
    ImebraQualityLow = 500,         ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are higher than the ratios used in the belowMedium quality
    ImebraQualityVeryLow = 600      ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are high
};


///
///  \brief This class represents a DICOM dataset.
///
/// The information it contains is organized into groups and each group may
/// contain several tags.
///
/// You can create a DataSet from a DICOM file by using the
/// ImebraCodecFactory::load() function:
///
/// \code
/// NSError* error = nil;
/// ImebraDataSet* pDataSet = [ImebraCodecFactory load:@"dicomFile.dcm" error:&error];
/// \endcode
///
/// You can also create an empty ImebraDataSet that can be filled with data and
/// images and then saved to a DICOM file via ImebraCodecFactory::save().
///
/// When creating an empty ImebraDataSet you should specify the proper transfer
/// syntax in the init method.
///
/// To retrieve the DataSet's content, use one of the following methods which
/// give direct access to the tags' values:
/// - getImage()
/// - getImageApplyModalityTransform()
/// - getSequenceItem()
/// - getSignedLong()
/// - getUnsignedLong()
/// - getDouble()
/// - getString()
/// - getUnicodeString()
/// - getAge()
/// - getDate()
///
/// In alternative, you can first retrieve a ImebraReadingDataHandler with
/// getReadingDataHandler() and then access the tag's content via the handler.
///
/// To set the ImebraDataSet's content, use one of the following methods:
/// - setImage()
/// - setSequenceItem()
/// - setSignedLong()
/// - setUnsignedLong()
/// - setDouble()
/// - setString()
/// - setUnicodeString()
/// - setAge()
/// - setDate()
///
/// The previous methods allow to write just the first item in the tag's
/// content and before writing wipe out the old tag's content (all the items).
/// If you have to write more than one item in a tag, retrieve a
/// ImebraWritingDataHandler with getWritingDataHandler() and then modify all
/// the tag's items using the ImebraWritingDataHandler.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraDataSet: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::DataSet* m_pDataSet;
}

    -(id)initWithImebraDataSet:(imebra::DataSet*)pDataSet;
#endif


    /// \brief Construct an empty DICOM dataset with unspecified transfer syntax
    ///        (e.g. to be used in a sequence) charset "ISO 2022 IR 6".
    ///
    /// Use this method when creating a DataSet that will be embedded in a sequence
    /// item.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)init;

    /// \brief Construct an empty DICOM dataset with charset "ISO 2022 IR 6" and
    ///        the desidered transfer syntax.
    ///
    /// \param transferSyntax the dataSet's transfer syntax. The following transfer
    ///                       syntaxes are supported:
    ///                       - "1.2.840.10008.1.2" (Implicit VR little endian)
    ///                       - "1.2.840.10008.1.2.1" (Explicit VR little endian)
    ///                       - "1.2.840.10008.1.2.2" (Explicit VR big endian)
    ///                       - "1.2.840.10008.1.2.5" (RLE compression)
    ///                       - "1.2.840.10008.1.2.4.50" (Jpeg baseline 8 bit
    ///                         lossy)
    ///                       - "1.2.840.10008.1.2.4.51" (Jpeg extended 12 bit
    ///                         lossy)
    ///                       - "1.2.840.10008.1.2.4.57" (Jpeg lossless NH)
    ///                       - "1.2.840.10008.1.2.4.70" (Jpeg lossless NH first
    ///                         order prediction)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithTransferSyntax:(NSString*)transferSyntax;

    -(void)dealloc;

    /// \brief Retrieve an image from the dataset.
    ///
    /// Images should be retrieved in order (first frame 0, then frame 1, then
    /// frame 2 and so on).
    /// Images can be retrieved also in random order but this introduces
    /// performance penalties.
    ///
    /// Set NSError and returns nil if the requested image does not exist.
    ///
    /// \note Images retrieved from the ImebraDataSet should be processed by the
    ///       ImebraModalityVOILUT transform, which converts the modality-specific
    ///       pixel values to values that the application can understand. Consider
    ///       using getImageApplyModalityTransform() to retrieve the image already
    ///       processed by ImebraModalityVOILUT.
    ///
    /// \param frameNumber the frame to retrieve (the first frame is 0)
    /// \param pError      a pointer to a NSError pointer which is set when an
    ///                    error occurs
    /// \return an ImebraImage object containing the decompressed image
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraImage*) getImage:(unsigned int) frameNumber error:(NSError**)pError;

    /// \brief Retrieve an image from the dataset and if necessary process it with
    ///        ImebraModalityVOILUT before returning it.
    ///
    /// Images should be retrieved in order (first frame 0, then frame 1, then
    ///  frame 2 and so on).
    /// Images can be retrieved also in random order but this introduces
    ///  performance penalties.
    ///
    /// Set NSError and returns nil if the requested image does not exist.
    ///
    /// \param frameNumber the frame to retrieve (the first frame is 0)
    /// \param pError      a pointer to a NSError pointer which is set when an
    ///                    error occurs
    /// \return an ImebraImage object containing the decompressed image
    ///         processed by ImebraModalityVOILUT (if present)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraImage*) getImageApplyModalityTransform:(unsigned int) frameNumber error:(NSError**)pError;


    -(void) setImage:(unsigned int)frameNumber image:(ImebraImage*)image quality:(ImebraImageQuality_t)quality error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));


    -(ImebraReadingDataHandler*) getReadingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError;

    -(ImebraWritingDataHandler*) getWritingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError;

    -(ImebraWritingDataHandler*) getWritingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError;


    -(signed int)getSignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(signed int)getSignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed int)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)setSignedLong:(ImebraTagId*)tagId newValue:(signed int)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)setSignedLong:(ImebraTagId*)tagId newValue:(signed int)newValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(unsigned int)getUnsignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(unsigned int)getUnsignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned int)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)setUnsignedLong:(ImebraTagId*)tagId newValue:(unsigned int)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)setUnsignedLong:(ImebraTagId*)tagId newValue:(unsigned int)newValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(double)getDouble:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(double)getDouble:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(double)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)setDouble:(ImebraTagId*)tagId newValue:(double)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)setDouble:(ImebraTagId*)tagId newValue:(double)newValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(NSString*)getString:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError;

    -(NSString*)getString:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(NSString*)defaultValue error:(NSError**)pError;

    -(void)setString:(ImebraTagId*)tagId newValue:(NSString*)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)setString:(ImebraTagId*)tagId newValue:(NSString*)newValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(ImebraAge*)getAge:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError;

    -(ImebraAge*)getAge:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraAge*)defaultValue error:(NSError**)pError;

    -(void)setAge:(ImebraTagId*)tagId newValue:(ImebraAge*)newValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(ImebraDate*)getDate:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError;

    -(ImebraDate*)getDate:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraDate*)defaultValue error:(NSError**)pError;

    -(void)setDate:(ImebraTagId*)tagId newValue:(ImebraDate*)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)setDate:(ImebraTagId*)tagId newValue:(ImebraDate*)newValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(ImebraTagVR_t)getDataType:(ImebraTagId*)tagId error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));


@end

#endif // imebraObjcDataSet__INCLUDED_


