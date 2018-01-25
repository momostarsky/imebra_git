/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcVOILUT__INCLUDED_)
#define imebraObjcVOILUT__INCLUDED_

#import "imebra_transform.h"

@class ImebraImage;
@class ImebraLUT;

@interface ImebraVOILUT: ImebraTransform

    -(id)init;

    -(void)applyOptimalVOI:
        (ImebraImage*)pInputImage
        inputTopLeftX:(unsigned int)inputTopLeftX
        inputTopLeftY:(unsigned int)inputTopLeftY
        inputWidth:(unsigned int)inputWidth
        inputHeight:(unsigned int)inputHeight
        error:(NSError**)pError

        __attribute__((swift_error(nonnull_error)));

    -(void)setCenter:(double)center width:(double)width;

    -(void)setLUT:(ImebraLUT*)pLUT;

    @property (readonly) double center;
    @property (readonly) double width;

@end


#endif // imebraObjcVOILUT__INCLUDED_
