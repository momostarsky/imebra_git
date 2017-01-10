/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file codecFactory.cpp
    \brief Implementation of the codecFactory class.

*/

#include "codecFactoryImpl.h"
#include "configurationImpl.h"
#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "codecImpl.h"
#include "jpegCodecImpl.h"
#include "dicomCodecImpl.h"
#include "../include/imebra/exceptions.h"

namespace imebra
{

namespace implementation
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
    IMEBRA_FUNCTION_START();

    registerCodec(std::make_shared<dicomCodec>());
    registerCodec(std::make_shared<jpegCodec>());


    IMEBRA_FUNCTION_END();
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
void codecFactory::registerCodec(std::shared_ptr<codec> pCodec)
{
    IMEBRA_FUNCTION_START();

	if(pCodec == 0)
	{
		return;
	}

	m_codecsList.push_back(pCodec);

	IMEBRA_FUNCTION_END();
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
std::shared_ptr<codec> codecFactory::getCodec(const std::string& transferSyntax)
{
    IMEBRA_FUNCTION_START();

	std::shared_ptr<codecFactory> pFactory(getCodecFactory());

	for(std::list<std::shared_ptr<codec> >::iterator scanCodecs=pFactory->m_codecsList.begin(); scanCodecs!=pFactory->m_codecsList.end(); ++scanCodecs)
	{
		if((*scanCodecs)->canHandleTransferSyntax(transferSyntax))
		{
			return (*scanCodecs)->createCodec();
		}
	}

    IMEBRA_THROW(DataSetUnknownTransferSyntaxError, "None of the codecs support the specified transfer syntax");

	IMEBRA_FUNCTION_END();
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
std::shared_ptr<codecFactory> codecFactory::getCodecFactory()
{
    IMEBRA_FUNCTION_START();

    // Violation to requirement REQ_MAKE_SHARED due to protected constructor
    static std::shared_ptr<codecFactory> m_codecFactory(new codecFactory());

	return m_codecFactory;

    IMEBRA_FUNCTION_END();
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
std::shared_ptr<dataSet> codecFactory::load(std::shared_ptr<streamReader> pStream, std::uint32_t maxSizeBufferLoad /* = 0xffffffff */)
{
    IMEBRA_FUNCTION_START();

	// Copy the list of codecs in a local list so we don't have
	//  to lock the object for a long time
	///////////////////////////////////////////////////////////
	std::list<std::shared_ptr<codec> > localCodecsList;
	std::shared_ptr<codecFactory> pFactory(getCodecFactory());
	{
		for(std::list<std::shared_ptr<codec> >::iterator scanCodecs=pFactory->m_codecsList.begin(); scanCodecs!=pFactory->m_codecsList.end(); ++scanCodecs)
		{
			std::shared_ptr<codec> copyCodec((*scanCodecs)->createCodec());
			localCodecsList.push_back(copyCodec);
		}
	}

	std::shared_ptr<dataSet> pDataSet;
	for(std::list<std::shared_ptr<codec> >::iterator scanCodecs=localCodecsList.begin(); scanCodecs != localCodecsList.end() && pDataSet == 0; ++scanCodecs)
	{
		try
		{
			return (*scanCodecs)->read(pStream, maxSizeBufferLoad);
		}
        catch(CodecWrongFormatError& /* e */)
		{
            exceptionsManagerGetter::getExceptionsManagerGetter().getExceptionsManager().getMessage(); // Reset the messages stack
			continue;
		}
	}

	if(pDataSet == 0)
	{
        IMEBRA_THROW(CodecWrongFormatError, "none of the codecs recognized the file format");
	}

	return pDataSet;

	IMEBRA_FUNCTION_END();
}


void codecFactory::setMaximumImageSize(const uint32_t maximumWidth, const uint32_t maximumHeight)
{
    IMEBRA_FUNCTION_START();

    m_maximumImageWidth = maximumWidth;
    m_maximumImageHeight = maximumHeight;

    IMEBRA_FUNCTION_END();
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

} // namespace implementation

} // namespace imebra

