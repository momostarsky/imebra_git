#if !defined(imebraDicomDirTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraDicomDirTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class dicomDirTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(dicomDirTest);
	
	CPPUNIT_TEST(createDicomDir);

	CPPUNIT_TEST_SUITE_END();

public:
	void createDicomDir();
};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraDicomDirTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)