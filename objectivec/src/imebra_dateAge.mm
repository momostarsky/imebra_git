/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import <Foundation/NSString.h>
#include "imebra_implementation_macros.h"
#include "../include/imebraobjc/imebra_dateAge.h"
#include <imebra/dataSet.h>

@implementation ImebraAge

-(void)dealloc
{
    delete_imebra_object_holder(Age);
}

-(id)initWithAge:(unsigned int)initialAge units:(ImebraAgeUnit_t)initialUnits
{
    reset_imebra_object_holder(Age);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Age, new imebra::Age(initialAge, (imebra::ageUnit_t)initialUnits));
    }
    return self;
}

-(double)years
{
    return get_imebra_object_holder(Age)->years();
}

-(unsigned int)age
{
    return get_imebra_object_holder(Age)->age;
}

-(ImebraAgeUnit_t)units
{
    return (ImebraAgeUnit_t)(get_imebra_object_holder(Age)->units);
}

@end


@implementation ImebraDate

-(void)dealloc
{
    delete_imebra_object_holder(Date);
}

-(id)initWithYear:(unsigned int)initialYear
                                month:(unsigned int)initialMonth
                                day:(unsigned int)initialDay
                                hour:(unsigned int)initialHour
                                minutes:(unsigned int)initialMinutes
                                seconds:(unsigned int)initialSeconds
                                nanoseconds:(unsigned int)initialNanoseconds
                                offsetHours:(int)initialOffsetHours
                                offsetMinutes:(int)initialOffsetMinutes
{
    reset_imebra_object_holder(Date);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Date,
                                 new imebra::Date(
                                     initialYear,
                                     initialMonth,
                                     initialDay,
                                     initialHour,
                                     initialMinutes,
                                     initialSeconds,
                                     initialNanoseconds,
                                     initialOffsetHours,
                                     initialOffsetMinutes));
    }
    return self;
}

-(unsigned int)year
{
    return get_imebra_object_holder(Date)->year;
}

-(unsigned int)month
{
    return get_imebra_object_holder(Date)->month;
}

-(unsigned int)day
{
    return get_imebra_object_holder(Date)->day;
}

-(unsigned int)hour
{
    return get_imebra_object_holder(Date)->hour;
}

-(unsigned int)minutes
{
    return get_imebra_object_holder(Date)->minutes;
}

-(unsigned int)seconds
{
    return get_imebra_object_holder(Date)->seconds;
}

-(unsigned int)nanoseconds
{
    return get_imebra_object_holder(Date)->nanoseconds;
}

-(int)offsetHours
{
    return get_imebra_object_holder(Date)->offsetHours;
}

-(int)offsetMinutes
{
    return get_imebra_object_holder(Date)->offsetMinutes;
}

@end
