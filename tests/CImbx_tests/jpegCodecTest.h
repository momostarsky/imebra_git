#if !defined(imebraJpegCodecTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraJpegCodecTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class jpegCodecTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(jpegCodecTest);
	
	CPPUNIT_TEST(testBaseline);
	CPPUNIT_TEST(testLossless);
	CPPUNIT_TEST(testBaselineSubsampled);

	CPPUNIT_TEST_SUITE_END();

public:
	void testBaseline();
	void testBaselineSubsampled();
	void testLossless();
};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraJpegCodecTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)