/*
$fileHeader$
*/

/*! \file codecFactory_swig.h
    \brief Declaration of the class used to retrieve the codec able to
		handle the requested transfer syntax (SWIG).

*/

#if !defined(imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_)
#define imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_

#include "dataSet.h"
#include "streamReader.h"
#include "streamWriter.h"
#include "definitions.h"

namespace imebra
{

/// \addtogroup group_swig_bindings
/// @{

class IMEBRA_API CodecFactory
{
public:
    static DataSet load(StreamReader reader, size_t maxSizeBufferLoad);

    enum codecType
    {
        dicom,
        jpeg
    };

    static void save(DataSet dataSet, StreamWriter writer, codecType codecType);
};

///@}

}
#endif // !defined(imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_)
