/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandler.cpp
    \brief Implementation of the classes ReadingDataHandler & WritingDataHandler.
*/

#include "../include/imebra/readingDataHandlerNumeric.h"
#include "../include/imebra/writingDataHandlerNumeric.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace imebra
{

ReadingDataHandlerNumeric::ReadingDataHandlerNumeric(const std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase>& pDataHandler):
    ReadingDataHandler(pDataHandler)
{
}

ReadingDataHandlerNumeric::ReadingDataHandlerNumeric(const ReadingDataHandlerNumeric& source): ReadingDataHandler(source)
{
}

ReadingDataHandlerNumeric& ReadingDataHandlerNumeric::operator=(const ReadingDataHandlerNumeric& source)
{
    ReadingDataHandler::operator =(source);
    return *this;
}

ReadingDataHandlerNumeric::~ReadingDataHandlerNumeric()
{
}

const Memory ReadingDataHandlerNumeric::getMemory() const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return Memory(numericDataHandler->getMemory());
}

size_t ReadingDataHandlerNumeric::data(char* destination, size_t destinationSize) const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    size_t memorySize = numericDataHandler->getMemorySize();
    if(destination != 0 && destinationSize >= memorySize && memorySize != 0)
    {
        ::memcpy(destination, numericDataHandler->getMemoryBuffer(), memorySize);
    }
    return memorySize;
}

const char* ReadingDataHandlerNumeric::data(size_t* pDataSize) const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    *pDataSize = numericDataHandler->getMemorySize();
    return (const char*)numericDataHandler->getMemoryBuffer();
}

size_t ReadingDataHandlerNumeric::getUnitSize() const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return numericDataHandler->getUnitSize();
}

bool ReadingDataHandlerNumeric::isSigned() const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return numericDataHandler->isSigned();
}

bool ReadingDataHandlerNumeric::isFloat() const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return numericDataHandler->isFloat();
}

void ReadingDataHandlerNumeric::copyTo(const WritingDataHandlerNumeric& destination)
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return numericDataHandler->copyTo(std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(destination)));
}

}
