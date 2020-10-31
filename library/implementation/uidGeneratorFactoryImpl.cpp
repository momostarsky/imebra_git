/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file uidGeneratorFactoryImpl.cpp
    \brief Implementation of the uidGeneratorFactory class.

*/

#include "exceptionImpl.h"
#include "../include/dicomhero/exceptions.h"
#include "uidGeneratorFactoryImpl.h"
#include <string.h>


namespace dicomhero
{

namespace implementation
{

namespace uidGenerators
{


uidGeneratorFactory::forceUidGeneratorFactoryCreation forceUidGeneratorFactoryAllocation;


uidGeneratorFactory::uidGeneratorFactory()
{
}

uidGeneratorFactory& uidGeneratorFactory::getUidGeneratorFactory()
{
    static uidGeneratorFactory factory;
    return factory;
}

void uidGeneratorFactory::registerUIDGenerator(const std::string &generatorName, const std::shared_ptr<baseUidGenerator> &uidGenerator)
{
    std::unique_lock<std::mutex> lockMap(m_lockUidGenerator);

    m_uidGenerators[generatorName] = uidGenerator;

    if(m_defaultUidGenerator == nullptr)
    {
        m_defaultUidGenerator = uidGenerator;
    }
}


std::shared_ptr<baseUidGenerator> uidGeneratorFactory::getUidGenerator(const std::string &generatorName) const
{
    DICOMHERO_FUNCTION_START();

    std::unique_lock<std::mutex> lockMap(m_lockUidGenerator);

    std::map<std::string, std::shared_ptr<baseUidGenerator>>::const_iterator findUidGenerator(m_uidGenerators.find(generatorName));
    if(findUidGenerator == m_uidGenerators.end())
    {
        DICOMHERO_THROW(NonRegisteredUIDGenerator, "UID generator " << generatorName << " was not registered");
    }
    return findUidGenerator->second;

    DICOMHERO_FUNCTION_END();
}


std::shared_ptr<baseUidGenerator> uidGeneratorFactory::getDefaultUidGenerator() const
{
    DICOMHERO_FUNCTION_START();

    std::unique_lock<std::mutex> lockMap(m_lockUidGenerator);

    if(m_defaultUidGenerator == nullptr)
    {
        DICOMHERO_THROW(NonRegisteredUIDGenerator, "No UID generator was registered");
    }

    return m_defaultUidGenerator;

    DICOMHERO_FUNCTION_END();
}

} // uidGenerators

} // implementation

} // imebra
