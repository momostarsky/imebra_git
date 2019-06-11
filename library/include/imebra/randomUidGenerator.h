/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/


#if !defined(imebraRandomUIDGenerator__INCLUDED_)
#define imebraRandomUIDGenerator__INCLUDED_

#include "baseUidGenerator.h"
#include "definitions.h"

namespace imebra
{

///
/// \brief An input stream that reads data from a memory region.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API RandomUIDGenerator : public BaseUIDGenerator
{

public:
    /// \brief Constructor.
    ///
    /// \param memory the memory region from which the stream will read the data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit RandomUIDGenerator(const std::string& root, std::uint32_t departmentId, std::uint32_t modelId);

    ///
    /// \brief Copy constructor.
    ///
    /// \param source source MemoryStreamInput object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    RandomUIDGenerator(const RandomUIDGenerator& source);

};

}
#endif // !defined(imebraRandomUIDGenerator__INCLUDED_)
