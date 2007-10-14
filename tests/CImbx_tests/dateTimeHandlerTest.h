#if !defined(imebraDateTimeHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraDateTimeHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class dateTimeHandlerTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(dateTimeHandlerTest);
	
	CPPUNIT_TEST(dateTest);
	CPPUNIT_TEST(timeTest);
	CPPUNIT_TEST(dateTimeTest);

	CPPUNIT_TEST_SUITE_END();

public:
	void dateTest();
	void timeTest();
	void dateTimeTest();

};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraDateTimeHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)