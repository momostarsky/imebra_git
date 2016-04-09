#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>


namespace imebra
{

namespace tests
{

TEST(colorConversion, RGB2YBRFULL)
{
    Image rgb(1, 1, bitDepth_t::depthU8, "RGB", 7);

    {
        std::unique_ptr<WritingDataHandler> rgbHandler(rgb.getWritingDataHandler());
        rgbHandler->setUnsignedLong(0, 255);
        rgbHandler->setUnsignedLong(1, 255);
        rgbHandler->setUnsignedLong(2, 255);
    }

    std::unique_ptr<Transform> rgb2ybr(ColorTransformsFactory::getTransform("RGB", "YBR_FULL"));

    Image ybr1(1, 1, bitDepth_t::depthU8, "YBR_FULL", 7);
    rgb2ybr->runTransform(rgb, 0, 0, 1, 1, ybr1, 0, 0);

    std::unique_ptr<ReadingDataHandler> ybr1Handler(ybr1.getReadingDataHandler());
    ASSERT_EQ(255, ybr1Handler->getSignedLong(0));
    ASSERT_EQ(128, ybr1Handler->getSignedLong(1));
    ASSERT_EQ(128, ybr1Handler->getSignedLong(2));
}

TEST(colorConversion, YBRFULL2RGB)
{
    Image ybr(1, 1, bitDepth_t::depthU8, "YBR_FULL", 7);

    {
        std::unique_ptr<WritingDataHandler> ybrHandler(ybr.getWritingDataHandler());
        ybrHandler->setUnsignedLong(0, 255);
        ybrHandler->setUnsignedLong(1, 128);
        ybrHandler->setUnsignedLong(2, 128);
    }

    std::unique_ptr<Transform> ybr2rgb(ColorTransformsFactory::getTransform("YBR_FULL", "RGB"));

    Image rgb1(1, 1, bitDepth_t::depthU8, "RGB", 7);
    ybr2rgb->runTransform(ybr, 0, 0, 1, 1, rgb1, 0, 0);
    std::unique_ptr<ReadingDataHandler> rgb1Handler(rgb1.getReadingDataHandler());

    ASSERT_EQ(255, rgb1Handler->getSignedLong(0));
    ASSERT_EQ(255, rgb1Handler->getSignedLong(1));
    ASSERT_EQ(255, rgb1Handler->getSignedLong(2));
}

}

}

