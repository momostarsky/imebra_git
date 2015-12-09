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

/// \addtogroup group_swig_bindings
/// @{

class CodecFactory
{
public:
    static DataSet load(StreamReader reader, int maxSizeBufferLoad);

    enum codecType
    {
        dicom,
        jpeg
    };

    static void save(DataSet dataSet, StreamWriter writer, codecType codecType);
};

///@}

#endif // !defined(imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_)
