#if !defined(imebraBitTransformTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraBitTransformTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class bitTransformTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(bitTransformTest);
	
	CPPUNIT_TEST(testBitTransform);

	CPPUNIT_TEST_SUITE_END();

public:
	void testBitTransform();
};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraBitTransformTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)