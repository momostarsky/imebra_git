#if !defined(imebraDataSetTest_5CBE4806_5E5B_45c0_A43B_4A8BED58EB53__INCLUDED_)
#define imebraDataSetTest_5CBE4806_5E5B_45c0_A43B_4A8BED58EB53__INCLUDED_


#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class dataSetTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(dataSetTest);
	
	CPPUNIT_TEST(testFragmentation);

	CPPUNIT_TEST_SUITE_END();

public:
	void testFragmentation();

};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraDataSetTest_5CBE4806_5E5B_45c0_A43B_4A8BED58EB53__INCLUDED_)