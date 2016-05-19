/*
$fileHeader$
*/

#include "../include/imebra/lut.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include "../implementation/LUTImpl.h"

namespace imebra
{

LUT::LUT(std::shared_ptr<implementation::lut> pLut): m_pLut(pLut)
{
}

LUT::LUT(ReadingDataHandlerNumeric &descriptor, ReadingDataHandlerNumeric &data, const std::wstring &description, bool pixelRepresentation):
    m_pLut(std::make_shared<implementation::lut>(
               std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(descriptor.m_pDataHandler),
               std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(data.m_pDataHandler),
               description, pixelRepresentation))
{
}

LUT::~LUT()
{
}

std::wstring LUT::getDescription()
{
    return m_pLut->getDescription();
}

}

