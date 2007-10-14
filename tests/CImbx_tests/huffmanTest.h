#if !defined(imebraHuffmanTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraHuffmanTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class huffmanTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(huffmanTest);
	
	CPPUNIT_TEST(test);

	CPPUNIT_TEST_SUITE_END();

public:
	void test();
};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraJpegCodecTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)