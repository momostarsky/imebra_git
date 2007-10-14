#if !defined(imebraTransactionTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraTransactionTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <cppunit/TestCase.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

class transactionTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(transactionTest);
	
	CPPUNIT_TEST(testOneTransaction);

	CPPUNIT_TEST(testNestedTransactions0);
	CPPUNIT_TEST(testNestedTransactions1);

	CPPUNIT_TEST(testNestedTransactionsFail0);
	CPPUNIT_TEST(testNestedTransactionsFail1);

	CPPUNIT_TEST_SUITE_END();

public:
	void testOneTransaction();
	void testNestedTransactions0();
	void testNestedTransactions1();
	void testNestedTransactionsFail0();
	void testNestedTransactionsFail1();

};

} // namespace tests

} // namespace imebra

} // namespace puntoexe


#endif // #if !defined(imebraTransactionTest_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)