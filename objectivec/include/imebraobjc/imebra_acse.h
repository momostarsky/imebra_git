/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcAcse__INCLUDED_)
#define imebraObjcAcse__INCLUDED_

#import <Foundation/Foundation.h>

#import "imebra_dataset.h"
#import "imebra_streamReader.h"
#import "imebra_streamWriter.h"

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class PresentationContext;
class PresentationContexts;
class AssociationMessage;
class AssociationBase;
class AssociationSCU;
class AssociationSCP;
}
#endif

@interface ImebraPresentationContext: NSObject
#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::PresentationContext* m_pPresentationContext;
}

    -(id)initWithImebraPresentationContext:(imebra::PresentationContext*)pPresentationContext;
#endif

    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax;

    -(id)initWithRole:(NSString*)abstractSyntax scuRole:(BOOL)bSCURole scpRole:(BOOL)bSCPRole;

    -(void)dealloc;

    -(void)addTransferSyntax:(NSString*)transferSyntax;

@end


@interface ImebraPresentationContexts: NSObject
#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::PresentationContexts* m_pPresentationContexts;
}

    -(id)initWithImebraPresentationContexts:(imebra::PresentationContexts*)pPresentationContexts;
#endif

    -(id)init;

    -(void)dealloc;

    -(void)addPresentationContext:(ImebraPresentationContext*)pPresentationContext;

@end


@interface ImebraAssociationMessage: NSObject
#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::AssociationMessage* m_pAssociationMessage;
}

    -(id)initWithImebraAssociationMessage:(imebra::AssociationMessage*)pAssociationMessage;
 #endif

    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax;

    -(void)dealloc;

    -(ImebraDataSet*)getCommand:(NSError**)pError;

    -(ImebraDataSet*)getPayload:(NSError**)pError;

    -(BOOL)hasPayload;

    -(void)addDataSet:(ImebraDataSet*)pDataSet error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    @property (readonly) NSString* abstractSyntax;

@end


@interface ImebraAssociationBase: NSObject
#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::AssociationBase* m_pAssociation;
}

#endif

    -(void)dealloc;

    -(ImebraAssociationMessage*)getCommand:(NSError**)pError;

    -(ImebraAssociationMessage*)getResponse:(unsigned int)messageId error:(NSError**)pError;

    -(void)sendMessage:(ImebraAssociationMessage*)pMessage error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)release:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)abort:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(NSString*)getTransferSyntax:(NSString*)abstractSyntax error:(NSError**)pError;

    @property (readonly) NSString* thisAET;

    @property (readonly) NSString* otherAET;

@end


@interface ImebraAssociationSCU: ImebraAssociationBase

    -(id)init:(NSString*)thisAET otherAET:(NSString*)otherAET
                                    maxInvokedOperations:(unsigned int)invokedOperations
                                    maxPerformedOperations:(unsigned int)performedOperations
                                    presentationContexts:(ImebraPresentationContexts*)presentationContexts
                                    reader:(ImebraStreamReader*)pInput
                                    writer:(ImebraStreamWriter*)pOutput
                                    dimseTimeoutSeconds:(unsigned int)dimseTimeoutSeconds error:(NSError**)pError;
@end


@interface ImebraAssociationSCP: ImebraAssociationBase

    -(id)init:(NSString*)thisAET
                                    maxInvokedOperations:(unsigned int)invokedOperations
                                    maxPerformedOperations:(unsigned int)performedOperations
                                    presentationContexts:(ImebraPresentationContexts*)presentationContexts
                                    reader:(ImebraStreamReader*)pInput
                                    writer:(ImebraStreamWriter*)pOutput
                                    dimseTimeoutSeconds:(unsigned int)dimseTimeoutSeconds
                                    artimTimeoutSeconds:(unsigned int)artimTimeoutSeconds error:(NSError**)pError;
@end


#endif // imebraObjcAcse__INCLUDED_
