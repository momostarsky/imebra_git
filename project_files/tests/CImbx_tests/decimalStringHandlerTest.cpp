#include <cppunit/extensions/HelperMacros.h>
#include "decimalStringHandlerTest.h"

#include "../../imebra/include/imebra.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{

CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::decimalStringHandlerTest);



void decimalStringHandlerTest::decimalTest()
{
	ptr<data> tag(new data(ptr<baseObject>(0)));
	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "DS");
		hTag->setSize(1);

		hTag->setDouble(0, 0.000001);
		std::wstring decimalString = hTag->getUnicodeString(0);
		CPPUNIT_ASSERT(decimalString == L"1e-006" || decimalString == L"1e-06" || decimalString == L"1e-6");
		double decimal = hTag->getDouble(0);
		CPPUNIT_ASSERT(decimal > 0.0000009 && decimal < 0.0000011);
	}
}



} // namespace tests

} // namespace imebra

} // namespace puntoexe