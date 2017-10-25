#include <gtest/gtest.h>
#include <imebra/imebra.h>
#include <imebra/objectivec/imebra.h>
#include "../buildImageForTest.h"

namespace imebra
{

namespace tests
{

// Test NSString conversion functions
TEST(objectivec, stringToNSStringTest)
{
    // Try a cyrillic/arabic patient name
    std::string patientName0 = "??\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9";
    std::string patientName1 = "\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9";

    ReadWriteMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 6");
        DataSet testDataSet("1.2.840.10008.1.2.1", charsets);

        {
            std::unique_ptr<WritingDataHandler> handler(testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0));

            handler->setString(0, patientName0);
            handler->setString(1, patientName1);
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

    {
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        std::unique_ptr<DataSet> testDataSet(CodecFactory::load(reader));

        std::string patientName0(testDataSet->getString(TagId(0x0010, 0x0010), 0));
        std::string patientName1(testDataSet->getString(TagId(0x0010, 0x0010), 1));

        NSString* nsPatientName0 = stringToNSString(patientName0);
        NSString* nsPatientName1 = stringToNSString(patientName1);

        EXPECT_TRUE([nsPatientName0 isEqualToString:@"??\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"]);
        EXPECT_TRUE([nsPatientName1 isEqualToString:@"\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"]);

    }
}


// Test NSString conversion functions
TEST(objectivec, NSStringToStringTest)
{
    ReadWriteMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 6");
        DataSet testDataSet("1.2.840.10008.1.2.1", charsets);

        {
            std::unique_ptr<WritingDataHandler> handler(testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0));

            handler->setString(0, NSStringToString(@"Test 1"));
            handler->setString(1, NSStringToString(@"Test 2"));
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

    {
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        std::unique_ptr<DataSet> testDataSet(CodecFactory::load(reader));

        std::string patientName0(testDataSet->getString(TagId(0x0010, 0x0010), 0));
        std::string patientName1(testDataSet->getString(TagId(0x0010, 0x0010), 1));

        EXPECT_EQ("Test 1", patientName0);
        EXPECT_EQ("Test 2", patientName1);

    }
}


TEST(objectivec, CodecFactory)
{
    DataSet testDataSet("1.2.840.10008.1.2");
    testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test^Patient");
    testDataSet.setString(TagId(tagId_t::PatientID_0010_0020), "TestID");
    CodecFactory::save(testDataSet, "testCodecFactory.dcm", codecType_t::dicom);

    NSError* error = nil;
    ImebraDataSet* pDataSet = [ImebraCodecFactory load:@"testCodecFactory.dcm" error:&error];
    NSString* checkPatientName = [pDataSet getString:[[ImebraTagId alloc] init:0x10 tag:0x10] elementNumber:0 error:&error];
    NSString* checkPatientID = [pDataSet getString:[[ImebraTagId alloc] init:0x10 tag:0x20] elementNumber:0 error:&error];

    EXPECT_EQ(imebra::NSStringToString(checkPatientName), "Test^Patient");
    EXPECT_EQ(imebra::NSStringToString(checkPatientID), "TestID");
}

TEST(objectivec, CodecFactoryFailLoad)
{
    NSError* error = nil;
    ImebraDataSet* pDataSet = [ImebraCodecFactory load:@"fail.dcm" error:&error];
    EXPECT_EQ(pDataSet, nullptr);
    EXPECT_EQ(imebra::NSStringToString([error domain]), "imebra");
}

TEST(objectivec, image)
{
    ImebraImage* pImage = [[ImebraImage alloc] initWithSize:5 height:5 depth:depthU16 colorSpace:@"MONOCHROME2" highBit:15];

    NSError* error = nil;
    {
        ImebraWritingDataHandlerNumeric* writingDataHandler = [pImage getWritingDataHandler:&error];
        for(unsigned int pixel(0); pixel != 25; ++pixel)
        {
            [writingDataHandler setUnsignedLong:pixel withValue:pixel error:&error];
        }
#if !__has_feature(objc_arc)
        [writingDataHandler release];
#endif
    }

    ImebraDataSet* pDataSet = [[ImebraDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];
    [pDataSet setImage:0 image:pImage quality:veryHigh error:&error];

    ImebraImage* pCheckImage = [pDataSet getImage:0 error:&error];
    ImebraReadingDataHandlerNumeric* readingDataHandler = [pCheckImage getReadingDataHandler:&error];
    for(unsigned int pixel(0); pixel != 25; ++pixel)
    {
        EXPECT_EQ([readingDataHandler getUnsignedLong:pixel error:&error], pixel);
    }
}


TEST(objectivec, datasetValues)
{
    NSError* error = nil;

    ImebraDataSet* pDataSet = [[ImebraDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

    [pDataSet setString:[[ImebraTagId alloc] init:0x10 tag:0x10] newValue:@"TestPatient" error:&error];
    [pDataSet setAge:[[ImebraTagId alloc] init:0x10 tag:0x1010] newValue:[[ImebraAge alloc] initWithAge:10 units:years] error:&error];

    NSString* checkPatient0 = [pDataSet getString:[[ImebraTagId alloc] init:0x10 tag:0x10] elementNumber:0 error:&error];
    ImebraAge* checkAge = [pDataSet getAge:[[ImebraTagId alloc] init:0x10 tag:0x1010] elementNumber:0 error:&error];

    EXPECT_EQ(error, nil);
    NSString* checkPatient1 = [pDataSet getString:[[ImebraTagId alloc] init:0x10 tag:0x11] elementNumber:0 error:&error];
    EXPECT_EQ(imebra::NSStringToString([error domain]), "imebra");

    NSString* checkPatient2 = [pDataSet getString:[[ImebraTagId alloc] init:0x10 tag:0x11] elementNumber:0 defaultValue:@"defaultValue" error:&error];

    EXPECT_EQ(imebra::NSStringToString(checkPatient0), "TestPatient");
    EXPECT_EQ(checkPatient1, nil);
    EXPECT_EQ(imebra::NSStringToString(checkPatient2), "defaultValue");

    EXPECT_EQ([checkAge age], 10);
    EXPECT_EQ([checkAge units], years);
}


#if defined(__APPLE__)
// Test NSImage
TEST(objectivec, images)
{
    std::string transferSyntax = "1.2.840.10008.1.2.4.50";
    DataSet dataset(transferSyntax);

    std::uint32_t width = 600;
    std::uint32_t height = 400;

    std::unique_ptr<Image> baselineImage(buildImageForTest(width, height, bitDepth_t::depthU8, 7, 30, 20, "RGB", 50));

    std::unique_ptr<Transform> colorTransform(ColorTransformsFactory::getTransform("RGB", "YBR_FULL"));
    std::unique_ptr<Image> ybrImage(colorTransform->allocateOutputImage(*baselineImage, width, height));
    colorTransform->runTransform(*baselineImage, 0, 0, width, height, *ybrImage, 0, 0);

    TransformsChain chain;
    DrawBitmap drawBitmap(chain);
    NSImage* nsImage = getImebraImage(*ybrImage, drawBitmap);

    NSData *imageData = [nsImage TIFFRepresentation];
    NSBitmapImageRep *imageRep = [NSBitmapImageRep imageRepWithData:imageData];
    NSDictionary *imageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:1.0] forKey:NSImageCompressionFactor];
    imageData = [imageRep representationUsingType:NSJPEGFileType properties:imageProps];

    ReadWriteMemory dataMemory((const char*)[imageData bytes], [imageData length]);
    MemoryStreamInput dataStream(dataMemory);
    StreamReader dataReader(dataStream);

    std::unique_ptr<DataSet> loadedDataSet(CodecFactory::load(dataReader));
    std::unique_ptr<Image> loadedImage(loadedDataSet->getImage(0));

    // Compare the buffers. A little difference is allowed
    double differenceYBR = compareImages(*ybrImage, *loadedImage);
    ASSERT_LE(differenceYBR, 1);
}
#endif

} // namespace tests

} // namespace imebra
