#include <gtest/gtest.h>
#include <imebra/imebra.h>

namespace imebra
{

namespace tests
{

// A buffer initialized to a default data type should use the data type OB
TEST(bitTransformTest, bitShift)
{
    std::uint32_t sizeX = 41;
    std::uint32_t sizeY = 13;
    Image bits8Image(sizeX, sizeY, bitDepth::depthU8, "RGB", 7);
    Image bits16Image(sizeX, sizeY, bitDepth::depthU16, "RGB", 15);
    Image bits4Image(sizeX, sizeY, bitDepth::depthU8, "RGB", 3);
    {
        WritingDataHandler imageHandler = bits8Image.getWritingDataHandler();

        // Make 3 bands (RGB)
        size_t elementNumber(0);
        for(std::uint32_t y=0; y<sizeY; ++y)
        {
            for(std::uint32_t x=0; x<sizeX; ++x)
            {
                std::int32_t r, g, b;
                std::uint32_t value = y * 255 / sizeY;
                r = g = 0;
                b = value;
                if(x < sizeX - sizeX/3)
                {
                    r = 0;
                    g = value;
                    b = 0;
                }
                if(x < sizeX / 3)
                {
                    r = value;
                    g = 0;
                    b = 0;
                }
                imageHandler.setUnsignedLong(elementNumber++, r);
                imageHandler.setUnsignedLong(elementNumber++, g);
                imageHandler.setUnsignedLong(elementNumber++, b);
            }
        }
    }

    TransformHighBit transform;
    transform.runTransform(bits8Image, 0, 0, sizeX, sizeY, bits16Image, 0, 0);
    transform.runTransform(bits8Image, 0, 0, sizeX, sizeY, bits4Image, 0, 0);


    ReadingDataHandler bits8Handler = bits8Image.getReadingDataHandler();
    ReadingDataHandler bits16Handler = bits16Image.getReadingDataHandler();
    ReadingDataHandler bits4Handler = bits4Image.getReadingDataHandler();
    size_t elementNumber = 0;
    for(std::uint32_t checkY = 0; checkY < sizeY; ++checkY)
    {
        for(std::uint32_t checkX = 0; checkX < sizeX; ++checkX)
        {
            std::int32_t r, g, b;
            std::uint32_t value = checkY * 255 / sizeY;
            r = g = 0;
            b = value;
            if(checkX < sizeX - sizeX/3)
            {
                r = 0;
                g = value;
                b = 0;
            }
            if(checkX < sizeX / 3)
            {
                r = value;
                g = 0;
                b = 0;
            }

            std::int32_t value0r = bits8Handler.getUnsignedLong(elementNumber);
            std::int32_t value1r = bits16Handler.getUnsignedLong(elementNumber);
            std::int32_t value2r = bits4Handler.getUnsignedLong(elementNumber++);

            std::int32_t value0g = bits8Handler.getUnsignedLong(elementNumber);
            std::int32_t value1g = bits16Handler.getUnsignedLong(elementNumber);
            std::int32_t value2g = bits4Handler.getUnsignedLong(elementNumber++);

            std::int32_t value0b = bits8Handler.getUnsignedLong(elementNumber);
            std::int32_t value1b = bits16Handler.getUnsignedLong(elementNumber);
            std::int32_t value2b = bits4Handler.getUnsignedLong(elementNumber++);

            EXPECT_EQ(value0r, r);
            EXPECT_EQ(value0g, g);
            EXPECT_EQ(value0b, b);

            EXPECT_EQ(value0r, (value1r>>8));
            EXPECT_EQ(value0g, (value1g>>8));
            EXPECT_EQ(value0b, (value1b>>8));

            EXPECT_EQ((value0r >> 4), value2r);
            EXPECT_EQ((value0g >> 4), value2g);
            EXPECT_EQ((value0b >> 4), value2b);

        }
    }
}

} // namespace tests

} // namespace imebra
