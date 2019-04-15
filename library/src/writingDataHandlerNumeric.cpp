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

#include "../include/imebra/writingDataHandlerNumeric.h"
#include "../include/imebra/readingDataHandlerNumeric.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace imebra
{

WritingDataHandlerNumeric::WritingDataHandlerNumeric(const std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase>& pDataHandler):
    WritingDataHandler(pDataHandler)
{
}

WritingDataHandlerNumeric::WritingDataHandlerNumeric(const WritingDataHandlerNumeric& source): WritingDataHandler(source)
{
}

WritingDataHandlerNumeric& WritingDataHandlerNumeric::operator=(const WritingDataHandlerNumeric& source)
{
    WritingDataHandler::operator =(source);
    return *this;
}

WritingDataHandlerNumeric::~WritingDataHandlerNumeric()
{
}

MutableMemory WritingDataHandlerNumeric::getMemory() const
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return MutableMemory(numericDataHandler->getMemory());
}

void WritingDataHandlerNumeric::assign(const char* source, size_t sourceSize)
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    numericDataHandler->getMemory()->assign((std::uint8_t*) source, sourceSize);
}

char* WritingDataHandlerNumeric::data(size_t* pDataSize) const
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    *pDataSize = numericDataHandler->getMemorySize();
    return (char*)numericDataHandler->getMemoryBuffer();
}

size_t WritingDataHandlerNumeric::data(char* destination, size_t destinationSize) const
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    size_t memorySize = numericDataHandler->getMemorySize();
    if(destination != 0 && destinationSize >= memorySize && memorySize != 0)
    {
        ::memcpy(destination, numericDataHandler->getMemoryBuffer(), memorySize);
    }
    return memorySize;
}

size_t WritingDataHandlerNumeric::getUnitSize() const
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return numericDataHandler->getUnitSize();
}

bool WritingDataHandlerNumeric::isSigned() const
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return numericDataHandler->isSigned();
}

bool WritingDataHandlerNumeric::isFloat() const
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return numericDataHandler->isFloat();
}

void WritingDataHandlerNumeric::copyFrom(const ReadingDataHandlerNumeric& source)
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return numericDataHandler->copyFrom(std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(source)));
}

}
