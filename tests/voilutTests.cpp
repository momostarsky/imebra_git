#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>


namespace imebra
{

namespace tests
{

TEST(voilut, voilutUnsigned8)
{
    Image unsigned8(6, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        std::unique_ptr<WritingDataHandler> unsigned8Handler(unsigned8.getWritingDataHandler());
        unsigned8Handler->setUnsignedLong(0, 0);
        unsigned8Handler->setUnsignedLong(1, 10);
        unsigned8Handler->setUnsignedLong(2, 20);
        unsigned8Handler->setUnsignedLong(3, 30);
        unsigned8Handler->setUnsignedLong(4, 40);
        unsigned8Handler->setUnsignedLong(5, 50);
    }

    VOILUT voilut;
    voilut.setCenterWidth(0, 50);

    std::unique_ptr<Image> unsigned8Out(voilut.allocateOutputImage(unsigned8, 6, 1));
    voilut.runTransform(unsigned8, 0, 0, 6, 1, *unsigned8Out, 0, 0);

    std::unique_ptr<ReadingDataHandler> unsigned8Handler(unsigned8Out->getReadingDataHandler());

    ASSERT_EQ(128, unsigned8Handler->getUnsignedLong(0));
    ASSERT_EQ(179, unsigned8Handler->getUnsignedLong(1));
    ASSERT_EQ(230, unsigned8Handler->getUnsignedLong(2));
    ASSERT_EQ(255, unsigned8Handler->getUnsignedLong(3));
    ASSERT_EQ(255, unsigned8Handler->getUnsignedLong(4));
    ASSERT_EQ(255, unsigned8Handler->getUnsignedLong(5));

    voilut.setCenterWidth(70, 50);

    Image signed16Out(6, 1, bitDepth_t::depthS16, "MONOCHROME2", 15);
    voilut.runTransform(unsigned8, 0, 0, 6, 1, signed16Out, 0, 0);

    std::unique_ptr<ReadingDataHandler> signed16Handler(signed16Out.getReadingDataHandler());

    ASSERT_EQ(-32768, signed16Handler->getSignedLong(0));
    ASSERT_EQ(-32768, signed16Handler->getSignedLong(1));
    ASSERT_EQ(-32768, signed16Handler->getSignedLong(2));
    ASSERT_EQ(-32768, signed16Handler->getSignedLong(3));
    ASSERT_EQ(-32768, signed16Handler->getSignedLong(4));
    ASSERT_EQ(-26213, signed16Handler->getSignedLong(5));

}


}

}

