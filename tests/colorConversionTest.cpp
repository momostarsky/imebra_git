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

TEST(colorConversion, factoryTest)
{
    ASSERT_FALSE(ColorTransformsFactory::canSubsample("RGB"));
    ASSERT_FALSE(ColorTransformsFactory::canSubsample("MONOCHROME2"));
    ASSERT_FALSE(ColorTransformsFactory::canSubsample("MONOCHROME1"));
    ASSERT_FALSE(ColorTransformsFactory::canSubsample("PALETTE COLOR"));
    ASSERT_TRUE(ColorTransformsFactory::canSubsample("YBR_FULL"));
    ASSERT_TRUE(ColorTransformsFactory::canSubsample("YBR_PARTIAL"));

    ASSERT_FALSE(ColorTransformsFactory::isMonochrome("RGB"));
    ASSERT_TRUE(ColorTransformsFactory::isMonochrome("MONOCHROME2"));
    ASSERT_TRUE(ColorTransformsFactory::isMonochrome("MONOCHROME1"));
    ASSERT_FALSE(ColorTransformsFactory::isMonochrome("PALETTE COLOR"));
    ASSERT_FALSE(ColorTransformsFactory::isMonochrome("YBR_FULL"));
    ASSERT_FALSE(ColorTransformsFactory::isMonochrome("YBR_PARTIAL"));

    ASSERT_EQ(3, ColorTransformsFactory::getNumberOfChannels("RGB"));
    ASSERT_EQ(1, ColorTransformsFactory::getNumberOfChannels("MONOCHROME2"));
    ASSERT_EQ(1, ColorTransformsFactory::getNumberOfChannels("MONOCHROME1"));
    ASSERT_EQ(1, ColorTransformsFactory::getNumberOfChannels("PALETTE COLOR"));
    ASSERT_EQ(3, ColorTransformsFactory::getNumberOfChannels("YBR_FULL"));
    ASSERT_EQ(3, ColorTransformsFactory::getNumberOfChannels("YBR_PARTIAL"));

    ASSERT_EQ("YBR_PARTIAL_422", ColorTransformsFactory::makeSubsampled("YBR_PARTIAL", true, false));
    ASSERT_EQ("YBR_PARTIAL_420", ColorTransformsFactory::makeSubsampled("YBR_PARTIAL", true, true));
    ASSERT_EQ("YBR_PARTIAL", ColorTransformsFactory::makeSubsampled("YBR_PARTIAL", false, false));

    ASSERT_EQ("YBR_FULL", ColorTransformsFactory::normalizeColorSpace("YBR_FULL_422"));
    ASSERT_TRUE(ColorTransformsFactory::isSubsampledX("YBR_FULL_422"));
    ASSERT_FALSE(ColorTransformsFactory::isSubsampledY("YBR_FULL_422"));
    ASSERT_TRUE(ColorTransformsFactory::isSubsampledY("YBR_FULL_420"));
    ASSERT_EQ("PALETTE COLOR", ColorTransformsFactory::normalizeColorSpace("PALETTE COLOR"));
}

}

}

