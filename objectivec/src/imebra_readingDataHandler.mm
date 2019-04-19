/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_readingDataHandler.h"
#import "../include/imebraobjc/imebra_dateAge.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include "imebra_strings.h"

#include <imebra/readingDataHandler.h>

@implementation ImebraReadingDataHandler

-(id)initWithImebraReadingDataHandler:define_imebra_parameter(ReadingDataHandler)
{
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(ReadingDataHandler, get_imebra_parameter(ReadingDataHandler));
    }
    else
    {
        delete get_imebra_parameter(ReadingDataHandler);
    }
    return self;

}

-(void)dealloc
{
    delete_imebra_object_holder(ReadingDataHandler);
}

-(unsigned int) size
{
    return (unsigned int)get_imebra_object_holder(ReadingDataHandler)->getSize();
}

-(int) getSignedLong:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getSignedLong(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned int) getUnsignedLong:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getUnsignedLong(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(double) getDouble:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getDouble(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0.0f);
}

-(NSString*) getString:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(ReadingDataHandler)->getString(index));

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraDate*) getDate:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    imebra::Date date(get_imebra_object_holder(ReadingDataHandler)->getDate(index));
    return [[ImebraDate alloc] initWithYear:date.year
            month:date.month
            day:date.day
            hour:date.hour
            minutes:date.minutes
            seconds:date.seconds
            nanoseconds:date.nanoseconds
            offsetHours:date.offsetHours
            offsetMinutes:date.offsetMinutes];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraAge*) getAge:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    imebra::Age age(get_imebra_object_holder(ReadingDataHandler)->getAge(index));
    return [[ImebraAge alloc] initWithAge:age.age
            units:(ImebraAgeUnit_t)age.units];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


@end


