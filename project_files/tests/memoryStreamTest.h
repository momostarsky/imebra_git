#if !defined(imebraMemoryStreamTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraMemoryStreamTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class memoryStreamTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(memoryStreamTest);
	
	CPPUNIT_TEST(test);
	CPPUNIT_TEST(testBytes);

	CPPUNIT_TEST_SUITE_END();

public:
	void test();

	void testBytes();

};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraMemoryStreamTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)