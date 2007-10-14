#if !defined(imebraPaletteTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraPaletteTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class paletteTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(paletteTest);
	
	CPPUNIT_TEST(testPalette);

	CPPUNIT_TEST_SUITE_END();

public:
	void testPalette();
};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraPaletteTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)