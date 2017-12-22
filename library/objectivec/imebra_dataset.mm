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
#import "imebra_nserror.h"
#import "imebra_strings.h"
#import "../include/imebra/objectivec/imebra_tagId.h"
#import "../include/imebra/objectivec/imebra_dataset.h"
#import "../include/imebra/objectivec/imebra_dateAge.h"
#import "../include/imebra/objectivec/imebra_image.h"
#import "../include/imebra/objectivec/imebra_readingDataHandler.h"
#import "../include/imebra/objectivec/imebra_writingDataHandler.h"
#import <Foundation/NSString.h>

@implementation ImebraDataSet

-(id)initWithImebraDataSet:(imebra::DataSet*)pDataSet
{
    self = [super init];
    if(self)
    {
        m_pDataSet = pDataSet;
    }
    return self;
}

-(id)init
{
    self = [super init];
    if(self)
    {
        m_pDataSet = new imebra::DataSet();
    }
    return self;
}

-(id)initWithTransferSyntax:(NSString*)transferSyntax
{
    self = [super init];
    if(self)
    {
        m_pDataSet = new imebra::DataSet(imebra::NSStringToString(transferSyntax));
    }
    return self;
}

-(void)dealloc
{
    delete m_pDataSet;
#if !__has_feature(objc_arc)
    [super dealloc];
#endif
}

-(ImebraImage*) getImage:(unsigned int) frameNumber error:(NSError**)pError
{
    try
    {
        return [[ImebraImage alloc] initWithImebraImage:m_pDataSet->getImage(frameNumber)];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(ImebraImage*) getImageApplyModalityTransform:(unsigned int) frameNumber error:(NSError**)pError
{
    try
    {
        return [[ImebraImage alloc] initWithImebraImage:m_pDataSet->getImageApplyModalityTransform(frameNumber)];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(void) setImage:(unsigned int)frameNumber image:(ImebraImage*)image quality:(ImebraImageQuality_t)quality error:(NSError**)pError
{
    try
    {
        m_pDataSet->setImage(frameNumber, *(image->m_pImage), (imebra::imageQuality_t)quality);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}


-(ImebraReadingDataHandler*) getReadingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    try
    {
        return [[ImebraReadingDataHandler alloc] initWithImebraReadingDataHandler:m_pDataSet->getReadingDataHandler(*(tagId->m_pTagId), bufferId)];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(ImebraWritingDataHandler*) getWritingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
{
    try
    {
        return [[ImebraWritingDataHandler alloc] initWithImebraWritingDataHandler:m_pDataSet->getWritingDataHandler(*(tagId->m_pTagId), bufferId, (imebra::tagVR_t)tagVR)];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(ImebraWritingDataHandler*) getWritingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    try
    {
        return [[ImebraWritingDataHandler alloc] initWithImebraWritingDataHandler:m_pDataSet->getWritingDataHandler(*(tagId->m_pTagId), bufferId)];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(signed int)getSignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    try
    {
        return m_pDataSet->getSignedLong(*(tagId->m_pTagId), elementNumber);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return 0;
    }
}

-(signed int)getSignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed int)defaultValue error:(NSError**)pError
{
    try
    {
        return m_pDataSet->getSignedLong(*(tagId->m_pTagId), elementNumber, defaultValue);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return 0;
    }
}

-(void)setSignedLong:(ImebraTagId*)tagId newValue:(signed int)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
{
    try
    {
        m_pDataSet->setSignedLong(*(tagId->m_pTagId), newValue, (imebra::tagVR_t)tagVR);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)setSignedLong:(ImebraTagId*)tagId newValue:(signed int)newValue error:(NSError**)pError
{
    try
    {
        m_pDataSet->setSignedLong(*(tagId->m_pTagId), newValue);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}


-(unsigned int)getUnsignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    try
    {
        return m_pDataSet->getUnsignedLong(*(tagId->m_pTagId), elementNumber);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return 0;
    }
}

-(unsigned int)getUnsignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned int)defaultValue error:(NSError**)pError
{
    try
    {
        return m_pDataSet->getUnsignedLong(*(tagId->m_pTagId), elementNumber, defaultValue);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return 0;
    }
}

-(void)setUnsignedLong:(ImebraTagId*)tagId newValue:(unsigned int)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
{
    try
    {
        m_pDataSet->setUnsignedLong(*(tagId->m_pTagId), newValue, (imebra::tagVR_t)tagVR);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)setUnsignedLong:(ImebraTagId*)tagId newValue:(unsigned int)newValue error:(NSError**)pError
{
    try
    {
        m_pDataSet->setUnsignedLong(*(tagId->m_pTagId), newValue);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}


-(double)getDouble:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    try
    {
        return m_pDataSet->getDouble(*(tagId->m_pTagId), elementNumber);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return 0.0f;
    }
}

-(double)getDouble:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(double)defaultValue error:(NSError**)pError
{
    try
    {
        return m_pDataSet->getDouble(*(tagId->m_pTagId), elementNumber, defaultValue);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return 0.0f;
    }
}

-(void)setDouble:(ImebraTagId*)tagId newValue:(double)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
{
    try
    {
        m_pDataSet->setDouble(*(tagId->m_pTagId), newValue, (imebra::tagVR_t)tagVR);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)setDouble:(ImebraTagId*)tagId newValue:(double)newValue error:(NSError**)pError
{
    try
    {
        m_pDataSet->setDouble(*(tagId->m_pTagId), newValue);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}


-(NSString*)getString:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    try
    {
        return imebra::stringToNSString(m_pDataSet->getString(*(tagId->m_pTagId), elementNumber));
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(NSString*)getString:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(NSString*)defaultValue error:(NSError**)pError
{
    try
    {
        return imebra::stringToNSString(m_pDataSet->getString(*(tagId->m_pTagId), elementNumber, imebra::NSStringToString(defaultValue)));
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(void)setString:(ImebraTagId*)tagId newValue:(NSString*)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
{
    try
    {
        m_pDataSet->setString(*(tagId->m_pTagId), imebra::NSStringToString(newValue), (imebra::tagVR_t)tagVR);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)setString:(ImebraTagId*)tagId newValue:(NSString*)newValue error:(NSError**)pError
{
    try
    {
        m_pDataSet->setString(*(tagId->m_pTagId), imebra::NSStringToString(newValue));
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}


-(ImebraAge*)getAge:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    try
    {
        std::unique_ptr<imebra::Age> pAge(m_pDataSet->getAge(*(tagId->m_pTagId), elementNumber));
        return [[ImebraAge alloc] initWithAge:pAge->age units:(ImebraAgeUnit_t)pAge->units];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(ImebraAge*)getAge:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraAge*)defaultValue error:(NSError**)pError
{
    try
    {
        std::unique_ptr<imebra::Age> pAge(m_pDataSet->getAge(*(tagId->m_pTagId), elementNumber, *(imebra::Age*)(defaultValue->m_pAge)));
        return [[ImebraAge alloc] initWithAge:pAge->age units:(ImebraAgeUnit_t)pAge->units];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(void)setAge:(ImebraTagId*)tagId newValue:(ImebraAge*)newValue error:(NSError**)pError
{
    try
    {
        m_pDataSet->setAge(*(tagId->m_pTagId), *(imebra::Age*)(newValue->m_pAge));
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}


-(ImebraDate*)getDate:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    try
    {
        std::unique_ptr<imebra::Date> pDate(m_pDataSet->getDate(*(tagId->m_pTagId), elementNumber));
        return [[ImebraDate alloc] initWithDate:pDate->year
                month:pDate->month
                day:pDate->day
                hour:pDate->hour
                minutes:pDate->minutes
                seconds:pDate->seconds
                nanoseconds:pDate->nanoseconds
                offsetHours:pDate->offsetHours
                offsetMinutes:pDate->offsetMinutes];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(ImebraDate*)getDate:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraDate*)defaultValue error:(NSError**)pError
{
    try
    {
        std::unique_ptr<imebra::Date> pDate(m_pDataSet->getDate(*(tagId->m_pTagId), elementNumber, *(imebra::Date*)(defaultValue->m_pDate)));
        return [[ImebraDate alloc] initWithDate:pDate->year
                month:pDate->month
                day:pDate->day
                hour:pDate->hour
                minutes:pDate->minutes
                seconds:pDate->seconds
                nanoseconds:pDate->nanoseconds
                offsetHours:pDate->offsetHours
                offsetMinutes:pDate->offsetMinutes];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(void)setDate:(ImebraTagId*)tagId newValue:(ImebraDate*)newValue tagVR:(ImebraTagVR_t)tagVR error:(NSError**)pError
{
    try
    {
        m_pDataSet->setDate(*(tagId->m_pTagId), *(imebra::Date*)(newValue->m_pDate), (imebra::tagVR_t)tagVR);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)setDate:(ImebraTagId*)tagId newValue:(ImebraDate*)newValue error:(NSError**)pError
{
    try
    {
        m_pDataSet->setDate(*(tagId->m_pTagId), *(imebra::Date*)(newValue->m_pDate));
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}


@end




