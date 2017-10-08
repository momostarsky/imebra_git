/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file acse.cpp
    \brief Implementation of the the ACSE classes.
*/

#include "../include/imebra/acse.h"
#include "../include/imebra/streamReader.h"
#include "../include/imebra/streamWriter.h"
#include "../include/imebra/dataSet.h"
#include "../implementation/acseImpl.h"

namespace imebra
{

PresentationContext::PresentationContext(const std::string& abstractSyntax):
    m_pPresentationContext(std::make_shared<implementation::presentationContext>(abstractSyntax))
{
}

PresentationContext::PresentationContext(const std::string& abstractSyntax, bool bSCURole, bool bSCPRole):
    m_pPresentationContext(std::make_shared<implementation::presentationContext>(abstractSyntax, bSCURole, bSCPRole))
{
}

void PresentationContext::addTransferSyntax(const std::string& transferSyntax)
{
    m_pPresentationContext->addTransferSyntax(transferSyntax);

}

PresentationContext::~PresentationContext()
{
}

PresentationContexts::PresentationContexts():
    m_pPresentationContexts(std::make_shared<implementation::presentationContexts>())
{
}

PresentationContexts::~PresentationContexts()
{

}

void PresentationContexts::addPresentationContext(const PresentationContext& presentationContext)
{
    m_pPresentationContexts->m_presentationContexts.push_back(presentationContext.m_pPresentationContext);
}



AssociationMessage::AssociationMessage(std::shared_ptr<implementation::associationMessage> pMessage):
    m_pMessage(pMessage)
{
}

AssociationMessage::AssociationMessage(const std::string& abstractSyntax):
    m_pMessage(std::make_shared<implementation::associationMessage>(abstractSyntax))
{
}

std::string AssociationMessage::getAbstractSyntax() const
{
    return m_pMessage->abstractSyntax;
}

DataSet* AssociationMessage::getCommand() const
{
    return new DataSet(m_pMessage->dataSets.front());
}

DataSet* AssociationMessage::getPayload() const
{
    IMEBRA_FUNCTION_START();

    if(m_pMessage->dataSets.size() != 2)
    {
        IMEBRA_THROW(AcseNoPayloadError, "Payload not available");
    }
    return new DataSet(m_pMessage->dataSets.back());

    IMEBRA_FUNCTION_END();
}

bool AssociationMessage::hasPayload() const
{
    return m_pMessage->dataSets.size() > 1;
}

void AssociationMessage::addDataSet(const DataSet& dataSet)
{
    m_pMessage->dataSets.push_back(dataSet.m_pDataSet);
}



AssociationBase::AssociationBase()
{

}

AssociationBase::~AssociationBase()
{

}

AssociationMessage* AssociationBase::getCommand()
{
    return new AssociationMessage(m_pAssociation->getCommand());
}

AssociationMessage* AssociationBase::getResponse(unsigned long messageId)
{
    return new AssociationMessage(m_pAssociation->getResponse(messageId));
}

void AssociationBase::sendMessage(const AssociationMessage& messageDataSet)
{
    m_pAssociation->sendMessage(messageDataSet.m_pMessage);
}

void AssociationBase::release()
{
    m_pAssociation->release();
}

void AssociationBase::abort()
{
    m_pAssociation->abort(implementation::acsePDUAAbort::reason_t::serviceUser);
}


AssociationSCU::AssociationSCU(
        const std::string& thisAET,
        const std::string& otherAET,
        std::uint32_t invokedOperations,
        std::uint32_t performedOperations,
        const PresentationContexts& presentationContexts,
        StreamReader& pInput,
        StreamWriter& pOutput)
{
    m_pAssociation = std::make_shared<implementation::associationSCU>(
                presentationContexts.m_pPresentationContexts,
                thisAET,
                otherAET,
                invokedOperations,
                performedOperations,
                pInput.m_pReader,
                pOutput.m_pWriter);
}


AssociationSCP::AssociationSCP(
        const std::string& thisAET,
        std::uint32_t invokedOperations,
        std::uint32_t performedOperations,
        const PresentationContexts& presentationContexts,
        StreamReader& pInput,
        StreamWriter& pOutput)
{
    m_pAssociation = std::make_shared<implementation::associationSCP>(
                presentationContexts.m_pPresentationContexts,
                thisAET,
                invokedOperations,
                performedOperations,
                pInput.m_pReader,
                pOutput.m_pWriter);
}




}
