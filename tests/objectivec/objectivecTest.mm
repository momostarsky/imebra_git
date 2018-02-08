#include <gtest/gtest.h>
#include <imebra/imebra.h>
#include <imebraobjc/imebra.h>
#include "../buildImageForTest.h"
#include "../../objectivec/src/imebra_strings.h"
#include <thread>

namespace imebra
{

namespace tests
{

// Test NSString conversion functions
TEST(objectivec, stringToNSStringTest)
{
    NSAutoreleasePool *myPool = [[NSAutoreleasePool alloc] init];

    NSString* patient0 = [[NSString alloc] initWithUTF8String:"??\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"];
    NSString* patient1 = [[NSString alloc] initWithUTF8String:"\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"];

    ImebraReadWriteMemory* pStreamMemory = [[ImebraReadWriteMemory alloc] init];
    ImebraTagId* pPatientTag = [[ImebraTagId alloc] initWithId:ImebraTagPatientName_0010_0010];
    {
        NSMutableArray* pCharsets = [[NSMutableArray alloc] init];
        [pCharsets addObject: @"ISO_IR 6"];
        ImebraDataSet* pDataSet = [[ImebraDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2.1" charsets:pCharsets];

        {
            NSError* pError = 0;
            ImebraWritingDataHandler* pHandler = [pDataSet getWritingDataHandler:pPatientTag bufferId:0 error:&pError];

            [pHandler setString:0 withValue:patient0 error:&pError];
            [pHandler setString:1 withValue:patient1 error:&pError];

            [pHandler release];
        }

        ImebraMemoryStreamOutput* pWriteStream = [[ImebraMemoryStreamOutput alloc] initWithReadWriteMemory:pStreamMemory];
        ImebraStreamWriter* pWriter = [[ImebraStreamWriter alloc] initWithOutputStream: pWriteStream];
        NSError* pError = 0;
        [ImebraCodecFactory saveToStream:pWriter dataSet:pDataSet codecType:ImebraCodecTypeDicom error:&pError];

        [pWriter release];
        [pWriteStream release];

        NSArray* pTags = [pDataSet getTags];
        size_t numTags = [pTags count];
        bool bPatientFound(false);
        for(size_t scanTags(0); scanTags != numTags; ++scanTags)
        {
            ImebraTagId* pTag = [pTags objectAtIndex:scanTags];
            if(pTag.groupId == 0x10 && pTag.tagId == 0x10 && pTag.groupOrder == 0)
            {
                bPatientFound = true;
            }
        }
        EXPECT_TRUE(bPatientFound);

    }

    {
        ImebraMemoryStreamInput* pReadStream = [[ImebraMemoryStreamInput alloc] initWithReadMemory:pStreamMemory];

        ImebraStreamReader* pReader = [[ImebraStreamReader alloc] initWithInputStream:pReadStream];

        NSError* pError = 0;
        ImebraDataSet* pTestDataSet = [ImebraCodecFactory loadFromStream:pReader error:&pError];

        NSString* nsPatientName0 = [pTestDataSet getString:pPatientTag elementNumber:0 error:&pError];
        NSString* nsPatientName1 = [pTestDataSet getString:pPatientTag elementNumber:1 error:&pError];

        EXPECT_TRUE([nsPatientName0 isEqualToString:patient0]);
        EXPECT_TRUE([nsPatientName1 isEqualToString:patient1]);
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


// Test the codec factory (save and reload a dataset)
TEST(objectivec, CodecFactory)
{
    DataSet testDataSet("1.2.840.10008.1.2");
    testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test^Patient");
    testDataSet.setString(TagId(tagId_t::PatientID_0010_0020), "TestID");
    CodecFactory::save(testDataSet, "testCodecFactory.dcm", codecType_t::dicom);

    NSError* error = nil;
    ImebraDataSet* pDataSet = [ImebraCodecFactory loadFromFile:@"testCodecFactory.dcm" error:&error];
    NSString* checkPatientName = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&error];
    NSString* checkPatientID = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x20] elementNumber:0 error:&error];

    EXPECT_EQ(imebra::NSStringToString(checkPatientName), "Test^Patient");
    EXPECT_EQ(imebra::NSStringToString(checkPatientID), "TestID");
}


// Test NSError on non-existent file
TEST(objectivec, CodecFactoryFailLoad)
{
    NSError* error = nil;
    ImebraDataSet* pDataSet = [ImebraCodecFactory loadFromFile:@"fail.dcm" error:&error];
    EXPECT_EQ(pDataSet, nullptr);
    EXPECT_EQ(imebra::NSStringToString([error domain]), "imebra");
}


// Initialize and check an image content
TEST(objectivec, image)
{
    ImebraImage* pImage = [[ImebraImage alloc] initWithWidth:5 height:5 depth:ImebraBitDepthU16 colorSpace:@"MONOCHROME2" highBit:15];

    NSError* error = nil;
#if __has_feature(objc_arc)
    @autoreleasepool
#endif
    {
        ImebraWritingDataHandler* writingDataHandler = [pImage getWritingDataHandler:&error];
        for(unsigned int pixel(0); pixel != 25; ++pixel)
        {
            [writingDataHandler setUnsignedLong:pixel withValue:pixel error:&error];
        }
#if !__has_feature(objc_arc)
        [writingDataHandler release];
#endif
    }

    ImebraDataSet* pDataSet = [[ImebraDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];
    [pDataSet setImage:0 image:pImage quality:ImebraQualityVeryHigh error:&error];

    ImebraImage* pCheckImage = [pDataSet getImage:0 error:&error];
    ImebraReadingDataHandlerNumeric* readingDataHandler = [pCheckImage getReadingDataHandler:&error];
    for(unsigned int pixel(0); pixel != 25; ++pixel)
    {
        EXPECT_EQ([readingDataHandler getUnsignedLong:pixel error:&error], pixel);
    }
}


// Initialize and check an image content
TEST(objectivec, imageNSData)
{
    ImebraImage* pImage = [[ImebraImage alloc] initWithWidth:5 height:5 depth:ImebraBitDepthU16 colorSpace:@"MONOCHROME2" highBit:15];

    NSError* error = nil;
#if __has_feature(objc_arc)
    @autoreleasepool
#endif
    {
        std::uint16_t buffer[25];
        for(unsigned int pixel(0); pixel != 25; ++pixel)
        {
            buffer[pixel] = pixel + 1;
        }
        NSData* pSource = [[NSData alloc] initWithBytes:buffer length:sizeof(buffer)];
        ImebraWritingDataHandlerNumeric* writingDataHandler = [pImage getWritingDataHandler:&error];
        [writingDataHandler assign:pSource error:&error];
#if !__has_feature(objc_arc)
        [writingDataHandler release];
#endif
    }

    ImebraDataSet* pDataSet = [[ImebraDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];
    [pDataSet setImage:0 image:pImage quality:ImebraQualityVeryHigh error:&error];

    ImebraImage* pCheckImage = [pDataSet getImage:0 error:&error];
    ImebraReadingDataHandlerNumeric* readingDataHandler = [pCheckImage getReadingDataHandler:&error];
    NSData* pData = [readingDataHandler getMemory:&error].data;
    for(unsigned int pixel(0); pixel != 25; ++pixel)
    {
        EXPECT_EQ(pixel + 1, ((std::uint16_t*)(pData.bytes))[pixel]);
    }
}



// Set different dataset tags
TEST(objectivec, datasetValues)
{
    NSError* error = nil;

    ImebraDataSet* pDataSet = [[ImebraDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

    [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&error];
    [pDataSet setAge:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1010] newValue:[[ImebraAge alloc] initWithAge:10 units:ImebraYears] error:&error];

    NSString* checkPatient0 = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&error];
    ImebraAge* checkAge = [pDataSet getAge:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1010] elementNumber:0 error:&error];

    EXPECT_EQ(error, nil);
    NSString* checkPatient1 = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x11] elementNumber:0 error:&error];
    EXPECT_EQ(imebra::NSStringToString([error domain]), "imebra");
    NSString* checkPatient2 = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x11] elementNumber:0 defaultValue:@"defaultValue" error:&error];

    EXPECT_EQ(imebra::NSStringToString(checkPatient0), "TestPatient");
    EXPECT_EQ(checkPatient1, nil);
    EXPECT_EQ(imebra::NSStringToString(checkPatient2), "defaultValue");

    EXPECT_EQ([checkAge age], 10);
    EXPECT_EQ([checkAge units], ImebraYears);
}


void listenerThread()
{
    try
    {
    NSError* pError;
    ImebraTCPPassiveAddress* pAddress = [[ImebraTCPPassiveAddress alloc] initWithNode:@"localhost" service:@"20000" error:&pError];
    ImebraTCPListener* pListener = [[ImebraTCPListener alloc] initWithAddress:pAddress error:&pError];

    ImebraTCPStream* pStream = [pListener waitForConnection:&pError];

    ImebraStreamReader* pReader = [[ImebraStreamReader alloc] initWithInputStream:pStream];
    ImebraStreamWriter* pWriter = [[ImebraStreamWriter alloc] initWithInputOutputStream:pStream];

    ImebraPresentationContexts* pContexts = [[ImebraPresentationContexts alloc] init];

    ImebraPresentationContext* pContext = [[ImebraPresentationContext alloc] initWithAbstractSyntax:@"1.2.840.10008.1.1"];
    [pContext addTransferSyntax:@"1.2.840.10008.1.2"];

    [pContexts addPresentationContext:pContext];

    ImebraAssociationSCP* pSCP = [[ImebraAssociationSCP alloc]
            initWithThisAET:@"SCP" maxInvokedOperations:1 maxPerformedOperations:1 presentationContexts:pContexts
                 reader:pReader writer:pWriter dimseTimeoutSeconds:30 artimTimeoutSeconds:30 error:&pError];

    ImebraDimseService* pDimse = [[ImebraDimseService alloc]initWithAssociation:pSCP];

    ImebraCStoreCommand* pCommand = (ImebraCStoreCommand*)[pDimse getCommand:&pError];

    ImebraCStoreResponse* pResponse = [[ImebraCStoreResponse alloc]initWithcommand:pCommand responseCode:ImebraDimseSuccess];

    [pDimse sendCommandOrResponse:pResponse error:&pError];

#if !__has_feature(objc_arc)

    [pDimse release];
    [pSCP release];
    [pReader release];
    [pWriter release];
    [pStream release];
    [pListener release];
#endif
    }
    catch(const std::runtime_error&e)
    {
        std::cout << imebra::ExceptionsManager::getExceptionTrace();

    }
}


// Send a CStore command to a SCP via TCP
TEST(objectivec, dimse)
{
    std::thread scp(imebra::tests::listenerThread);
    try
    {

    std::this_thread::sleep_for(std::chrono::seconds(5));

    NSError* pError(0);
    ImebraTCPActiveAddress* pAddress = [[ImebraTCPActiveAddress alloc] initWithNode:@"localhost" service:@"20000" error:&pError];

    ImebraTCPStream* pStream = [[ImebraTCPStream alloc] initWithAddress:pAddress error:&pError];

    ImebraStreamReader* pReader = [[ImebraStreamReader alloc] initWithInputStream:pStream];
    ImebraStreamWriter* pWriter = [[ImebraStreamWriter alloc] initWithInputOutputStream:pStream];

    ImebraPresentationContexts* pContexts = [[ImebraPresentationContexts alloc] init];

    ImebraPresentationContext* pContext = [[ImebraPresentationContext alloc] initWithAbstractSyntax:@"1.2.840.10008.1.1"];
    [pContext addTransferSyntax:@"1.2.840.10008.1.2"];

    [pContexts addPresentationContext:pContext];

    ImebraAssociationSCU* pSCU = [[ImebraAssociationSCU alloc]
            initWithThisAET:@"SCU" otherAET:@"SCP" maxInvokedOperations:1 maxPerformedOperations:1 presentationContexts:pContexts
                 reader:pReader writer:pWriter dimseTimeoutSeconds:30 error:&pError];

    ImebraDimseService* pDimse = [[ImebraDimseService alloc]initWithAssociation:pSCU];

    ImebraDataSet* pDataSet = [[ImebraDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

    [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];
    [pDataSet setAge:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1010] newValue:[[ImebraAge alloc] initWithAge:10 units:ImebraYears] error:&pError];

    ImebraCStoreCommand* pCommand = [[ImebraCStoreCommand alloc]initWithabstractsyntax:
        @"1.2.840.10008.1.1"
        messageID:[pDimse getNextCommandID]
        priority:ImebraPriorityMedium
        affectedSopClassUid:@"1.2.840.10008.1.1"
        affectedSopInstanceUid:@"1.2.3.4.5"
        originatorAET:@"SCU"
        originatorMessageID:0
        payload:pDataSet];


    [pDimse sendCommandOrResponse:pCommand error:&pError];

    ImebraCStoreResponse* pResponse = [pDimse getCStoreResponse:pCommand error:&pError];

    EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);

#if !__has_feature(objc_arc)

    [pDimse release];
    [pSCU release];
    [pReader release];
    [pWriter release];
    [pStream release];
#endif

    }
    catch(std::exception& e)
    {
        std::cout << imebra::ExceptionsManager::getExceptionTrace();
    }

    scp.join();

}


// Test DrawBitmap generating a NSImage
#if defined(__APPLE__)

TEST(objectivec, images)
{
    NSError* pError(0);

    unsigned int width = 600;
    unsigned int height = 400;

    ImebraImage* pBaselineImage = [[ImebraImage alloc] initWithWidth:width height:height depth:ImebraBitDepthU8 colorSpace:@"RGB" highBit:7];

    {
        ImebraWritingDataHandler* pWritingDataHandler = [pBaselineImage getWritingDataHandler:&pError];

        unsigned int index(0);
        for(unsigned int y(0); y != height; ++y)
        {
            for(unsigned int x(0); x != width; ++x)
            {
                int r = x < 100 ? 10: 100;
                int g = x < 200 ? 40: 200;
                int b = x < 300 ? 100: 4;
                [pWritingDataHandler setUnsignedLong:index++ withValue:r error:&pError];
                [pWritingDataHandler setUnsignedLong:index++ withValue:g error:&pError];
                [pWritingDataHandler setUnsignedLong:index++ withValue:b error:&pError];

            }
        }
        #if !__has_feature(objc_arc)
            [pWritingDataHandler release];
        #endif

    }


    ImebraTransform* pColorTransform = [ImebraColorTransformsFactory getTransform:@"RGB" finalColorSpace:@"YBR_FULL" error:&pError];

    ImebraImage* pYbrImage = [pColorTransform allocateOutputImage:pBaselineImage width:width height:height error:&pError];

    [pColorTransform runTransform:pBaselineImage inputTopLeftX:0 inputTopLeftY:0 inputWidth:width inputHeight:height outputImage:pYbrImage outputTopLeftX:0 outputTopLeftY:0 error:&pError];

    ImebraDrawBitmap* pDrawBitmap = [[ImebraDrawBitmap alloc] init];

    NSImage* pNsImage = [pDrawBitmap getImebraImage:pYbrImage error:&pError];

    NSData* pImageData = [pNsImage TIFFRepresentation];
    NSBitmapImageRep* pImageRep = [NSBitmapImageRep imageRepWithData:pImageData];
    NSDictionary *pImageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:1.0] forKey:NSImageCompressionFactor];
    pImageData = [pImageRep representationUsingType:NSJPEGFileType properties:pImageProps];

    ImebraReadWriteMemory* pDataMemory = [[ImebraReadWriteMemory alloc] initWithData:pImageData];
    ImebraMemoryStreamInput* pDataStream = [[ImebraMemoryStreamInput alloc] initWithReadMemory:pDataMemory];
    ImebraStreamReader* pDataReader = [[ImebraStreamReader alloc] initWithInputStream:pDataStream];

    ImebraDataSet* pLoadedDataSet = [ImebraCodecFactory loadFromStream:pDataReader error:&pError];
    ImebraImage* pLoadedImage = [pLoadedDataSet getImage:0 error:&pError];

    // Compare the buffers. A little difference is allowed
    double differenceYBR = compareImages(*(pYbrImage->m_pImage), *(pLoadedImage->m_pImage));
    ASSERT_LE(differenceYBR, 1);
}

#endif

} // namespace tests

} // namespace imebra
