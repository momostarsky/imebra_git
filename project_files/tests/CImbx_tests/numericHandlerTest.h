#if !defined(imebraNumericHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraNumericHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class numericHandlerTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(numericHandlerTest);
	
	CPPUNIT_TEST(interleavedCopy);

	CPPUNIT_TEST(stringConversion);

	CPPUNIT_TEST_SUITE_END();

public:
	void interleavedCopy();
	void stringConversion();

};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraNumericHandlerTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)