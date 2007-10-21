#include <cppunit/extensions/HelperMacros.h>
#include "dateTimeHandlerTest.h"

#include "../../imebra/include/imebra.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{

CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::dateTimeHandlerTest);



void dateTimeHandlerTest::dateTest()
{
	ptr<data> tag(new data(ptr<baseObject>(0)));
	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "DA");
		hTag->setSize(1);

		hTag->setDate(2004, 11, 5, 9, 20, 30, 5000, 1, 2);

		imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

		CPPUNIT_ASSERT(year == 2004);
		CPPUNIT_ASSERT(month == 11);
		CPPUNIT_ASSERT(day == 5);
		CPPUNIT_ASSERT(hour == 0);
		CPPUNIT_ASSERT(minutes == 0);
		CPPUNIT_ASSERT(seconds == 0);
		CPPUNIT_ASSERT(nanoseconds == 0);
		CPPUNIT_ASSERT(offsetHours == 0);
		CPPUNIT_ASSERT(offsetMinutes == 0);

		CPPUNIT_ASSERT(hTag->getUnicodeString() == L"2004-11-05");
	}

	{
		ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, true, "DA");
		CPPUNIT_ASSERT(*(hTag->getMemory()->getStringPointer()) == (imbxUint8*)"20041105");
		hTag->getMemory()->assign((imbxUint8*)"2004-11-5", 9);
	}

	{
		ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, false, "DA");
		stringUint8 tempString = *(hTag->getMemory()->getStringPointer());
		stringUint8 compString((imbxUint8*)"2004-11-5", 9);
		compString += (imbxUint8)0; // buffer's size is always even!
		CPPUNIT_ASSERT(tempString == compString);
	}

	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, false, "DA");

		imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

		CPPUNIT_ASSERT(year == 2004);
		CPPUNIT_ASSERT(month == 11);
		CPPUNIT_ASSERT(day == 5);
		CPPUNIT_ASSERT(hour == 0);
		CPPUNIT_ASSERT(minutes == 0);
		CPPUNIT_ASSERT(seconds == 0);
		CPPUNIT_ASSERT(nanoseconds == 0);
		CPPUNIT_ASSERT(offsetHours == 0);
		CPPUNIT_ASSERT(offsetMinutes == 0);

		CPPUNIT_ASSERT(hTag->getUnicodeString() == L"2004-11-05");
	}
}

void dateTimeHandlerTest::timeTest()
{
	ptr<data> tag(new data(ptr<baseObject>(0)));
	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "TM");
		hTag->setSize(1);

		hTag->setDate(2004, 11, 5, 9, 20, 40, 5000, 1, 2);

		imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

		CPPUNIT_ASSERT(year == 0);
		CPPUNIT_ASSERT(month == 0);
		CPPUNIT_ASSERT(day == 0);
		CPPUNIT_ASSERT(hour == 9);
		CPPUNIT_ASSERT(minutes == 20);
		CPPUNIT_ASSERT(seconds == 40);
		CPPUNIT_ASSERT(nanoseconds == 5000);
		CPPUNIT_ASSERT(offsetHours == 0);
		CPPUNIT_ASSERT(offsetMinutes == 0);

		CPPUNIT_ASSERT(hTag->getUnicodeString() == L"09:20:40.005000");
	}

	{
		ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, true, "TM");
		stringUint8 compString((imbxUint8*)"092040.005000");
		compString += (imbxUint8)0;
		CPPUNIT_ASSERT(*(hTag->getMemory()->getStringPointer()) == compString);
		hTag->getMemory()->assign((imbxUint8*)"9:20:40", 7);
	}

	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, false, "TM");

		imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

		CPPUNIT_ASSERT(year == 0);
		CPPUNIT_ASSERT(month == 0);
		CPPUNIT_ASSERT(day == 0);
		CPPUNIT_ASSERT(hour == 9);
		CPPUNIT_ASSERT(minutes == 20);
		CPPUNIT_ASSERT(seconds == 40);
		CPPUNIT_ASSERT(nanoseconds == 0);
		CPPUNIT_ASSERT(offsetHours == 0);
		CPPUNIT_ASSERT(offsetMinutes == 0);

		CPPUNIT_ASSERT(hTag->getUnicodeString() == L"09:20:40.000000");
	}
}

void dateTimeHandlerTest::dateTimeTest()
{
	ptr<data> tag(new data(ptr<baseObject>(0)));
	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "DT");
		hTag->setSize(1);

		hTag->setDate(2004, 11, 5, 9, 20, 40, 5000, 1, 2);

		imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

		CPPUNIT_ASSERT(year == 2004);
		CPPUNIT_ASSERT(month == 11);
		CPPUNIT_ASSERT(day == 5);
		CPPUNIT_ASSERT(hour == 9);
		CPPUNIT_ASSERT(minutes == 20);
		CPPUNIT_ASSERT(seconds == 40);
		CPPUNIT_ASSERT(nanoseconds == 5000);
		CPPUNIT_ASSERT(offsetHours == 1);
		CPPUNIT_ASSERT(offsetMinutes == 2);

		CPPUNIT_ASSERT(hTag->getUnicodeString() == L"2004-11-05 09:20:40.005000+01:02");
	}

	{
		ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, false, "DT");
		CPPUNIT_ASSERT(*(hTag->getMemory()->getStringPointer()) == (imbxUint8*)"20041105092040.005000+0102");
	}

	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "DT");

		imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

		CPPUNIT_ASSERT(year == 2004);
		CPPUNIT_ASSERT(month == 11);
		CPPUNIT_ASSERT(day == 5);
		CPPUNIT_ASSERT(hour == 9);
		CPPUNIT_ASSERT(minutes == 20);
		CPPUNIT_ASSERT(seconds == 40);
		CPPUNIT_ASSERT(nanoseconds == 5000);
		CPPUNIT_ASSERT(offsetHours == 1);
		CPPUNIT_ASSERT(offsetMinutes == 2);

		CPPUNIT_ASSERT(hTag->getUnicodeString() == L"2004-11-05 09:20:40.005000+01:02");

		hTag->setString("2005-12-06 10:21:41.005001-4:5");
		hTag->getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);
		CPPUNIT_ASSERT(year == 2005);
		CPPUNIT_ASSERT(month == 12);
		CPPUNIT_ASSERT(day == 6);
		CPPUNIT_ASSERT(hour == 10);
		CPPUNIT_ASSERT(minutes == 21);
		CPPUNIT_ASSERT(seconds == 41);
		CPPUNIT_ASSERT(nanoseconds == 5001);
		CPPUNIT_ASSERT(offsetHours == -4);
		CPPUNIT_ASSERT(offsetMinutes == -5);
	}

	{
		ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, true, "DT");
		CPPUNIT_ASSERT(*(hTag->getMemory()->getStringPointer()) == (imbxUint8*)"20051206102141.005001-0405");
		hTag->getMemory()->assign((imbxUint8*)"19990305", 8);
	}

	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, false, "DT");

		imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

		CPPUNIT_ASSERT(year == 1999);
		CPPUNIT_ASSERT(month == 03);
		CPPUNIT_ASSERT(day == 05);
		CPPUNIT_ASSERT(hour == 0);
		CPPUNIT_ASSERT(minutes == 0);
		CPPUNIT_ASSERT(seconds == 0);
		CPPUNIT_ASSERT(nanoseconds == 0);
		CPPUNIT_ASSERT(offsetHours == 0);
		CPPUNIT_ASSERT(offsetMinutes == 0);
	}

	{
		ptr<handlers::dataHandlerRaw> hTag= tag->getDataHandlerRaw(0, true, "DT");
		hTag->getMemory()->assign((imbxUint8*)"1999030508", 10);
	}

	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, false, "DT");

		imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
		hTag->getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

		CPPUNIT_ASSERT(year == 1999);
		CPPUNIT_ASSERT(month == 03);
		CPPUNIT_ASSERT(day == 05);
		CPPUNIT_ASSERT(hour == 8);
		CPPUNIT_ASSERT(minutes == 0);
		CPPUNIT_ASSERT(seconds == 0);
		CPPUNIT_ASSERT(nanoseconds == 0);
		CPPUNIT_ASSERT(offsetHours == 0);
		CPPUNIT_ASSERT(offsetMinutes == 0);
	}
}



} // namespace tests

} // namespace imebra

} // namespace puntoexe