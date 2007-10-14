#include <cppunit/extensions/HelperMacros.h>
#include "ageStringHandlerTest.h"

#include "../../imebra/include/imebra.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{

CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::ageStringHandlerTest);



void ageStringHandlerTest::ageTest()
{
	ptr<data> tag(new data(ptr<baseObject>(0)));
	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "AS");
		hTag->setSize(1);

		hTag->setDouble(0.01);
		std::wstring ageString = hTag->getUnicodeString();
		CPPUNIT_ASSERT(ageString == L"003D");

		hTag->setDouble(0.2);
		ageString = hTag->getUnicodeString();
		CPPUNIT_ASSERT(ageString == L"010W");

		hTag->setDouble(0.9);
		ageString = hTag->getUnicodeString();
		CPPUNIT_ASSERT(ageString == L"010M");

		hTag->setDouble(0.5);
		ageString = hTag->getUnicodeString();
		CPPUNIT_ASSERT(ageString == L"006M");

		hTag->setDouble(2.3);
		ageString = hTag->getUnicodeString();
		CPPUNIT_ASSERT(ageString == L"002Y");
		imbxUint32 ageInt = hTag->getUnsignedLong();
		CPPUNIT_ASSERT(ageInt == 2);
	}
}



} // namespace tests

} // namespace imebra

} // namespace puntoexe