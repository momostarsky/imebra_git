#if !defined(imebraDecimalStringHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraDecimalStringHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class decimalStringHandlerTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(decimalStringHandlerTest);
	
	CPPUNIT_TEST(decimalTest);

	CPPUNIT_TEST_SUITE_END();

public:
	void decimalTest();

};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraDecimalStringHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)