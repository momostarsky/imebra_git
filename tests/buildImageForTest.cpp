#include <imebra/image.h>
#include <stdlib.h>

namespace imebra
{

namespace tests
{


imebra::Image buildImageForTest(
	std::uint32_t pixelsX, 
	std::uint32_t pixelsY, 
    imebra::Image::bitDepth depth,
	std::uint32_t highBit, 
	double sizeX, 
	double sizeY, 
    const std::string& colorSpace,
	std::uint32_t continuity)
{
    imebra::Image newImage;
    imebra::WritingDataHandler handler = newImage.create(pixelsX, pixelsY, depth, colorSpace, highBit);
    int channelsNumber = newImage.getChannelsNumber();

	std::int32_t range = (std::uint32_t)1 << highBit;
	std::int32_t minValue = 0;
    if(depth == Image::bitDepth::depthS16 || depth == Image::bitDepth::depthS8)
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
				std::int32_t value = (std::int32_t)(((double)((scanX * channelsNumber+ scanY + scanChannels) % continuity) / (double)continuity) * (double)range)  + minValue;
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

    newImage.setSizeMm(sizeX, sizeY);

	return newImage;
}


double compareImages(const imebra::Image& image0, const imebra::Image& image1)
{
    std::uint32_t sizeX0(image0.getSizeX()), sizeY0(image0.getSizeY());
    std::uint32_t sizeX1(image1.getSizeX()), sizeY1(image1.getSizeY());

    if(sizeX0 != sizeX1 || sizeY0 != sizeY1)
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

    Image::bitDepth depth0 = image0.getDepth();
    Image::bitDepth depth1 = image1.getDepth();
	if(depth0 != depth1)
	{
		return 1000;
	}
	
	if(sizeX0 == 0 || sizeY0 == 0)
	{
		return 0;
	}

	std::uint32_t valuesNum = sizeX0 * sizeY0 * channelsNumber0;
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
