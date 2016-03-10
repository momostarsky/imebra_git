/*
$fileHeader$
*/

/*! \file codecFactory.h
    \brief Declaration of the class used to retrieve the codec able to
        handle the requested transfer syntax.

*/

#if !defined(imebraCodecFactory__INCLUDED_)
#define imebraCodecFactory__INCLUDED_

#include <string>
#include "dataSet.h"
#include "streamReader.h"
#include "streamWriter.h"
#include "definitions.h"

namespace imebra
{

///
/// \brief The CodecFactory class contains a collections of
///         codecs and select the right one when loading
///         or writing data from/to a stream.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CodecFactory
{
public:
    ///
    /// \brief Tries to parse the
    /// \param reader
    /// \param maxSizeBufferLoad
    /// \return
    ///
    static DataSet load(StreamReader& reader, size_t maxSizeBufferLoad);
    static DataSet load(const std::wstring& fileName, size_t maxSizeBufferLoad);
    static DataSet load(const std::string& fileName, size_t maxSizeBufferLoad);

    static void saveImage(
            StreamWriter& destStream,
            const Image& sourceImage,
            const std::string& transferSyntax,
            imageQuality_t imageQuality_t,
            const std::string& dataType,
            std::uint32_t allocatedBits,
            bool bSubSampledX,
            bool bSubSampledY,
            bool bInterleaved,
            bool b2Complement);

    static void save(const DataSet& dataSet, StreamWriter& writer, codecType_t codecType);
    static void save(const DataSet& dataSet, const std::wstring& fileName, codecType_t codecType);
    static void save(const DataSet& dataSet, const std::string& fileName, codecType_t codecType);
};

}
#endif // !defined(imebraCodecFactory__INCLUDED_)
