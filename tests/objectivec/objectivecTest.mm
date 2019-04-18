#include <gtest/gtest.h>
#include <imebra/imebra.h>
#include <imebraobjc/imebra.h>
#include "../buildImageForTest.h"
#include "../../objectivec/src/imebra_strings.h"
#include <thread>

#if __has_feature(objc_arc)

#define AUTORELEASE_START(poolName) \
    @autoreleasepool {

#define AUTORELEASE_END(poolName) \
    }

#else

#define AUTORELEASE_START(poolName) \
    { \
        NSAutoreleasePool *poolName = [[NSAutoreleasePool alloc] init];

#define AUTORELEASE_END(poolName) \
        [poolName drain]; \
    }

#endif


namespace imebra
{

namespace tests
{


// Test NSString conversion functions
TEST(objectivec, stringToNSStringTest)
{
    AUTORELEASE_START(pool)

    NSString* patient0 = [[[NSString alloc] initWithUTF8String:"??\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"] autorelease];
    NSString* patient1 = [[[NSString alloc] initWithUTF8String:"\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"] autorelease];

    ImebraMutableMemory* pStreamMemory = [[[ImebraMutableMemory alloc] init] autorelease];
    ImebraTagId* pPatientTag = [[[ImebraTagId alloc] initWithId:ImebraTagPatientName_0010_0010] autorelease];

    AUTORELEASE_START(pool1)

        NSMutableArray* pCharsets = [[[NSMutableArray alloc] init] autorelease];
        [pCharsets addObject: @"ISO_IR 6"];
        ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2.1" charsets:pCharsets] autorelease];

        AUTORELEASE_START(pool2)

            NSError* pError = 0;
            ImebraWritingDataHandler* pHandler = [pDataSet getWritingDataHandler:pPatientTag bufferId:0 error:&pError];

            [pHandler setString:0 newValue:patient0 error:&pError];
            [pHandler setString:1 newValue:patient1 error:&pError];

        AUTORELEASE_END(pool2)


        AUTORELEASE_START(pool2)

            ImebraMemoryStreamOutput* pWriteStream = [[[ImebraMemoryStreamOutput alloc] initWithMutableMemory:pStreamMemory] autorelease];
            ImebraStreamWriter* pWriter = [[[ImebraStreamWriter alloc] initWithOutputStream: pWriteStream] autorelease];
            NSError* pError = 0;
            [ImebraCodecFactory saveToStream:pWriter dataSet:pDataSet codecType:ImebraCodecTypeDicom error:&pError];

        AUTORELEASE_END(pool2)

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

    AUTORELEASE_END(pool1)

    ImebraMemoryStreamInput* pReadStream = [[[ImebraMemoryStreamInput alloc] initWithReadMemory:pStreamMemory] autorelease];

    ImebraStreamReader* pReader = [[[ImebraStreamReader alloc] initWithInputStream:pReadStream] autorelease];

    NSError* pError = 0;
    ImebraDataSet* pTestDataSet = [ImebraCodecFactory loadFromStream:pReader error:&pError];

    NSString* nsPatientName0 = [pTestDataSet getString:pPatientTag elementNumber:0 error:&pError];
    NSString* nsPatientName1 = [pTestDataSet getString:pPatientTag elementNumber:1 error:&pError];

    EXPECT_TRUE([nsPatientName0 isEqualToString:patient0]);
    EXPECT_TRUE([nsPatientName1 isEqualToString:patient1]);

    AUTORELEASE_END(pool)

}


// Test NSString conversion functions
TEST(objectivec, NSStringToStringTest)
{
    AUTORELEASE_START(pool)

    MutableMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 6");
        MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

        {
            WritingDataHandler handler(testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0));

            handler.setString(0, NSStringToString(@"Test 1"));
            handler.setString(1, NSStringToString(@"Test 2"));
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

    {
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        DataSet testDataSet(CodecFactory::load(reader));

        std::string patientName0(testDataSet.getString(TagId(0x0010, 0x0010), 0));
        std::string patientName1(testDataSet.getString(TagId(0x0010, 0x0010), 1));

        EXPECT_EQ("Test 1", patientName0);
        EXPECT_EQ("Test 2", patientName1);

    }

    AUTORELEASE_END(pool)
}


// Test the codec factory (save and reload a dataset)
TEST(objectivec, CodecFactory)
{
    AUTORELEASE_START(pool)

    MutableDataSet testDataSet("1.2.840.10008.1.2");
    testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test^Patient");
    testDataSet.setString(TagId(tagId_t::PatientID_0010_0020), "TestID");
    CodecFactory::save(testDataSet, "testCodecFactory.dcm", codecType_t::dicom);

    NSError* error = nil;
    ImebraDataSet* pDataSet = [ImebraCodecFactory loadFromFile:@"testCodecFactory.dcm" error:&error];
    NSString* checkPatientName = [pDataSet getString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] elementNumber:0 error:&error];
    NSString* checkPatientID = [pDataSet getString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x20] autorelease] elementNumber:0 error:&error];

    EXPECT_EQ(imebra::NSStringToString(checkPatientName), "Test^Patient");
    EXPECT_EQ(imebra::NSStringToString(checkPatientID), "TestID");

    AUTORELEASE_END(pool)
}


// Test NSError on non-existent file
TEST(objectivec, CodecFactoryFailLoad)
{
    AUTORELEASE_START(pool)

    NSError* error = nil;
    ImebraDataSet* pDataSet = [ImebraCodecFactory loadFromFile:@"fail.dcm" error:&error];
    EXPECT_EQ(pDataSet, nullptr);
    EXPECT_EQ(imebra::NSStringToString([error domain]), "imebra");

    AUTORELEASE_END(pool)
}


// Initialize and check an image content
TEST(objectivec, image)
{
    AUTORELEASE_START(pool)

    ImebraMutableImage* pImage = [[[ImebraMutableImage alloc] initWithWidth:5 height:5 depth:ImebraBitDepthU16 colorSpace:@"MONOCHROME2" highBit:15] autorelease];
    NSError* error = nil;

    AUTORELEASE_START(pool1)

        ImebraWritingDataHandler* writingDataHandler = [pImage getWritingDataHandler:&error];
        for(unsigned int pixel(0); pixel != 25; ++pixel)
        {
            [writingDataHandler setUnsignedLong:pixel newValue:pixel error:&error];
        }

    AUTORELEASE_END(pool1)

    ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

    [pDataSet setImage:0 image:pImage quality:ImebraQualityVeryHigh error:&error];

    ImebraImage* pCheckImage = [pDataSet getImage:0 error:&error];
    ImebraReadingDataHandlerNumeric* readingDataHandler = [pCheckImage getReadingDataHandler:&error];
    for(unsigned int pixel(0); pixel != 25; ++pixel)
    {
        EXPECT_EQ([readingDataHandler getUnsignedLong:pixel error:&error], pixel);
    }

    AUTORELEASE_END(pool)
}


// Initialize and check an image content
TEST(objectivec, imageNSData)
{
    AUTORELEASE_START(pool)

    ImebraMutableImage* pImage = [[[ImebraMutableImage alloc] initWithWidth:5 height:5 depth:ImebraBitDepthU16 colorSpace:@"MONOCHROME2" highBit:15] autorelease];
    NSError* error = nil;

    AUTORELEASE_START(pool1)

        std::uint16_t buffer[25];
        for(std::uint16_t pixel(0); pixel != 25; ++pixel)
        {
            buffer[pixel] = (std::uint16_t)(pixel + 1u);
        }
        NSData* pSource = [[[NSData alloc] initWithBytes:buffer length:sizeof(buffer)] autorelease];
        ImebraWritingDataHandlerNumeric* writingDataHandler = [pImage getWritingDataHandler:&error];
        [writingDataHandler assign:pSource error:&error];

    AUTORELEASE_END(pool1)

    ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

    [pDataSet setImage:0 image:pImage quality:ImebraQualityVeryHigh error:&error];

    ImebraImage* pCheckImage = [pDataSet getImage:0 error:&error];
    ImebraReadingDataHandlerNumeric* readingDataHandler = [pCheckImage getReadingDataHandler:&error];
    NSData* pData = [readingDataHandler getMemory:&error].data;
    for(unsigned int pixel(0); pixel != 25; ++pixel)
    {
        EXPECT_EQ(pixel + 1, ((std::uint16_t*)(pData.bytes))[pixel]);
    }

    AUTORELEASE_END(pool)

}



// Set different dataset tags
TEST(objectivec, datasetValues)
{
    AUTORELEASE_START(pool)

    NSError* error = nil;

    ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

    [pDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"TestPatient" error:&error];
    [pDataSet setAge:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1010] autorelease] newValue:[[[ImebraAge alloc] initWithAge:10 units:ImebraYears] autorelease] error:&error];

    [pDataSet setSignedLong:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1011] autorelease] newValue:10 tagVR:ImebraSL error:&error];
    [pDataSet setUnsignedLong:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1012] autorelease] newValue:11 tagVR:ImebraUL error:&error];
    [pDataSet setDouble:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1013] autorelease] newValue:12.0f tagVR:ImebraUL error:&error];

    ImebraMutableTag* pTag = [pDataSet getTagCreate:[[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] autorelease] tagVR:ImebraFD error:&error];

    AUTORELEASE_START(pool1)

        ImebraWritingDataHandlerNumeric* pWriteDouble = [pTag getWritingDataHandlerNumeric:0 error:&error];
        [pWriteDouble setSize:4];
        EXPECT_EQ(4u, pWriteDouble.size);
        [pWriteDouble setDouble:0 newValue:0 error:&error];
        [pWriteDouble setDouble:1 newValue:1 error:&error];
        [pWriteDouble setDouble:2 newValue:2 error:&error];
        [pWriteDouble setDouble:3 newValue:3 error:&error];

    AUTORELEASE_END(pool1)

    NSString* checkPatient0 = [pDataSet getString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] elementNumber:0 error:&error];
    ImebraAge* checkAge = [pDataSet getAge:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1010] autorelease] elementNumber:0 error:&error];

    EXPECT_EQ(error, nil);
    NSString* checkPatient1 = [pDataSet getString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x11] autorelease] elementNumber:0 error:&error];
    EXPECT_EQ(imebra::NSStringToString([error domain]), "imebra");
    NSString* checkPatient2 = [pDataSet getString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x11] autorelease] elementNumber:0 defaultValue:@"defaultValue" error:&error];

    EXPECT_EQ(imebra::NSStringToString(checkPatient0), "TestPatient");
    EXPECT_EQ(checkPatient1, nil);
    EXPECT_EQ(imebra::NSStringToString(checkPatient2), "defaultValue");

    EXPECT_EQ(10u, [checkAge age]);
    EXPECT_EQ(ImebraYears, [checkAge units]);

    EXPECT_EQ(10, [pDataSet getSignedLong:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1011] autorelease] elementNumber:0 error:&error]);
    EXPECT_EQ(11u, [pDataSet getUnsignedLong:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1012] autorelease] elementNumber:0 error:&error]);
    EXPECT_DOUBLE_EQ(12.0, [pDataSet getDouble:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1013] autorelease] elementNumber:0 error:&error]);
    EXPECT_EQ(12, [pDataSet getSignedLong:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1020] autorelease] elementNumber:0 defaultValue:12u error:&error]);
    EXPECT_EQ(13u, [pDataSet getUnsignedLong:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1021] autorelease] elementNumber:0 defaultValue:13u error:&error]);
    EXPECT_DOUBLE_EQ(14.0, [pDataSet getDouble:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1022] autorelease] elementNumber:0 defaultValue:14.0 error:&error]);

    EXPECT_DOUBLE_EQ(0.0, [pDataSet getDouble:[[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] autorelease] elementNumber:0 error:&error]);
    EXPECT_DOUBLE_EQ(1.0, [pDataSet getDouble:[[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] autorelease] elementNumber:1 error:&error]);
    EXPECT_DOUBLE_EQ(2.0, [pDataSet getDouble:[[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] autorelease] elementNumber:2 error:&error]);
    EXPECT_DOUBLE_EQ(3.0, [pDataSet getDouble:[[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] autorelease] elementNumber:3 error:&error]);

    AUTORELEASE_END(pool)
}


void listenerThread()
{
    AUTORELEASE_START(pool)

    try
    {
        NSError* pError(0);
        ImebraTCPPassiveAddress* pAddress = [[[ImebraTCPPassiveAddress alloc] initWithNode:@"localhost" service:@"20000" error:&pError] autorelease];
        ImebraTCPListener* pListener = [[[ImebraTCPListener alloc] initWithAddress:pAddress error:&pError] autorelease];

        ImebraTCPStream* pStream = [pListener waitForConnection:&pError];

        ImebraBaseStreamInput* pInput = [pStream getStreamInput];
        ImebraBaseStreamOutput* pOutput = [pStream getStreamOutput];
        ImebraStreamReader* pReader = [[[ImebraStreamReader alloc] initWithInputStream:pInput] autorelease];
        ImebraStreamWriter* pWriter = [[[ImebraStreamWriter alloc] initWithOutputStream:pOutput] autorelease];

        ImebraPresentationContexts* pContexts = [[[ImebraPresentationContexts alloc] init] autorelease];

        ImebraPresentationContext* pContext = [[[ImebraPresentationContext alloc] initWithAbstractSyntax:@"1.2.840.10008.1.1"] autorelease];
        [pContext addTransferSyntax:@"1.2.840.10008.1.2"];

        [pContexts addPresentationContext:pContext];

        ImebraAssociationSCP* pSCP = [[[ImebraAssociationSCP alloc]
                initWithThisAET:@"SCP" maxInvokedOperations:1 maxPerformedOperations:1 presentationContexts:pContexts
                     reader:pReader writer:pWriter dimseTimeoutSeconds:30 artimTimeoutSeconds:30 error:&pError] autorelease];

        ImebraDimseService* pDimse = [[[ImebraDimseService alloc]initWithAssociation:pSCP] autorelease];

        for(;;)
        {
            AUTORELEASE_START(pool1)

            ImebraDimseCommand* pCommand = [pDimse getCommand:&pError];

            if(pError != 0)
            {
                break;
            }

            ImebraDimseResponse* pResponse = nil;
            switch([pCommand commandType])
            {
            case ImebraDimseCStore:
                pResponse = [[[ImebraCStoreResponse alloc]initWithcommand:(ImebraCStoreCommand*)pCommand responseCode:ImebraDimseSuccess] autorelease];
                break;
            case ImebraDimseCGet:
                pResponse = [[[ImebraCGetResponse alloc]initWithcommand:(ImebraCGetCommand*)pCommand responseCode:ImebraDimseSuccess
                                                                       remainingSubOperations:0
                                                                       completedSubOperations:1
                                                                       failedSubOperations:0
                                                                       warningSubOperations:0] autorelease];
                break;
            case ImebraDimseCFind:
                pResponse = [[[ImebraCFindResponse alloc]initWithcommand:(ImebraCFindCommand*)pCommand responseCode:ImebraDimseSuccess] autorelease];
                break;
            case ImebraDimseCMove:
                pResponse = [[[ImebraCMoveResponse alloc]initWithcommand:(ImebraCMoveCommand*)pCommand responseCode:ImebraDimseSuccess
                                                                       remainingSubOperations:0
                                                                       completedSubOperations:1
                                                                       failedSubOperations:0
                                                                       warningSubOperations:0] autorelease];
                EXPECT_EQ("DEST", imebra::NSStringToString([(ImebraCMoveCommand*)pCommand getDestinationAET:&pError]));
                break;
            case ImebraDimseCEcho:
                pResponse = [[[ImebraCEchoResponse alloc]initWithcommand:(ImebraCEchoCommand*)pCommand responseCode:ImebraDimseSuccess] autorelease];
                break;
            case ImebraDimseCCancel:
                break;
            case ImebraDimseNEventReport:
                pResponse = [[[ImebraNEventReportResponse alloc]initWithcommand:(ImebraNEventReportCommand*)pCommand responseCode:ImebraDimseSuccess] autorelease];
                break;
            case ImebraDimseNGet:
                pResponse = [[[ImebraNGetResponse alloc]initWithcommand:(ImebraNGetCommand*)pCommand responseCode:ImebraDimseSuccess] autorelease];
                break;
            case ImebraDimseNSet:
                pResponse = [[[ImebraNSetResponse alloc]initWithcommand:(ImebraNSetCommand*)pCommand responseCode:ImebraDimseSuccess] autorelease];
                break;
            case ImebraDimseNAction:
                pResponse = [[[ImebraNActionResponse alloc]initWithcommand:(ImebraNActionCommand*)pCommand responseCode:ImebraDimseSuccess] autorelease];
                break;
            case ImebraDimseNCreate:
                pResponse = [[[ImebraNCreateResponse alloc]initWithcommand:(ImebraNCreateCommand*)pCommand responseCode:ImebraDimseSuccess] autorelease];
                break;
            case ImebraDimseNDelete:
                pResponse = [[[ImebraNDeleteResponse alloc]initWithcommand:(ImebraNDeleteCommand*)pCommand responseCode:ImebraDimseSuccess] autorelease];
                break;
            }

            if(pResponse != nil)
            {
                [pDimse sendCommandOrResponse:pResponse error:&pError];
            }

            AUTORELEASE_END(pool1)
        }

    }
    catch(const std::runtime_error&e)
    {
        std::cout << imebra::ExceptionsManager::getExceptionTrace();
        EXPECT_TRUE(false);

    }

    AUTORELEASE_END(pool)
}


// Send a CStore command to a SCP via TCP
TEST(objectivec, dimse)
{
    AUTORELEASE_START(pool)

    std::thread scp(imebra::tests::listenerThread);

    try
    {

        std::this_thread::sleep_for(std::chrono::seconds(5));

        NSError* pError(0);
        ImebraTCPActiveAddress* pAddress = [[[ImebraTCPActiveAddress alloc] initWithNode:@"localhost" service:@"20000" error:&pError] autorelease];

        ImebraTCPStream* pStream = [[[ImebraTCPStream alloc] initWithAddress:pAddress error:&pError] autorelease];

        ImebraBaseStreamInput* pInput = [pStream getStreamInput];
        ImebraBaseStreamOutput* pOutput = [pStream getStreamOutput];
        ImebraStreamReader* pReader = [[[ImebraStreamReader alloc] initWithInputStream:pInput] autorelease];
        ImebraStreamWriter* pWriter = [[[ImebraStreamWriter alloc] initWithOutputStream:pOutput] autorelease];

        ImebraPresentationContexts* pContexts = [[[ImebraPresentationContexts alloc] init] autorelease];

        ImebraPresentationContext* pContext = [[[ImebraPresentationContext alloc] initWithAbstractSyntax:@"1.2.840.10008.1.1"] autorelease];
        [pContext addTransferSyntax:@"1.2.840.10008.1.2"];

        [pContexts addPresentationContext:pContext];

        ImebraAssociationSCU* pSCU = [[[ImebraAssociationSCU alloc]
                initWithThisAET:@"SCU" otherAET:@"SCP" maxInvokedOperations:1 maxPerformedOperations:1 presentationContexts:pContexts
                     reader:pReader writer:pWriter dimseTimeoutSeconds:30 error:&pError] autorelease];

        ImebraDimseService* pDimse = [[[ImebraDimseService alloc]initWithAssociation:pSCU] autorelease];

        // Send C-STORE
        AUTORELEASE_START(pool1)

            ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

            [pDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"TestPatient" error:&pError];
            [pDataSet setAge:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1010] autorelease] newValue:[[[ImebraAge alloc] initWithAge:10 units:ImebraYears] autorelease] error:&pError];

            ImebraCStoreCommand* pCommand = [[[ImebraCStoreCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                priority:ImebraPriorityMedium
                affectedSopClassUid:@"1.2.840.10008.1.1"
                affectedSopInstanceUid:@"1.2.3.4.5"
                originatorAET:@"SCU"
                originatorMessageID:0
                payload:pDataSet] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];
            ImebraCStoreResponse* pResponse = [pDimse getCStoreResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);

        AUTORELEASE_END(pool1)

        // Send C-GET
        AUTORELEASE_START(pool1)

            ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

            [pDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"TestPatient" error:&pError];

            ImebraCGetCommand* pCommand = [[[ImebraCGetCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                priority:ImebraPriorityMedium
                affectedSopClassUid:@"1.2.840.10008.1.1"
                identifier:pDataSet] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];
            ImebraCGetResponse* pResponse = [pDimse getCGetResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
        AUTORELEASE_END(pool1)

        // Send C-FIND
        AUTORELEASE_START(pool1)
            ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

            [pDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"TestPatient" error:&pError];

            ImebraCFindCommand* pCommand = [[[ImebraCFindCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                priority:ImebraPriorityMedium
                affectedSopClassUid:@"1.2.840.10008.1.1"
                identifier:pDataSet] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];
            ImebraCFindResponse* pResponse = [pDimse getCFindResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
        AUTORELEASE_END(pool1)

        // Send C-MOVE
        AUTORELEASE_START(pool1)
            ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

            [pDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"TestPatient" error:&pError];

            ImebraCMoveCommand* pCommand = [[[ImebraCMoveCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                priority:ImebraPriorityMedium
                affectedSopClassUid:@"1.2.840.10008.1.1"
                destinationAET:@"DEST"
                identifier:pDataSet] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];
            ImebraCMoveResponse* pResponse = [pDimse getCMoveResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
        AUTORELEASE_END(pool1)

        // Send C-ECHO
        AUTORELEASE_START(pool1)
            ImebraCEchoCommand* pCommand = [[[ImebraCEchoCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                priority:ImebraPriorityMedium
                affectedSopClassUid:@"1.2.840.10008.1.1"] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];
            ImebraCEchoResponse* pResponse = [pDimse getCEchoResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
        AUTORELEASE_END(pool1)

        // Send C-CANCEL
        AUTORELEASE_START(pool1)
            ImebraCCancelCommand* pCommand = [[[ImebraCCancelCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                priority:ImebraPriorityMedium
                cancelMessageID:1] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];
        AUTORELEASE_END(pool1)

        // Send N-EVENTREPORT
        AUTORELEASE_START(pool1)
            ImebraNEventReportCommand* pCommand = [[[ImebraNEventReportCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                affectedSopClassUid:@"1.2.840.10008.1.1"
                affectedSopInstanceUid:@"1.1.1"
                eventID:1] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];

            ImebraNEventReportResponse* pResponse = [pDimse getNEventReportResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
        AUTORELEASE_END(pool1)

        // Send N-GET
        AUTORELEASE_START(pool1)
            NSMutableArray* identifierList = [[[NSMutableArray alloc] init] autorelease];
            [identifierList addObject: [[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease]];
            [identifierList addObject: [[[ImebraTagId alloc] initWithGroup:0x20 tag:0x10] autorelease]];

            ImebraNGetCommand* pCommand = [[[ImebraNGetCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                requestedSopClassUid:@"1.2.840.10008.1.1"
                requestedSopInstanceUid:@"1.1.1"
                attributeIdentifierList:identifierList] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];

            ImebraNGetResponse* pResponse = [pDimse getNGetResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
        AUTORELEASE_END(pool1)

        AUTORELEASE_START(pool1)

            ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

            [pDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"TestPatient" error:&pError];

            ImebraNSetCommand* pCommand = [[[ImebraNSetCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                requestedSopClassUid:@"1.2.840.10008.1.1"
                requestedSopInstanceUid:@"1.1.1"
                modificationList:pDataSet] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];

            ImebraNSetResponse* pResponse = [pDimse getNSetResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
        AUTORELEASE_END(pool1)

        // Send N-ACTION
        AUTORELEASE_START(pool1)
            ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

            [pDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"TestPatient" error:&pError];

            ImebraNActionCommand* pCommand = [[[ImebraNActionCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                requestedSopClassUid:@"1.2.840.10008.1.1"
                requestedSopInstanceUid:@"1.1.1"
                actionID:10
                actionInformation:pDataSet] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];

            ImebraNActionResponse* pResponse = [pDimse getNActionResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            EXPECT_EQ(10, pResponse.actionID);
        AUTORELEASE_END(pool1)

        // Send N-CREATE
        AUTORELEASE_START(pool1)

            ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

            [pDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"TestPatient" error:&pError];

            ImebraNCreateCommand* pCommand = [[[ImebraNCreateCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                affectedSopClassUid:@"1.2.840.10008.1.1"
                affectedSopInstanceUid:@"1.1.1"
                attributeList:pDataSet] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];

            ImebraNCreateResponse* pResponse = [pDimse getNCreateResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
        AUTORELEASE_END(pool1)

        // Send N-DELETE
        AUTORELEASE_START(pool1)
            ImebraMutableDataSet* pDataSet = [[[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"] autorelease];

            [pDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"TestPatient" error:&pError];

            ImebraNDeleteCommand* pCommand = [[[ImebraNDeleteCommand alloc]initWithAbstractSyntax:
                @"1.2.840.10008.1.1"
                messageID:[pDimse getNextCommandID]
                requestedSopClassUid:@"1.2.840.10008.1.1"
                requestedSopInstanceUid:@"1.1.1"] autorelease];

            [pDimse sendCommandOrResponse:pCommand error:&pError];

            ImebraNDeleteResponse* pResponse = [pDimse getNDeleteResponse:pCommand error:&pError];

            EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
        AUTORELEASE_END(pool1)


    }
    catch(...)
    {
        std::cout << imebra::ExceptionsManager::getExceptionTrace();
    }

    scp.join();

    AUTORELEASE_END(pool)

}


// Test interface with dicomdir
TEST(objectivec, createDicomDir)
{
    AUTORELEASE_START(pool)

    ImebraMutableDicomDir* newDicomDir = [[[ImebraMutableDicomDir alloc] init] autorelease];

    NSError* pError(0);
    ImebraMutableDicomDirEntry* rootRecord = [newDicomDir getNewEntry:@"PATIENT" error:&pError];

    ImebraMutableDataSet* rootRecordDataSet = [rootRecord getEntryDataSet];
    [rootRecordDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"Surname" error:&pError];
    [newDicomDir setFirstRootEntry:rootRecord error:&pError];

    ImebraMutableDicomDirEntry* nextRecord = [newDicomDir getNewEntry:@"PATIENT" error:&pError];
    ImebraMutableDataSet* nextRecordDataSet = [nextRecord getEntryDataSet];
    [nextRecordDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] newValue:@"Surname 1" error:&pError];
    [rootRecord setNextEntry:nextRecord error:&pError];

    ImebraMutableDicomDirEntry* imageRecord = [newDicomDir getNewEntry:@"IMAGE" error:&pError];
    ImebraMutableDataSet* imageRecordDataSet = [imageRecord getEntryDataSet];
    [imageRecordDataSet setString:[[[ImebraTagId alloc] initWithGroup:0x8 tag:0x18] autorelease] newValue:@"1.2.840.34.56.78999654.235" error:&pError];
    [nextRecord setFirstChildEntry:imageRecord error:&pError];

    NSMutableArray* parts = [[[NSMutableArray alloc] init] autorelease];
    [parts addObject: @"folder"];
    [parts addObject: @"file.dcm"];

    [imageRecord setFileParts:parts error:&pError];

    [nextRecord setFirstChildEntry:imageRecord error:&pError];

    ImebraDataSet* dicomDirDataSet = [newDicomDir updateDataSet:&pError];

    ImebraDicomDir* testDicomDir = [[[ImebraDicomDir alloc] initWithDataSet:dicomDirDataSet error:&pError] autorelease];
    ImebraDicomDirEntry* testRootRecord = [testDicomDir getFirstRootEntry:&pError];
    ImebraDataSet* testRootRecordDataSet = [testRootRecord getEntryDataSet];
    EXPECT_EQ("PATIENT", NSStringToString([testRootRecord getTypeString:&pError]));
    EXPECT_EQ("Surname", NSStringToString([testRootRecordDataSet getString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] elementNumber:0 error:&pError]));

    ImebraDicomDirEntry* testNextRecord = [testRootRecord getNextEntry];
    ImebraDataSet* testNextRecordDataSet = [testNextRecord getEntryDataSet];
    EXPECT_EQ("PATIENT", NSStringToString([testNextRecord getTypeString:&pError]));
    EXPECT_EQ("Surname 1", NSStringToString([testNextRecordDataSet getString:[[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] autorelease] elementNumber:0 error:&pError]));
    EXPECT_EQ(0, [testNextRecord getNextEntry]);

    ImebraDicomDirEntry* testImageRecord = [testNextRecord getFirstChildEntry];
    ImebraDataSet* testImageRecordDataSet = [testImageRecord getEntryDataSet];
    EXPECT_EQ("IMAGE", NSStringToString([testImageRecord getTypeString:&pError]));
    EXPECT_EQ("1.2.840.34.56.78999654.235", NSStringToString([testImageRecordDataSet getString:[[[ImebraTagId alloc] initWithGroup:0x8 tag:0x18] autorelease] elementNumber:0 error:&pError]));
    EXPECT_EQ("folder", NSStringToString([[testImageRecord getFileParts:&pError] objectAtIndex:0]));
    EXPECT_EQ("file.dcm", NSStringToString([[testImageRecord getFileParts:&pError] objectAtIndex:1]));
    EXPECT_EQ(0, [testImageRecord getFirstChildEntry]);

    AUTORELEASE_END(pool)

}


// Test DrawBitmap generating a NSImage
#if defined(__APPLE__)

TEST(objectivec, images)
{
    NSError* pError(0);

    unsigned int width = 600;
    unsigned int height = 400;

    ImebraMutableImage* pBaselineImage = [[ImebraMutableImage alloc] initWithWidth:width height:height depth:ImebraBitDepthU8 colorSpace:@"RGB" highBit:7];

#if __has_feature(objc_arc)
    @autoreleasepool
#endif
    {
        ImebraWritingDataHandler* pWritingDataHandler = [pBaselineImage getWritingDataHandler:&pError];

        unsigned int index(0);
        for(unsigned int y(0); y != height; ++y)
        {
            for(unsigned int x(0); x != width; ++x)
            {
                unsigned int r = x < 100 ? 10: 100;
                unsigned int g = x < 200 ? 40: 200;
                unsigned int b = x < 300 ? 100: 4;
                [pWritingDataHandler setUnsignedLong:index++ newValue:r error:&pError];
                [pWritingDataHandler setUnsignedLong:index++ newValue:g error:&pError];
                [pWritingDataHandler setUnsignedLong:index++ newValue:b error:&pError];

            }
        }
        #if !__has_feature(objc_arc)
            [pWritingDataHandler release];
        #endif
    }


    ImebraTransform* pColorTransform = [ImebraColorTransformsFactory getTransform:@"RGB" finalColorSpace:@"YBR_FULL" error:&pError];

    ImebraMutableImage* pYbrImage = [pColorTransform allocateOutputImage:pBaselineImage width:width height:height error:&pError];

    [pColorTransform runTransform:pBaselineImage inputTopLeftX:0 inputTopLeftY:0 inputWidth:width inputHeight:height outputImage:pYbrImage outputTopLeftX:0 outputTopLeftY:0 error:&pError];

    ImebraDrawBitmap* pDrawBitmap = [[ImebraDrawBitmap alloc] init];

    NSImage* pNsImage = [pDrawBitmap getImebraImage:pYbrImage error:&pError];

    NSData* pImageData = [pNsImage TIFFRepresentation];
    NSBitmapImageRep* pImageRep = [NSBitmapImageRep imageRepWithData:pImageData];
    NSDictionary *pImageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:1.0] forKey:NSImageCompressionFactor];
    pImageData = [pImageRep representationUsingType:NSJPEGFileType properties:pImageProps];

    ImebraMutableMemory* pDataMemory = [[ImebraMutableMemory alloc] initWithData:pImageData];
    ImebraMemoryStreamInput* pDataStream = [[ImebraMemoryStreamInput alloc] initWithReadMemory:pDataMemory];
    ImebraStreamReader* pDataReader = [[ImebraStreamReader alloc] initWithInputStream:pDataStream];

    ImebraDataSet* pLoadedDataSet = [ImebraCodecFactory loadFromStream:pDataReader error:&pError];
    ImebraImage* pLoadedImage = [pLoadedDataSet getImage:0 error:&pError];

    // Compare the buffers. A little difference is allowed
    double differenceYBR = compareImages(*(imebra::Image*)(pYbrImage->m_Image), *(imebra::Image*)(pLoadedImage->m_Image));
    ASSERT_LE(differenceYBR, 1);
}

#endif

} // namespace tests

} // namespace imebra
