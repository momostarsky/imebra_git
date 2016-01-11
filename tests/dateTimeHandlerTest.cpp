#include <imebra/dataSet.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(dateTimeHandlerTest, dateTest)
{
    DataSet testDataSet;

    testDataSet.setDate(0x0008, 0, 0x0012, 0, 0, Date(2004, 11, 5, 9, 20, 30, 5000, 1, 2));
    Date checkDate = testDataSet.getDate(0x0008, 0, 0x0012, 0, 0);
    std::wstring checkString = testDataSet.getString(0x0008, 0, 0x0012, 0, 0);
    EXPECT_EQ(L"20041105", checkString);
    EXPECT_EQ(2004, checkDate.year);
    EXPECT_EQ(11, checkDate.month);
    EXPECT_EQ(5, checkDate.day);
    EXPECT_EQ(0, checkDate.hour);
    EXPECT_EQ(0, checkDate.minutes);
    EXPECT_EQ(0, checkDate.seconds);
    EXPECT_EQ(0, checkDate.nanoseconds);
    EXPECT_EQ(0, checkDate.offsetHours);
    EXPECT_EQ(0, checkDate.offsetMinutes);
    EXPECT_EQ("DA", testDataSet.getDataType(0x0008, 0, 0x0012));


    testDataSet.setString(0x0008, 0, 0x0012, 0, 0, L"20120910");
    Date checkDate1 = testDataSet.getDate(0x0008, 0, 0x0012, 0, 0);
    EXPECT_EQ(2012, checkDate1.year);
    EXPECT_EQ(9, checkDate1.month);
    EXPECT_EQ(10, checkDate1.day);
    EXPECT_EQ(0, checkDate1.hour);
    EXPECT_EQ(0, checkDate1.minutes);
    EXPECT_EQ(0, checkDate1.seconds);
    EXPECT_EQ(0, checkDate1.nanoseconds);
    EXPECT_EQ(0, checkDate1.offsetHours);
    EXPECT_EQ(0, checkDate1.offsetMinutes);
}

TEST(dateTimeHandlerTest, timeTest)
{
    DataSet testDataSet;

    {
        testDataSet.setDate(0x0008, 0, 0x0013, 0, 0, Date(2004, 11, 5, 9, 20, 30, 5000, 1, 2));
        Date checkDate = testDataSet.getDate(0x0008, 0, 0x0013, 0, 0);
        std::wstring checkString = testDataSet.getString(0x0008, 0, 0x0013, 0, 0);
        EXPECT_EQ(L"092030.005000", checkString);
        EXPECT_EQ(0, checkDate.year);
        EXPECT_EQ(0, checkDate.month);
        EXPECT_EQ(0, checkDate.day);
        EXPECT_EQ(9, checkDate.hour);
        EXPECT_EQ(20, checkDate.minutes);
        EXPECT_EQ(30, checkDate.seconds);
        EXPECT_EQ(5000, checkDate.nanoseconds);
        EXPECT_EQ(0, checkDate.offsetHours);
        EXPECT_EQ(0, checkDate.offsetMinutes);
        EXPECT_EQ("TM", testDataSet.getDataType(0x0008, 0, 0x0013));
    }

    {
        testDataSet.setString(0x0008, 0, 0x0013, 0, 0, L"101502");
        Date checkDate = testDataSet.getDate(0x0008, 0, 0x0013, 0, 0);
        EXPECT_EQ(0, checkDate.year);
        EXPECT_EQ(0, checkDate.month);
        EXPECT_EQ(0, checkDate.day);
        EXPECT_EQ(10, checkDate.hour);
        EXPECT_EQ(15, checkDate.minutes);
        EXPECT_EQ(2, checkDate.seconds);
        EXPECT_EQ(0, checkDate.nanoseconds);
        EXPECT_EQ(0, checkDate.offsetHours);
        EXPECT_EQ(0, checkDate.offsetMinutes);
    }

    {
        testDataSet.setString(0x0008, 0, 0x0013, 0, 0, L"1015");
        Date checkDate = testDataSet.getDate(0x0008, 0, 0x0013, 0, 0);
        EXPECT_EQ(0, checkDate.year);
        EXPECT_EQ(0, checkDate.month);
        EXPECT_EQ(0, checkDate.day);
        EXPECT_EQ(10, checkDate.hour);
        EXPECT_EQ(15, checkDate.minutes);
        EXPECT_EQ(0, checkDate.seconds);
        EXPECT_EQ(0, checkDate.nanoseconds);
        EXPECT_EQ(0, checkDate.offsetHours);
        EXPECT_EQ(0, checkDate.offsetMinutes);
    }
}
/*
TEST(dateTimeHandlerTest, dateTimeTest)
{
	ptr<data> tag(new data(ptr<baseObject>(0)));
	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "DT");
		hTag->setSize(1);

		hTag->setDate(0, 2004, 11, 5, 9, 20, 40, 5000, 1, 2);

		std::int32_t year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

        EXPECT_EQ(2004, year);
        EXPECT_EQ(11, month);
        EXPECT_EQ(5, day);
        EXPECT_EQ(9, hour);
        EXPECT_EQ(20, minutes);
        EXPECT_EQ(40, seconds);
        EXPECT_EQ(5000, nanoseconds);
        EXPECT_EQ(1, offsetHours);
        EXPECT_EQ(2, offsetMinutes);

        EXPECT_EQ(std::wstring(L"2004-11-05 09:20:40.005000+01:02"), hTag->getUnicodeString(0));
	}

	{
		ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, false, "DT");
		std::basic_string<std::uint8_t> checkString(hTag->getMemory()->data(), hTag->getMemory()->size());
        EXPECT_EQ(std::basic_string<std::uint8_t>((std::uint8_t*)"20041105092040.005000+0102"), checkString);
	}

	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "DT");

		std::int32_t year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

        EXPECT_EQ(2004, year);
        EXPECT_EQ(11, month);
        EXPECT_EQ(5, day);
        EXPECT_EQ(9, hour);
        EXPECT_EQ(20, minutes);
        EXPECT_EQ(40, seconds);
        EXPECT_EQ(5000, nanoseconds);
        EXPECT_EQ(1, offsetHours);
        EXPECT_EQ(2, offsetMinutes);

        EXPECT_EQ(std::wstring(L"2004-11-05 09:20:40.005000+01:02"), hTag->getUnicodeString(0));

		hTag->setString(0, "2005-12-06 10:21:41.005001-4:5");
		hTag->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);
        EXPECT_EQ(2005, year);
        EXPECT_EQ(12, month);
        EXPECT_EQ(6, day);
        EXPECT_EQ(10, hour);
        EXPECT_EQ(21, minutes);
        EXPECT_EQ(41, seconds);
        EXPECT_EQ(5001, nanoseconds);
        EXPECT_EQ(-4, offsetHours);
        EXPECT_EQ(-5, offsetMinutes);
	}

	{
		ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, true, "DT");
		std::basic_string<std::uint8_t> checkString(hTag->getMemory()->data(), hTag->getMemory()->size());
        EXPECT_EQ(std::basic_string<std::uint8_t>((std::uint8_t*)"20051206102141.005001-0405"), checkString);
		hTag->getMemory()->assign((std::uint8_t*)"19990305", 8);
	}

	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, false, "DT");

		std::int32_t year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

        EXPECT_EQ(1999, year);
        EXPECT_EQ(3, month);
        EXPECT_EQ(5, day);
        EXPECT_EQ(0, hour);
        EXPECT_EQ(0, minutes);
        EXPECT_EQ(0, seconds);
        EXPECT_EQ(0, nanoseconds);
        EXPECT_EQ(0, offsetHours);
        EXPECT_EQ(0, offsetMinutes);
	}

	{
		ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, true, "DT");
		hTag->getMemory()->assign((std::uint8_t*)"1999030508", 10);
	}

	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, false, "DT");

		std::int32_t year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

        EXPECT_EQ(1999, year);
        EXPECT_EQ(3, month);
        EXPECT_EQ(5, day);
        EXPECT_EQ(8, hour);
        EXPECT_EQ(0, minutes);
        EXPECT_EQ(0, seconds);
        EXPECT_EQ(0, nanoseconds);
        EXPECT_EQ(0, offsetHours);
        EXPECT_EQ(0, offsetMinutes);
	}
}

TEST(dateTimeHandlerTest, incompleteDateTimeTest)
{
    ptr<data> tag(new data(ptr<baseObject>(0)));
    {
        ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, true, "DT");
        std::string bufferData;
        hTag->setSize(0);
        hTag->copyFrom((std::uint8_t*)bufferData.data(), bufferData.size());
    }

    std::int32_t year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
    ptr<handlers::dataHandler> hTag = tag->getDataHandler(0, false, "");
    hTag->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

    EXPECT_EQ(0, year);
    EXPECT_EQ(0, month);
    EXPECT_EQ(0, day);
    EXPECT_EQ(0, hour);
    EXPECT_EQ(0, minutes);
    EXPECT_EQ(0, seconds);
    EXPECT_EQ(0, nanoseconds);
    EXPECT_EQ(0, offsetHours);
    EXPECT_EQ(0, offsetMinutes);

    {
        ptr<handlers::dataHandlerRaw> hTag = tag->getDataHandlerRaw(0, true, "DT");
        hTag->setSize(1);
        std::string bufferData("199901");
        hTag->setSize(0);
        hTag->copyFrom((std::uint8_t*)bufferData.data(), bufferData.size());
    }

    hTag = tag->getDataHandler(0, false, "");
    hTag->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

    EXPECT_EQ(1999, year);
    EXPECT_EQ(1, month);
    EXPECT_EQ(0, day);
    EXPECT_EQ(0, hour);
    EXPECT_EQ(0, minutes);
    EXPECT_EQ(0, seconds);
    EXPECT_EQ(0, nanoseconds);
    EXPECT_EQ(0, offsetHours);
    EXPECT_EQ(0, offsetMinutes);

    {
        ptr<handlers::dataHandlerRaw> hTag = tag->getDataHandlerRaw(0, true, "DT");
        std::string bufferData("19990120");
        hTag->setSize(0);
        hTag->copyFrom((std::uint8_t*)bufferData.data(), bufferData.size());
    }

    hTag = tag->getDataHandler(0, false, "");
    hTag->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

    EXPECT_EQ(1999, year);
    EXPECT_EQ(1, month);
    EXPECT_EQ(20, day);
    EXPECT_EQ(0, hour);
    EXPECT_EQ(0, minutes);
    EXPECT_EQ(0, seconds);
    EXPECT_EQ(0, nanoseconds);
    EXPECT_EQ(0, offsetHours);
    EXPECT_EQ(0, offsetMinutes);

    {
        ptr<handlers::dataHandlerRaw> hTag = tag->getDataHandlerRaw(0, true, "DT");
        std::string bufferData("1999012012");
        hTag->setSize(0);
        hTag->copyFrom((std::uint8_t*)bufferData.data(), bufferData.size());
    }

    hTag = tag->getDataHandler(0, false, "");
    hTag->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

    EXPECT_EQ(1999, year);
    EXPECT_EQ(1, month);
    EXPECT_EQ(20, day);
    EXPECT_EQ(12, hour);
    EXPECT_EQ(0, minutes);
    EXPECT_EQ(0, seconds);
    EXPECT_EQ(0, nanoseconds);
    EXPECT_EQ(0, offsetHours);
    EXPECT_EQ(0, offsetMinutes);
}


*/
} // namespace tests

} // namespace imebra

