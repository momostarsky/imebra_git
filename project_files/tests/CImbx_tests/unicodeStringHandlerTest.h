#if !defined(imebraUnicodeStringHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraUnicodeStringHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class unicodeStringHandlerTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(unicodeStringHandlerTest);
	
	CPPUNIT_TEST(unicodeTest);

	CPPUNIT_TEST(iso2022Test);

	CPPUNIT_TEST_SUITE_END();

public:
	void unicodeTest();
	void iso2022Test();

};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraUnicodeStringHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)