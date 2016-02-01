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

VOILUT::VOILUT(const DataSet& dataset): Transform(std::make_shared<imebra::implementation::transforms::VOILUT>(dataset.m_pDataSet))
{
}

std::uint32_t VOILUT::getVOILUTId(std::uint32_t VOILUTNumber) const
{
    return ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->getVOILUTId(VOILUTNumber);

}

std::wstring VOILUT::getVOILUTDescription(std::uint32_t VOILUTId) const
{
    return ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->getVOILUTDescription(VOILUTId);

}

void VOILUT::setVOILUT(std::uint32_t VOILUTId)
{
    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->setVOILUT(VOILUTId);
}

void VOILUT::setCenterWidth(std::int32_t center, std::int32_t width)
{
    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->setCenterWidth(center, width);
}

void VOILUT::applyOptimalVOI(Image inputImage, std::uint32_t topLeftX, std::uint32_t topLeftY, std::uint32_t width, std::uint32_t height)
{
    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->applyOptimalVOI(inputImage.m_pImage, topLeftX, topLeftY, width, height);
}

double VOILUT::getCenter() const
{
    double center, width;
    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->getCenterWidth(&center, &width);
    return center;
}

double VOILUT::getWidth() const
{
    double center, width;
    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->getCenterWidth(&center, &width);
    return width;
}

}
