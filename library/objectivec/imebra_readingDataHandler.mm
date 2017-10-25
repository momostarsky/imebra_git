/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/imebra/imebra.h"
#import "../include/imebra/objectivec/imebra_nserror.h"
#import "../include/imebra/objectivec/imebra_strings.h"
#import "../include/imebra/objectivec/imebra_dateAge.h"
#import "../include/imebra/objectivec/imebra_readingDataHandler.h"
#import <Foundation/NSString.h>

@implementation ImebraReadingDataHandler

-(id)initWithImebraReadingDataHandler:(imebra::ReadingDataHandler*)pReadingDataHandler
{
    self = [super init];
    if(self)
    {
        self->m_pDataHandler = pReadingDataHandler;
    }
    return self;

}

-(void)dealloc
{
    delete self->m_pDataHandler;
}

-(unsigned int) size
{
    return (unsigned int)self->m_pDataHandler->getSize();
}

-(int) getSignedLong:(unsigned int)index error:(NSError**)pError
{
    try
    {
        return self->m_pDataHandler->getSignedLong(index);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return 0;
    }
}

-(unsigned int) getUnsignedLong:(unsigned int)index error:(NSError**)pError
{
    try
    {
        return self->m_pDataHandler->getUnsignedLong(index);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return 0;
    }
}

-(double) getDouble:(unsigned int)index error:(NSError**)pError
{
    try
    {
        return self->m_pDataHandler->getDouble(index);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return 0.0f;
    }
}

-(NSString*) getString:(unsigned int)index error:(NSError**)pError
{
    try
    {
        return imebra::stringToNSString(self->m_pDataHandler->getString(index));
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(ImebraDate*) getDate:(unsigned int)index error:(NSError**)pError
{
    try
    {
        imebra::Date date(self->m_pDataHandler->getDate(index));
        return [[ImebraDate alloc] initWithDate:date.year
                month:date.month
                day:date.day
                hour:date.hour
                minutes:date.minutes
                seconds:date.seconds
                nanoseconds:date.nanoseconds
                offsetHours:date.offsetHours
                offsetMinutes:date.offsetMinutes];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(ImebraAge*) getAge:(unsigned int)index error:(NSError**)pError
{
    imebra::Age age(0, imebra::ageUnit_t::days);
    try
    {
        imebra::Age age(self->m_pDataHandler->getAge(index));
        return [[ImebraAge alloc] initWithAge:age.age
                units:(ImebraAgeUnit_t)age.units];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}


@end


