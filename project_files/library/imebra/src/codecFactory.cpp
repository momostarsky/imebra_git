/*
$fileHeader$
*/

/*! \file codecFactory.cpp
    \brief Implementation of the codecFactory class.

*/

#include "../include/codecFactory.h"
#include "../../base/include/configuration.h"
#include "../../base/include/exception.h"
#include "../../base/include/streamReader.h"
#include "../include/codec.h"
#include "../include/jpegCodec.h"
#include "../include/dicomCodec.h"


namespace puntoexe
{

namespace imebra
{

namespace codecs
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Force the creation of the codec factory before main()
//  starts.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
static codecFactory::forceCodecFactoryCreation forceCreation;


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
codecFactory::codecFactory(): m_maximumImageWidth(MAXIMUM_IMAGE_WIDTH), m_maximumImageHeight(MAXIMUM_IMAGE_HEIGHT)
{
    registerCodec(new dicomCodec());
    registerCodec(new jpegCodec());
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Register a codec
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void codecFactory::registerCodec(ptr<codec> pCodec)
{
	PUNTOEXE_FUNCTION_START(L"codecFactory::registerCodec");

	if(pCodec == 0)
	{
		return;
	}

	lockObject lockAccess(this);

	m_codecsList.push_back(pCodec);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve a codec that can handle the specified
//  transfer syntax
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<codec> codecFactory::getCodec(std::wstring transferSyntax)
{
	PUNTOEXE_FUNCTION_START(L"codecFactory::getCodec");

	ptr<codecFactory> pFactory(getCodecFactory());
	lockObject lockAccess(pFactory.get());

	for(std::list<ptr<codec> >::iterator scanCodecs=pFactory->m_codecsList.begin(); scanCodecs!=pFactory->m_codecsList.end(); ++scanCodecs)
	{
		if((*scanCodecs)->canHandleTransferSyntax(transferSyntax))
		{
			return (*scanCodecs)->createCodec();
		}
	}

	ptr<codec> emptyCodec;
	return emptyCodec;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the only instance of the codec factory
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<codecFactory> codecFactory::getCodecFactory()
{
	static ptr<codecFactory> m_codecFactory(new codecFactory);
	return m_codecFactory;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Load the data from the specified stream and build a
//  dicomSet structure
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<dataSet> codecFactory::load(ptr<streamReader> pStream, std::uint32_t maxSizeBufferLoad /* = 0xffffffff */)
{
	PUNTOEXE_FUNCTION_START(L"codecFactory::load");

	// Copy the list of codecs in a local list so we don't have
	//  to lock the object for a long time
	///////////////////////////////////////////////////////////
	std::list<ptr<codec> > localCodecsList;
	ptr<codecFactory> pFactory(getCodecFactory());
	{
		lockObject lockAccess(pFactory.get());
		for(std::list<ptr<codec> >::iterator scanCodecs=pFactory->m_codecsList.begin(); scanCodecs!=pFactory->m_codecsList.end(); ++scanCodecs)
		{
			ptr<codec> copyCodec((*scanCodecs)->createCodec());
			localCodecsList.push_back(copyCodec);
		}
	}

	ptr<dataSet> pDataSet;
	for(std::list<ptr<codec> >::iterator scanCodecs=localCodecsList.begin(); scanCodecs != localCodecsList.end() && pDataSet == 0; ++scanCodecs)
	{
		try
		{
			return (*scanCodecs)->read(pStream, maxSizeBufferLoad);
		}
		catch(codecExceptionWrongFormat& /* e */)
		{
			exceptionsManager::getMessage(); // Reset the messages stack
			continue;
		}
	}

	if(pDataSet == 0)
	{
		PUNTOEXE_THROW(codecExceptionWrongFormat, "none of the codecs recognized the file format");
	}

	return pDataSet;

	PUNTOEXE_FUNCTION_END();
}


void codecFactory::setMaximumImageSize(const uint32_t maximumWidth, const uint32_t maximumHeight)
{
    m_maximumImageWidth = maximumWidth;
    m_maximumImageHeight = maximumHeight;
}


std::uint32_t codecFactory::getMaximumImageWidth()
{
    return m_maximumImageWidth;
}

std::uint32_t codecFactory::getMaximumImageHeight()
{
    return m_maximumImageHeight;
}

} // namespace codecs

} // namespace imebra

} // namespace puntoexe

