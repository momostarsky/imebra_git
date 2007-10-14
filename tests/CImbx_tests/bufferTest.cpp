#include <cppunit/extensions/HelperMacros.h>
#include "bufferTest.h"

#include "../../imebra/include/imebra.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{

CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::bufferTest);


void bufferTest::testDefaultType()
{
	ptr<buffer> patientBuffer(new buffer(ptr<baseObject>(0)));
	CPPUNIT_ASSERT(patientBuffer->getDataType() == "OB");
}

void bufferTest::testReadWrite()
{
	ptr<buffer> patientBuffer(new buffer(ptr<baseObject>(0), "UL"));

	// get a data reading handler
	ptr<handlers::dataHandler> readingHandler0 = patientBuffer->getDataHandler(false);

	// get a writing handler and write something
	{
		ptr<handlers::dataHandler> writingHandler0 = patientBuffer->getDataHandler(true);
		writingHandler0->setSize(10);
		for(int writeNumbers = 0; writeNumbers < 10; ++writeNumbers)
		{
			writingHandler0->setSignedLongIncPointer(writeNumbers);
		}
	}

	// now, the first reading handler should still be empty
	CPPUNIT_ASSERT(readingHandler0->getSize() == 0);

	// Get a new reading handler
	ptr<handlers::dataHandler> readingHandler1 = patientBuffer->getDataHandler(false);

	// Get two different writing handlers
	ptr<handlers::dataHandler> writingHandler1 = patientBuffer->getDataHandler(true);
	ptr<handlers::dataHandler> writingHandler2 = patientBuffer->getDataHandler(true);

	// Get another reading handler
	ptr<handlers::dataHandler> readingHandler2 = patientBuffer->getDataHandler(false);

	// Check the values in all the new handlers first
	CPPUNIT_ASSERT(writingHandler1->getSize() == 10);
	CPPUNIT_ASSERT(writingHandler2->getSize() == 10);
	CPPUNIT_ASSERT(readingHandler1->getSize() == 10);
	CPPUNIT_ASSERT(readingHandler2->getSize() == 10);
	writingHandler1->setPointer(0);
	writingHandler2->setPointer(0);
	readingHandler1->setPointer(0);
	readingHandler2->setPointer(0);
	for(int checkValues = 0; checkValues < 10; ++checkValues)
	{
		CPPUNIT_ASSERT(writingHandler1->getSignedLongIncPointer() == checkValues);
		CPPUNIT_ASSERT(writingHandler2->getSignedLongIncPointer() == checkValues);
		CPPUNIT_ASSERT(readingHandler1->getSignedLongIncPointer() == checkValues);
		CPPUNIT_ASSERT(readingHandler2->getSignedLongIncPointer() == checkValues);
	}

	// Change the content in the first writing handler
	writingHandler1->setSize(20);
	CPPUNIT_ASSERT(writingHandler1->getSize() == 20);
	for(int writeValues = 0; writeValues < 20; ++writeValues)
	{
		writingHandler1->setSignedLongIncPointer(writeValues+100);
	}

	// Check the other data handlers. They should still have the original values
	CPPUNIT_ASSERT(writingHandler2->getSize() == 10);
	CPPUNIT_ASSERT(readingHandler1->getSize() == 10);
	CPPUNIT_ASSERT(readingHandler2->getSize() == 10);
	writingHandler2->setPointer(0);
	readingHandler1->setPointer(0);
	readingHandler2->setPointer(0);
	for(int checkValues = 0; checkValues < 10; ++checkValues)
	{
		CPPUNIT_ASSERT(writingHandler2->getSignedLongIncPointer() == checkValues);
		CPPUNIT_ASSERT(readingHandler1->getSignedLongIncPointer() == checkValues);
		CPPUNIT_ASSERT(readingHandler2->getSignedLongIncPointer() == checkValues);
	}

	// Now modify the second writing handler
	writingHandler2->setSize(5);
	CPPUNIT_ASSERT(writingHandler2->getSize() == 5);
	writingHandler2->setPointer(0);
	for(int writeValues = 0; writeValues < 5; ++writeValues)
	{
		writingHandler2->setSignedLongIncPointer(writeValues+200);
	}

	// Release the first writing handler, then recheck the values in the other handlers
	writingHandler1 = ptr<handlers::dataHandler>(0);
	CPPUNIT_ASSERT(readingHandler1->getSize() == 10);
	CPPUNIT_ASSERT(readingHandler2->getSize() == 10);
	readingHandler1->setPointer(0);
	readingHandler2->setPointer(0);
	for(int checkValues = 0; checkValues < 10; ++checkValues)
	{
		CPPUNIT_ASSERT(readingHandler1->getSignedLongIncPointer() == checkValues);
		CPPUNIT_ASSERT(readingHandler2->getSignedLongIncPointer() == checkValues);
	}
	CPPUNIT_ASSERT(writingHandler2->getSize() == 5);
	writingHandler2->setPointer(0);
	for(int checkValues = 0; checkValues < 5; ++checkValues)
	{
		CPPUNIT_ASSERT(writingHandler2->getSignedLongIncPointer() == checkValues+200);
	}

	// Get a reading handler. It should have the value written by writingHandler1
	ptr<handlers::dataHandler> readingHandler3 = patientBuffer->getDataHandler(false);
	CPPUNIT_ASSERT(readingHandler3->getSize() == 20);
	for(int checkValues = 0; checkValues < 20; ++checkValues)
	{
		CPPUNIT_ASSERT(readingHandler3->getSignedLongIncPointer() == checkValues + 100);
	}

	// Release a reading handler. It shouldn't change the values in the buffer
	readingHandler1 = ptr<handlers::dataHandler>(0);
	ptr<handlers::dataHandler> readingHandler4 = patientBuffer->getDataHandler(false);
	CPPUNIT_ASSERT(readingHandler4->getSize() == 20);
	for(int checkValues = 0; checkValues < 20; ++checkValues)
	{
		CPPUNIT_ASSERT(readingHandler4->getSignedLongIncPointer() == checkValues + 100);
	}

	// Release the second writing handler. It should change the buffer, but already
	//  existing handlers should continue with their values
	writingHandler2 = ptr<handlers::dataHandler>(0);
	ptr<handlers::dataHandler> writingHandler3 = patientBuffer->getDataHandler(true);
	CPPUNIT_ASSERT(writingHandler3->getSize() == 5);
	for(int checkValues = 0; checkValues < 5; ++checkValues)
	{
		CPPUNIT_ASSERT(writingHandler3->getSignedLongIncPointer() == checkValues+200);
	}
	writingHandler3 = ptr<handlers::dataHandler>(0);

	// ReadingHandler2 still exist. Check its values
	CPPUNIT_ASSERT(readingHandler2->getSize() == 10);
	readingHandler2->setPointer(0);
	for(int checkValues = 0; checkValues < 10; ++checkValues)
	{
		CPPUNIT_ASSERT(readingHandler2->getSignedLongIncPointer() == checkValues);
	}
	readingHandler2 = ptr<handlers::dataHandler>(0);

	// Get a reading handler and check it. It should have the values of writingHandler2
	ptr<handlers::dataHandler> readingHandler5 = patientBuffer->getDataHandler(false);
	CPPUNIT_ASSERT(readingHandler5->getSize() == 5);
	for(int checkValues = 0; checkValues < 5; ++checkValues)
	{
		CPPUNIT_ASSERT(readingHandler5->getSignedLongIncPointer() == checkValues+200);
	}
}

void bufferTest::testOddLength() 
{
	ptr<buffer> patientBuffer(new buffer(ptr<baseObject>(0), "OB"));
	ptr<handlers::dataHandler> writingHandler = patientBuffer->getDataHandler(true);
	
	// Write 3 numbers
	writingHandler->setSize(3);
	writingHandler->setUnsignedLongIncPointer(10);
	writingHandler->setUnsignedLongIncPointer(20);
	writingHandler->setUnsignedLongIncPointer(30);
	writingHandler = ptr<handlers::dataHandler>(0);

	ptr<handlers::dataHandler> readingHandler = patientBuffer->getDataHandler(false);
	CPPUNIT_ASSERT(readingHandler->getSize() == 4);
	CPPUNIT_ASSERT(readingHandler->getUnsignedLongIncPointer() == 10);
	CPPUNIT_ASSERT(readingHandler->getUnsignedLongIncPointer() == 20);
	CPPUNIT_ASSERT(readingHandler->getUnsignedLongIncPointer() == 30);
	CPPUNIT_ASSERT(readingHandler->getUnsignedLongIncPointer() == 0);
}

} // namespace tests

} // namespace imebra

} // namespace puntoexe