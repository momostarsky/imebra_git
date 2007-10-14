#include <cppunit/extensions/HelperMacros.h>
#include "transactionTest.h"

#include "../../imebra/include/imebra.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{

CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::transactionTest);


void transactionTest::testOneTransaction()
{
	ptr<dataSet> newDataSet(new dataSet);
	tCharsetsList charsets;
	charsets.push_back(L"ISO_IR 100");
	newDataSet->setCharsetsList(&charsets);

	// Test without transactions
	newDataSet->setUnicodeString(20, 0, 10, 0, L"test 0", "PN");
	newDataSet->setUnicodeString(20, 0, 11, 0, L"test 1", "PN");
	newDataSet->setUnicodeString(20, 0, 12, 0, L"test 2", "PN");
	newDataSet->setUnicodeString(20, 0, 13, 0, L"test 3", "PN");

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 10, 0) == L"test 0");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 11, 0) == L"test 1");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 12, 0) == L"test 2");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 13, 0) == L"test 3");

	// Test one transaction
	IMEBRA_TRANSACTION_START();

		newDataSet->setUnicodeString(10, 0, 10, 0, L"test 0", "PN");
		newDataSet->setUnicodeString(10, 0, 11, 0, L"test 1", "PN");
		newDataSet->setUnicodeString(10, 0, 12, 0, L"test 2", "PN");
		newDataSet->setUnicodeString(10, 0, 13, 0, L"test 3", "PN");

		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 10, 0) != L"test 0");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 11, 0) != L"test 1");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 12, 0) != L"test 2");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 13, 0) != L"test 3");

	IMEBRA_TRANSACTION_END();

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 10, 0) == L"test 0");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 11, 0) == L"test 1");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 12, 0) == L"test 2");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 13, 0) == L"test 3");
}

void transactionTest::testNestedTransactions0()
{
	ptr<dataSet> newDataSet(new dataSet);
	tCharsetsList charsets;
	charsets.push_back(L"ISO_IR 100");
	newDataSet->setCharsetsList(&charsets);

	IMEBRA_TRANSACTION_START();

		newDataSet->setUnicodeString(10, 0, 10, 0, L"test 0", "PN");
		newDataSet->setUnicodeString(10, 0, 11, 0, L"test 1", "PN");
		newDataSet->setUnicodeString(10, 0, 12, 0, L"test 2", "PN");
		newDataSet->setUnicodeString(10, 0, 13, 0, L"test 3", "PN");

		IMEBRA_TRANSACTION_START();

			newDataSet->setUnicodeString(20, 0, 10, 0, L"test 4", "PN");
			newDataSet->setUnicodeString(20, 0, 11, 0, L"test 5", "PN");
			newDataSet->setUnicodeString(20, 0, 12, 0, L"test 6", "PN");
			newDataSet->setUnicodeString(20, 0, 13, 0, L"test 7", "PN");

			CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 10, 0) != L"test 4");
			CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 11, 0) != L"test 5");
			CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 12, 0) != L"test 6");
			CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 13, 0) != L"test 7");
		
		IMEBRA_TRANSACTION_END();

		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 10, 0) != L"test 0");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 11, 0) != L"test 1");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 12, 0) != L"test 2");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 13, 0) != L"test 3");

		CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 10, 0) != L"test 4");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 11, 0) != L"test 5");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 12, 0) != L"test 6");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 13, 0) != L"test 7");
	
	IMEBRA_TRANSACTION_END();

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 10, 0) == L"test 0");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 11, 0) == L"test 1");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 12, 0) == L"test 2");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 13, 0) == L"test 3");

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 10, 0) == L"test 4");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 11, 0) == L"test 5");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 12, 0) == L"test 6");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 13, 0) == L"test 7");
}

void transactionTest::testNestedTransactions1()
{
	ptr<dataSet> newDataSet(new dataSet);
	tCharsetsList charsets;
	charsets.push_back(L"ISO_IR 100");
	newDataSet->setCharsetsList(&charsets);

	// Test one transaction
	IMEBRA_TRANSACTION_START();

		newDataSet->setUnicodeString(10, 0, 10, 0, L"test 0", "PN");
		newDataSet->setUnicodeString(10, 0, 11, 0, L"test 1", "PN");
		newDataSet->setUnicodeString(10, 0, 12, 0, L"test 2", "PN");
		newDataSet->setUnicodeString(10, 0, 13, 0, L"test 3", "PN");

		IMEBRA_COMMIT_TRANSACTION_START();

			newDataSet->setUnicodeString(20, 0, 10, 0, L"test 4", "PN");
			newDataSet->setUnicodeString(20, 0, 11, 0, L"test 5", "PN");
			newDataSet->setUnicodeString(20, 0, 12, 0, L"test 6", "PN");
			newDataSet->setUnicodeString(20, 0, 13, 0, L"test 7", "PN");

			CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 10, 0) != L"test 4");
			CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 11, 0) != L"test 5");
			CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 12, 0) != L"test 6");
			CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 13, 0) != L"test 7");
		
		IMEBRA_TRANSACTION_END();

		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 10, 0) != L"test 0");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 11, 0) != L"test 1");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 12, 0) != L"test 2");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 13, 0) != L"test 3");

		CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 10, 0) == L"test 4");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 11, 0) == L"test 5");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 12, 0) == L"test 6");
		CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 13, 0) == L"test 7");
	
	IMEBRA_TRANSACTION_END();

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 10, 0) == L"test 0");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 11, 0) == L"test 1");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 12, 0) == L"test 2");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 13, 0) == L"test 3");

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 10, 0) == L"test 4");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 11, 0) == L"test 5");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 12, 0) == L"test 6");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 13, 0) == L"test 7");
}

void transactionTest::testNestedTransactionsFail0()
{
	ptr<dataSet> newDataSet(new dataSet);
	tCharsetsList charsets;
	charsets.push_back(L"ISO_IR 6");
	newDataSet->setCharsetsList(&charsets);

	newDataSet->setUnicodeString(10, 0, 10, 0, L"initial test 0", "PN");
	newDataSet->setUnicodeString(10, 0, 11, 0, L"initial test 1", "PN");
	newDataSet->setUnicodeString(10, 0, 12, 0, L"initial test 2", "PN");
	newDataSet->setUnicodeString(10, 0, 13, 0, L"initial test 3", "PN");

	newDataSet->setUnicodeString(20, 0, 10, 0, L"initial test 4", "PN");
	newDataSet->setUnicodeString(20, 0, 11, 0, L"initial test 5", "PN");
	newDataSet->setUnicodeString(20, 0, 12, 0, L"initial test 6", "PN");
	newDataSet->setUnicodeString(20, 0, 13, 0, L"initial test 7", "PN");

	IMEBRA_TRANSACTION_START();

		IMEBRA_TRANSACTION_START();

			newDataSet->setUnicodeString(20, 0, 10, 0, L"test 4", "PN");
			newDataSet->setUnicodeString(20, 0, 11, 0, L"test 5", "PN");
			newDataSet->setUnicodeString(20, 0, 12, 0, L"test 6", "PN");
			newDataSet->setUnicodeString(20, 0, 13, 0, L"test 7", "PN");
		
		IMEBRA_TRANSACTION_END();

		newDataSet->setUnicodeString(10, 0, 10, 0, L"test 0", "PN");
		newDataSet->setUnicodeString(10, 0, 11, 0, L"test 1", "PN");
		newDataSet->setUnicodeString(10, 0, 12, 0, L"\0x420\x062a\x062b^\0x400\0x410\x0628\x062a", "PN");
		newDataSet->setUnicodeString(10, 0, 13, 0, L"test 3", "PN");

		IMEBRA_TRANSACTION_ABORT();

	IMEBRA_TRANSACTION_END();

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 10, 0) == L"initial test 0");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 11, 0) == L"initial test 1");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 12, 0) == L"initial test 2");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 13, 0) == L"initial test 3");

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 10, 0) == L"initial test 4");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 11, 0) == L"initial test 5");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 12, 0) == L"initial test 6");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 13, 0) == L"initial test 7");
}

void transactionTest::testNestedTransactionsFail1()
{
	ptr<dataSet> newDataSet(new dataSet);
	tCharsetsList charsets;
	charsets.push_back(L"ISO_IR 100");
	newDataSet->setCharsetsList(&charsets);

	newDataSet->setUnicodeString(10, 0, 10, 0, L"initial test 0", "PN");
	newDataSet->setUnicodeString(10, 0, 11, 0, L"initial test 1", "PN");
	newDataSet->setUnicodeString(10, 0, 12, 0, L"initial test 2", "PN");
	newDataSet->setUnicodeString(10, 0, 13, 0, L"initial test 3", "PN");

	newDataSet->setUnicodeString(20, 0, 10, 0, L"initial test 4", "PN");
	newDataSet->setUnicodeString(20, 0, 11, 0, L"initial test 5", "PN");
	newDataSet->setUnicodeString(20, 0, 12, 0, L"initial test 6", "PN");
	newDataSet->setUnicodeString(20, 0, 13, 0, L"initial test 7", "PN");

	try
	{
		IMEBRA_TRANSACTION_START();

			IMEBRA_COMMIT_TRANSACTION_START();

				newDataSet->setUnicodeString(20, 0, 10, 0, L"test 4", "PN");
				newDataSet->setUnicodeString(20, 0, 11, 0, L"test 5", "PN");
				newDataSet->setUnicodeString(20, 0, 12, 0, L"test 6", "PN");
				newDataSet->setUnicodeString(20, 0, 13, 0, L"test 7", "PN");

			IMEBRA_TRANSACTION_END()

			newDataSet->setUnicodeString(10, 0, 10, 0, L"test 0", "PN");
			newDataSet->setUnicodeString(10, 0, 11, 0, L"test 1", "PN");
			newDataSet->setUnicodeString(10, 0, 12, 0, L"\0x420\x062a\x062b^\0x400\0x410\x0628\x062a", "PN");
			newDataSet->setUnicodeString(10, 0, 13, 0, L"test 3", "PN");

			PUNTOEXE_THROW(std::runtime_error, "test abort");

		IMEBRA_TRANSACTION_END();
	}
	catch(std::runtime_error&)
	{
		std::wstring message = puntoexe::exceptionsManager::getMessage();
		CPPUNIT_ASSERT(message.find(L"test abort") != std::string::npos);
	}

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 10, 0) == L"initial test 0");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 11, 0) == L"initial test 1");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 12, 0) == L"initial test 2");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(10, 0, 13, 0) == L"initial test 3");

	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 10, 0) == L"test 4");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 11, 0) == L"test 5");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 12, 0) == L"test 6");
	CPPUNIT_ASSERT(newDataSet->getUnicodeString(20, 0, 13, 0) == L"test 7");
}


} // namespace tests

} // namespace imebra

} // namespace puntoexe