#if !defined(imebraBufferTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraBufferTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class bufferTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(bufferTest);
	
	CPPUNIT_TEST(testDefaultType);
	CPPUNIT_TEST(testReadWrite);
	CPPUNIT_TEST(testOddLength);

	CPPUNIT_TEST_SUITE_END();

public:
	void testDefaultType();

	void testReadWrite();

	void testOddLength();
};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraBufferTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)