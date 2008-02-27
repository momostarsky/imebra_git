// imebra_tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <fstream>
#include "../../imebra/include/imebra.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


int main(int argc, char* argv[])
{
	puntoexe::ptr<puntoexe::stream> readStream(new puntoexe::stream);
	readStream->openFile(L"F:\\dicomImages\\waveforms\\39da47b8.dcm", std::ios::in);
	puntoexe::ptr<puntoexe::streamReader> reader(new puntoexe::streamReader(readStream));
	puntoexe::ptr<puntoexe::imebra::codecs::codecFactory> factory(puntoexe::imebra::codecs::codecFactory::getCodecFactory());
	puntoexe::ptr<puntoexe::imebra::dataSet> dataSet(factory->load(reader));
	
	{
		std::ofstream waveformLog;
		waveformLog.open("c:\\waveform.txt");
		for(imbxUint32 waveformId(0); ; ++waveformId)
		{
			puntoexe::ptr<puntoexe::imebra::waveform> waveform(dataSet->getWaveform(waveformId));
			if(waveform == 0)
			{
				break;
			}
			waveformLog << "----WAVEFORM----\n";
			waveformLog << "ID: " << waveformId << "\n";

			imbxUint32 numChannels(waveform->getChannels());
			for(imbxUint32 scanChannels(0); scanChannels != numChannels; ++scanChannels)
			{
				waveformLog << "    Channel----\n";
				waveformLog << "    id " << scanChannels << "\n";

				puntoexe::ptr<puntoexe::imebra::handlers::dataHandler> waveformHandler = waveform->getIntegerData(scanChannels);
				imbxUint32 numSamples = waveformHandler->getSize();
				imbxUint32 waveSize(waveformHandler->getSize());
				while(numSamples-- != 0)
				{
					waveformLog << waveformHandler->getSignedLongIncPointer() << "\n";
				}
			}
		}
	}

	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest( registry.makeTest() );
	bool wasSuccessful = runner.run( "", false );
	return wasSuccessful ? 0 : 1;
}

