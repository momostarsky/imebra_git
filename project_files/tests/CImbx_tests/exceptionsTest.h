#if !defined(imebraExceptionsTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraExceptionsTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class exceptionsTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(exceptionsTest);
	
	CPPUNIT_TEST(testExceptions);

	CPPUNIT_TEST_SUITE_END();

public:
	void testExceptions();
};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraExceptionsTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)