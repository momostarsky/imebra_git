/*
$fileHeader$
*/

/*! \file VOILUT_swig.cpp
    \brief Implementation of the VOILUT class for SWIG.

*/


#include "../include/imebra/VOILUT.h"
#include "../include/imebra/dataSet.h"
#include "../implementation/VOILUTImpl.h"

namespace imebra
{

VOILUT::VOILUT(const DataSet& dataset): Transform(std::make_shared<puntoexe::imebra::transforms::VOILUT>(dataset.m_pDataSet))
{
}

unsigned int VOILUT::getVOILUTId(unsigned int VOILUTNumber) const
{
    return (unsigned int) (((puntoexe::imebra::transforms::VOILUT*)m_pTransform.get())->getVOILUTId((std::uint32_t) VOILUTNumber));

}

std::wstring VOILUT::getVOILUTDescription(int VOILUTId) const
{
    return ((puntoexe::imebra::transforms::VOILUT*)m_pTransform.get())->getVOILUTDescription((std::uint32_t) VOILUTId);

}

void VOILUT::setVOILUT(int VOILUTId)
{
    ((puntoexe::imebra::transforms::VOILUT*)m_pTransform.get())->setVOILUT((std::uint32_t) VOILUTId);
}

void VOILUT::setCenterWidth(int center, int width)
{
    ((puntoexe::imebra::transforms::VOILUT*)m_pTransform.get())->setCenterWidth((std::int32_t) center, (std::int32_t) width);
}

void VOILUT::applyOptimalVOI(Image inputImage, unsigned int topLeftX, unsigned int topLeftY, unsigned int width, unsigned int height)
{
    ((puntoexe::imebra::transforms::VOILUT*)m_pTransform.get())->applyOptimalVOI(inputImage.m_pImage, (std::uint32_t) topLeftX, (std::uint32_t) topLeftY, (std::uint32_t) width, (std::uint32_t) height);
}

int VOILUT::getCenter() const
{
    std::int32_t center, width;
    ((puntoexe::imebra::transforms::VOILUT*)m_pTransform.get())->getCenterWidth(&center, &width);
    return (int)center;
}

int VOILUT::getWidth() const
{
    std::int32_t center, width;
    ((puntoexe::imebra::transforms::VOILUT*)m_pTransform.get())->getCenterWidth(&center, &width);
    return (int)width;
}

}
