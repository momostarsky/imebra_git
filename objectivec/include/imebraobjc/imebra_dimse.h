/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcDimse__INCLUDED_)
#define imebraObjcDimse__INCLUDED_

#import <Foundation/Foundation.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class PresentationContext;
class PresentationContexts;
class AssociationMessage;
class AssociationBase;
class AssociationSCU;
class AssociationSCP;
class DimseCommandBase;
class DimseService;
}
#endif

typedef NS_ENUM(unsigned short, ImebraDimseCommandType_t)
{
    ImebraDimseCStore = 0x1,         ///< C-STORE
    ImebraDimseCGet = 0x10,          ///< C-GET
    ImebraDimseCFind = 0x20,         ///< C-FIND
    ImebraDimseCMove = 0x21,         ///< C-MOVE
    ImebraDimseCCancel = 0xfff,      ///< C-CANCEL
    ImebraDimseCEcho = 0x30,         ///< C-ECHO
    ImebraDimseNEventReport = 0x100, ///< N-EVENT_REPORT
    ImebraDimseNGet = 0x110,         ///< N-GET
    ImebraDimseNSet = 0x120,         ///< N-SET
    ImebraDimseNAction = 0x130,      ///< N-ACTION
    ImebraDimseNCreate = 0x140,      ///< N-CREATE
    ImebraDimseNDelete = 0x150       ///< N-DELETE
};


typedef NS_ENUM(unsigned short, ImebraDimseCommandPriority_t)
{
    ImebraPriorityLow = 0x2,  ///< Low priority
    ImebraPriorityMedium = 0, ///< Medium priority
    ImebraPriorityHigh = 0x1  ///< High priority

};



///
/// \brief The DICOM response status code.
///
//////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned short, ImebraDimseStatusCode_t)
{
    ImebraDimseSuccess = 0,                                           ///< Success
    ImebraDimseUnsupportedOptionalAttributes = 0x0001,                ///< Requested optional Attributes are not supported
    ImebraDimseCannotUpdateperformedProcedureStepObject = 0x0110,     ///< Performed Procedure Step Object may no longer be updated
    ImebraDimseUnsupportedSOPClass = 0x0122,                          ///< SOP Class not Supported
    ImebraDimseOutOfResources = 0xa700,                               ///< Refused: Out of resources
    ImebraDimseOutOfResourcesCannotCalculateNumberOfMatches = 0xa701, ///< Refused: Out of Resources - Unable to calculate number of matches
    ImebraDimseOutOfResourcesCannotPerformSubOperations = 0xa702,     ///< Refused: Out of Resources - Unable to perform sub-operations
    ImebraDimseMoveDestinationUnknown = 0xa801,                       ///< Refused: Move Destination unknown
    ImebraDimseIdentifierDoesNotMatchSOPClass = 0xa900,               ///< Identifier does not match SOP Class
    ImebraDimseSubOperationCompletedWithErrors = 0xb000,              ///< Sub-operations Complete - One or more Failures
    ImebraDimseElementDiscarded = 0xb006,                             ///< Element discarded
    ImebraDimseDatasetDoesNotMatchSOPClass = 0xb007,                  ///< Data Set does not match SOP Class
    ImebraDimseUPSAlreadyCanceled = 0xb304,                           ///< The UPS is already in the requested state of CANCELED
    ImebraDimseCoercedInvalidValuesToValidValues = 0xb305,            ///< Coerced invalid values to valid values
    ImebraDimseUPSStateAlreadyCompleted = 0xb306,                     ///< The UPS is already in the requested state of COMPLETED
    ImebraDimseUnableToProcess = 0xc000,                              ///< Unable to process
    ImebraDimseMoreThanOneMatchFound = 0xc100,                        ///< More than one match found,
    ImebraDimseCannotSupportRequestedTemplate = 0xc200,               ///< Unable to support requested template
    ImebraDimseUPSNotUpdated = 0xc300,                                ///< Refused: The UPS may no longer be updated
    ImebraDimseTransactionUIDNotProvided = 0xc301,                    ///< Refused: The correct Transaction UID was not provided
    ImebraDimseUPSAlreadyInProgress = 0xc302,                         ///< Refused: The UPS is already IN PROGRESS
    ImebraDimseCanScheduleOnlyWithNCreate = 0xc303,                   ///< Refused: The UPS may only become SCHEDULED via N-CREATE, not N-SET or N-ACTION
    ImebraDimseUPSCannotChangeState = 0xc304,                         ///< Refused: The UPS has not met final state requirements for the requested state change
    ImebraDimseInstanceUIDDoesNotExist = 0xc307,                      ///< Specified SOP Instance UID does not exist or is not a UPS Instance managed by this SCP
    ImebraDimseUnknownAETitle = 0xc308,                               ///< Receiving AE-TITLE is Unknown to this SCP
    ImebraDimseUPSNotSchedule = 0xc309,                               ///< Refused: The provided value of UPS State was not SCHEDULED
    ImebraDimseUPSNotInProgress = 0xc310,                             ///< Refused: The UPS is not yet in the "IN PROGRESS" state
    ImebraDimseUPSAlreadyCompleted = 0xc311,                          ///< Refused: The UPS is already COMPLETED
    ImebraDimsePerformerCannotBeContacted = 0xc312,                   ///< Refused: The performer cannot be contacted
    ImebraDimsePerformerDoesNotCancel = 0xc313,                       ///< Refused: Performer chooses not to cancel
    ImebraDimseUnappropriateActionForInstance = 0xc314,               ///< Refused: Specified action not appropriate for specified instance
    ImebraDimseSCPDoesNotSupportEventReports = 0xc315,                ///< Refused: SCP does not support Event Reports
    ImebraDimseCanceled = 0xfe00,                                     ///< Terminated due to Cancel request
    ImebraDimsePending = 0xff00,                                      ///< Pending
    ImebraDimsePendingWithWarnings = 0xff01                           ///< Pending with warnings
};


///
/// \brief Simplified DIMSE response status code, derived from
///        dimseStatusCode_t.
///
//////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned short, ImebraDimseStatus_t)
{
    ImebraDimseStatusSuccess = 0, ///< The operation was completed succesfully
    ImebraDimseStatusWarning = 1, ///< The operation was completed with warnings
    ImebraDimseStatusFailure = 2, ///< The operation failed
    ImebraDimseStatusCancel  = 3, ///< The operation was canceled
    ImebraDimseStatusPending = 4  ///< The operation is still running

};


@class ImebraDataSet;
@class ImebraTagId;
@class ImebraAssociationBase;

@interface ImebraDimseCommandBase: NSObject
#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
   @public
   imebra::DimseCommandBase* m_pDimseCommandBase;
}
    -(id)initWithImebraCommand:(imebra::DimseCommandBase*)pCommand;
#endif

    -(void)dealloc;

    -(ImebraDataSet*)getCommandDataSet:(NSError**)pError;
    -(ImebraDataSet*)getPayloadDataSet:(NSError**)pError;

    -(NSString*)getAbstractSyntax;

    -(NSString*)getAffectedSopInstanceUid:(NSError**)pError;

    -(NSString*)getAffectedSopClassUid:(NSError**)pError;

    -(NSString*)getRequestedSopInstanceUid:(NSError**)pError;

    -(NSString*)getRequestedSopClassUid:(NSError**)pError;

@end


@interface ImebraDimseCommand: ImebraDimseCommandBase

    @property (readonly) unsigned short ID;
    @property (readonly) ImebraDimseCommandType_t commandType;

@end


@interface ImebraDimseResponse: ImebraDimseCommandBase

    @property (readonly) ImebraDimseStatus_t status;
    @property (readonly) unsigned short statusCode;

@end


///
/// \brief Base class for all the partial responses
///        (responses to C-GET, C-MOVE and C-FIND).
///
//////////////////////////////////////////////////////////////////
@interface ImebraCPartialResponse: ImebraDimseResponse

    -(unsigned int)getRemainingSubOperations:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(unsigned int)getCompletedSubOperations:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(unsigned int)getFailedSubOperations:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(unsigned int)getWarningSubOperations:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

@end


@interface ImebraCStoreCommand: ImebraDimseCommand

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(ImebraDimseCommandPriority_t)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        originatorAET:(NSString*)originatorAET
        originatorMessageID:(unsigned short)originatorMessageID
        payload:(ImebraDataSet*)pPayload;

    @property (readonly) NSString* originatorAET;

    @property (readonly) unsigned short originatorMessageID;

@end


@interface ImebraCStoreResponse: ImebraDimseResponse

    -(id)initResponse:(ImebraCStoreCommand*)pCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode;

@end


@interface ImebraCGetCommand: ImebraDimseCommand

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(ImebraDimseCommandPriority_t)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid
        identifier:(ImebraDataSet*)pIdentifier;

@end


@interface ImebraCGetResponse: ImebraCPartialResponse

    -(id)initResponseWithIdentifier:(ImebraCGetCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode
        remainingSubOperations:(unsigned int)remainingSubOperations
        completedSubOperations:(unsigned int)completedSubOperations
        failedSubOperations:(unsigned int)failedSubOperations
        warningSubOperations:(unsigned int)warningSubOperations
        identifier:(ImebraDataSet*)pIdentifier;

    -(id)initResponse:(ImebraCGetCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode
        remainingSubOperations:(unsigned int)remainingSubOperations
        completedSubOperations:(unsigned int)completedSubOperations
        failedSubOperations:(unsigned int)failedSubOperations
        warningSubOperations:(unsigned int)warningSubOperations;

@end


@interface ImebraCFindCommand: ImebraDimseCommand

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(ImebraDimseCommandPriority_t)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid
        identifier:(ImebraDataSet*)pIdentifier;

@end


@interface ImebraCFindResponse: ImebraDimseResponse

    -(id)initResponseWithIdentifier:(ImebraCFindCommand*)pReceivedCommand
        identifier:(ImebraDataSet*)pIdentifier;

    -(id)initResponse:(ImebraCFindCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode;
@end


@interface ImebraCMoveCommand: ImebraDimseCommand

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(ImebraDimseCommandPriority_t)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid
        identifier:(ImebraDataSet*)pIdentifier;
@end

@interface ImebraCMoveResponse: ImebraCPartialResponse

    -(id)initResponseWithIdentifier:(ImebraCMoveCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode
        remainingSubOperations:(unsigned int)remainingSubOperations
        completedSubOperations:(unsigned int)completedSubOperations
        failedSubOperations:(unsigned int)failedSubOperations
        warningSubOperations:(unsigned int)warningSubOperations
        identifier:(ImebraDataSet*)pIdentifier;

    -(id)initResponse:(ImebraCMoveCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode
        remainingSubOperations:(unsigned int)remainingSubOperations
        completedSubOperations:(unsigned int)completedSubOperations
        failedSubOperations:(unsigned int)failedSubOperations
        warningSubOperations:(unsigned int)warningSubOperations;

@end


@interface ImebraCEchoCommand: ImebraDimseCommand

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(ImebraDimseCommandPriority_t)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid;

@end


@interface ImebraCEchoResponse: ImebraDimseResponse

    -(id)initResponse:(ImebraCEchoCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode;

@end


@interface ImebraCCancelCommand: ImebraDimseCommand

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(ImebraDimseCommandPriority_t)priority
        cancelMessageID:(unsigned short)cancelMessageID;


    @property (readonly) unsigned short cancelMessageID;

@end


@interface ImebraNEventReportCommand: ImebraDimseCommand

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        eventID:(unsigned short)eventID;

    -(id)initCommandWithInformation:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        eventID:(unsigned short)eventID
        eventInformation:(ImebraDataSet*)pEventInformation;

    @property (readonly) unsigned short eventID;

@end


@interface ImebraNEventReportResponse: ImebraDimseResponse

    -(id)initResponseWithEventReply:(ImebraNEventReportCommand*)pReceivedCommand
        eventReply:(ImebraDataSet*)pEventReply;

    -(id)initResponse:(ImebraNEventReportCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode;

    @property (readonly) unsigned short eventID;

@end


@interface ImebraNGetCommand: ImebraDimseCommand

    ///
    /// \brief Initializes the N-GET command.
    ///
    /// \param abstractSyntax         the message's abstract syntax
    ///                               (previously negotiated via the
    ///                               PresentationContexts parameter
    ///                               of the AssociationSCP or
    ///                               AssociationSCU constructors)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DimseService::getNextCommandID()
    /// \param requestedSopClassUid    the requested SOP class UID
    /// \param requestedSopInstanceUid the requested SOP instance
    ///                                UID
    /// \param attributeIdentifierList An array of ImebraTagId.
    ///                                The list of identifier tags.
    ///                                An empty list means "all the
    ///                                tags".
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
        attributeIdentifierList:(NSArray*)attributeIdentifierList;

    @property (readonly) NSArray* attributeList;

@end


@interface ImebraNGetResponse: ImebraDimseResponse

    -(id)initResponseWithAttributeList:(ImebraNGetCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode
        attributeList:(ImebraDataSet*)pAttributeList;

    -(id)initResponse:(ImebraNGetCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode;

@end


@interface ImebraNSetCommand: ImebraDimseCommand

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
        modificationList:(ImebraDataSet*)pModificationList;

@end


@interface ImebraNSetResponse: ImebraDimseResponse

    -(id)initResponseWithAttributeList:(ImebraNSetCommand*)pReceivedCommand
        modifiedAttributes:(NSArray*)pModifiedAttributes;

    -(id)initResponse:(ImebraNSetCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode;

    @property (readonly) NSArray* modifiedAttributes;

@end


@interface ImebraNActionCommand: ImebraDimseCommand

    -(id)initCommandWithActionInformation:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
        actionID:(unsigned short)actionID
        actionInformation:(ImebraDataSet*)pActionInformation;

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
        actionID:(unsigned short)actionID;

    @property (readonly) unsigned short actionID;

@end


@interface ImebraNActionResponse: ImebraDimseResponse

    -(id)initResponseWithActionResponse:(ImebraNActionCommand*)pReceivedCommand
        actionReply:(ImebraDataSet*)pActionReply;

    -(id)initResponse:(ImebraNActionCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode;

    @property (readonly) unsigned short actionID;

@end


@interface ImebraNCreateCommand: ImebraDimseCommand

    -(id)initCommandWithAttributeList:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        attributeList:(ImebraDataSet*)pAttributeList;

    -(id)initCommandWithAttributeList:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid;

@end


@interface ImebraNCreateResponse: ImebraDimseResponse

    -(id)initResponseWithAttributeList:(ImebraNCreateCommand*)pReceivedCommand
        attributeList:(ImebraDataSet*)pAttributeList;

    -(id)initResponseWithAffectedSopInstanceAndAttributeList:(ImebraNCreateCommand*)pReceivedCommand
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        attributeList:(ImebraDataSet*)pAttributeList;

    -(id)initResponseWithAffectedSopInstance:(ImebraNCreateCommand*)pReceivedCommand
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid;

    -(id)initResponse:(ImebraNCreateCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode;

@end


@interface ImebraNDeleteCommand: ImebraDimseCommand

    -(id)initCommand:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid;

@end


@interface ImebraNDeleteResponse: ImebraDimseResponse

    -(id)initResponse:(ImebraNDeleteCommand*)pReceivedCommand
        responseCode:(ImebraDimseStatusCode_t)responseCode;

@end


@interface ImebraDimseService: NSObject
#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
   @public
   imebra::DimseService* m_pDimseService;
}

#endif

    -(id)init:(ImebraAssociationBase*)pAssociation;

    -(void)dealloc;

    ///
    /// \brief Returns the negotiated transfer syntax for a specific
    ///        abstract syntax.
    ///
    /// This method is multithread safe.
    ///
    /// \param abstractSyntax the abstract syntax for which the
    ///                       transfer syntax is needed
    /// \return the negotiated transfer syntax for the specified
    ///         abstract syntax
    ///
    //////////////////////////////////////////////////////////////////
    -(NSString*)getTransferSyntax:(NSString*)abstractSyntax error:(NSError**)pError;

    ///
    /// \brief Retrieves an ID that can be used on the next command
    ///        sent through this DimseService object.
    ///
    /// This method is multithread safe.
    ///
    /// \return an ID that can be used as command ID on a command sent
    ///         through this DimseService object
    ///
    //////////////////////////////////////////////////////////////////
    -(unsigned short)getNextCommandID;

    ///
    /// \brief Retrieves the next incoming DICOM command.
    ///
    /// The command blocks until the command is available or until
    /// the association is closed, either by the connected peer or
    /// by other means (e.g because of the DIMSE timeout), in which
    /// case the exception StreamEOFError is thrown.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// This method can be called by several threads at once:
    /// each thread will receive a DIMSE command and can reply
    /// to the command via sendCommandOrResponse().
    ///
    /// The underlying AssociationBase object will take care of
    /// limiting the number of incoming command according to the
    /// maximum number of performed operation negotiated for
    /// the association.
    ///
    /// Throws StreamEOFError if the association is closed while the
    /// method is waiting for an incoming command.
    ///
    /// \return the next incoming DICOM command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraDimseCommand*)getCommand:(NSError**)pError;

    ///
    /// \brief Sends a DICOM command or response through the
    ///        association.
    ///
    /// This method is multithread safe.
    ///
    /// \param pCommand the command or response to send
    ///
    //////////////////////////////////////////////////////////////////
    -(void)sendCommandOrResponse:(ImebraDimseCommandBase*)pCommand error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Wait for the response for the specified C-STORE
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent C-CSTORE command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraCStoreResponse*)getCStoreResponse:(ImebraCStoreCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified C-GET
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent C-GET command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraCGetResponse*)getCGetResponse:(ImebraCGetCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified C-FIND
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent C-FIND command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraCFindResponse*)getCFindResponse:(ImebraCFindCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified C-MOVE
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent C-MOVE command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraCMoveResponse*)getCMoveResponse:(ImebraCMoveCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified C-ECHO
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent C-ECHO command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraCEchoResponse*)getCEchoResponse:(ImebraCEchoCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-EVENT-REPORT
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent N-EVENT-REPORT command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraNEventReportResponse*)getNEventReportResponse:(ImebraNEventReportCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-GET
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent N-GET command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraNGetResponse*)getNGetResponse:(ImebraNGetCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-SET
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent N-SET command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraNSetResponse*)getNSetResponse:(ImebraNSetCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-ACTION
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent N-ACTION command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraNActionResponse*)getNActionResponse:(ImebraNActionCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-CREATE
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent N-CREATE command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraNCreateResponse*)getNCreateResponse:(ImebraNCreateCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-DELETE
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// \param pCommand the sent N-DELETE command for which to
    ///                wait for a response
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(ImebraNDeleteResponse*)getNDeleteResponse:(ImebraNDeleteCommand*)pCommand error:(NSError**)pError;

@end

#endif // imebraObjcDimse__INCLUDED_
