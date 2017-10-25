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
#include "../include/imebra/objectivec/imebra_nserror.h"
#import "../include/imebra/objectivec/imebra_codecFactory.h"
#import "../include/imebra/objectivec/imebra_dataset.h"
#import "../include/imebra/objectivec/imebra_strings.h"
#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>


@implementation ImebraCodecFactory

+(ImebraDataSet*)load:(NSString*) fileName error:(NSError**)pError
{
    try
    {
        std::unique_ptr<imebra::DataSet> pDataSet(imebra::CodecFactory::load(imebra::NSStringToString(fileName)));
        return [[ImebraDataSet alloc] initWithImebraDataSet:pDataSet.release()];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}


@end




