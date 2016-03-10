#include <imebra/imebra.h>
#include <stdlib.h>

namespace imebra
{

namespace tests
{


imebra::Image buildImageForTest(
	std::uint32_t pixelsX, 
	std::uint32_t pixelsY, 
    imebra::bitDepth_t depth,
	std::uint32_t highBit, 
	double width, 
	double height, 
    const std::string& colorSpace,
	std::uint32_t continuity)
{
    imebra::Image newImage(pixelsX, pixelsY, depth, colorSpace, highBit);
    imebra::WritingDataHandler handler = newImage.getWritingDataHandler();
    std::uint32_t channelsNumber = newImage.getChannelsNumber();

	std::int32_t range = (std::uint32_t)1 << highBit;
	std::int32_t minValue = 0;
    if(depth == bitDepth_t::depthS16 || depth == bitDepth_t::depthS8)
	{
		minValue = -1 << (highBit - 1);
	}
	std::int32_t maxValue(minValue + range);

	std::uint32_t index(0);
	for(std::uint32_t scanY(0); scanY != pixelsY; ++scanY)
	{
		for(std::uint32_t scanX(0); scanX != pixelsX; ++scanX)
		{
			for(std::uint32_t scanChannels = 0; scanChannels != channelsNumber; ++scanChannels)
			{
                std::int32_t value = (std::int32_t)(((double)((scanX + scanY) % continuity) / (double)continuity) * (double)range)  + minValue;
 				if(value < minValue)
				{
					value = minValue;
				}
				if(value >= maxValue)
				{
					value = maxValue - 1;
				}
                handler.setSignedLong(index++, value);
			}
		}
	}

    newImage.setSizeMm(width, height);

	return newImage;
}


double compareImages(const imebra::Image& image0, const imebra::Image& image1)
{
    size_t width0(image0.getWidth()), height0(image0.getHeight());
    size_t width1(image1.getWidth()), height1(image1.getHeight());

    if(width0 != width1 || height0 != height1)
	{
		return 1000;
	}

    std::uint32_t channelsNumber0(image0.getChannelsNumber());
    std::uint32_t channelsNumber1(image1.getChannelsNumber());
    if(channelsNumber0 != channelsNumber1)
	{
		return 1000;
	}

    ReadingDataHandler hImage0 = image0.getReadingDataHandler();
    ReadingDataHandler hImage1 = image1.getReadingDataHandler();

    std::uint32_t highBit0 = image0.getHighBit();
    std::uint32_t highBit1 = image1.getHighBit();
	if(highBit0 != highBit1)
	{
		return 1000;
	}

    bitDepth_t depth0 = image0.getDepth();
    bitDepth_t depth1 = image1.getDepth();
	if(depth0 != depth1)
	{
		return 1000;
	}
	
	if(width0 == 0 || height0 == 0)
	{
		return 0;
	}

    size_t valuesNum = width0 * height0 * channelsNumber0;
	double divisor = double(valuesNum);
    double range = (double)(1 << image0.getHighBit());
	double difference(0);
	int index(0);
	unsigned long long total(0);
	while(valuesNum--)
	{
        difference += 1000 * (double)labs(hImage0.getSignedLong(index) - hImage1.getSignedLong(index)) / range;
        total += labs(hImage0.getSignedLong(index));
		++index;
	}

	difference /= divisor;

	return difference;
}


} // namespace tests

} // namespace imebra
