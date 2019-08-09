/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file VOILUT.cpp
    \brief Implementation of VOILUT.

*/


#include "../include/imebra/VOILUT.h"
#include "../include/imebra/dataSet.h"
#include "../implementation/VOILUTImpl.h"
#include "../include/imebra/lut.h"

namespace imebra
{

VOILUT::VOILUT(): Transform(std::make_shared<imebra::implementation::transforms::VOILUT>())
{
}

VOILUT::VOILUT(const VOILUT& source): Transform(source)
{
}

VOILUT& VOILUT::operator=(const VOILUT& source)
{
    m_pTransform = getTransformImplementation(source);
    return *this;
}

VOILUT::~VOILUT()
{
}

void VOILUT::setCenterWidth(double center, double width)
{
    IMEBRA_FUNCTION_START();

    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->setCenterWidth(center, width);

    IMEBRA_FUNCTION_END_LOG();
}

void VOILUT::setLUT(const LUT &lut)
{
    IMEBRA_FUNCTION_START();

    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->setLUT(lut.m_pLut);

    IMEBRA_FUNCTION_END_LOG();
}

void VOILUT::applyOptimalVOI(const Image& inputImage, std::uint32_t topLeftX, std::uint32_t topLeftY, std::uint32_t width, std::uint32_t height)
{
    IMEBRA_FUNCTION_START();

    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->applyOptimalVOI(getImageImplementation(inputImage), topLeftX, topLeftY, width, height);

    IMEBRA_FUNCTION_END_LOG();
}

double VOILUT::getCenter() const
{
    IMEBRA_FUNCTION_START();

    double center, width;
    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->getCenterWidth(&center, &width);
    return center;

    IMEBRA_FUNCTION_END_LOG();
}

double VOILUT::getWidth() const
{
    IMEBRA_FUNCTION_START();

    double center, width;
    ((imebra::implementation::transforms::VOILUT*)m_pTransform.get())->getCenterWidth(&center, &width);
    return width;

    IMEBRA_FUNCTION_END_LOG();
}

}
