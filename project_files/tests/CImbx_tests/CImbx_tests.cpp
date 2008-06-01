// imebra_tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <fstream>
#include "../../imebra/include/imebra.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


int main(int argc, char* argv[])
{

	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest( registry.makeTest() );
	bool wasSuccessful = runner.run( "", false );
	return wasSuccessful ? 0 : 1;
}

