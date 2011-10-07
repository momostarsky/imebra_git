/*
$fileHeader$
*/

/*! \file codecFactory.h
    \brief Declaration of the class used to retrieve the codec able to
	        handle the requested transfer syntax.

*/

#if !defined(imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_)
#define imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_

#include "../../imebra/include/codecFactory.h"
#include "dataSet.h"
#include "streamReader.h"


class codecFactory
{
public:
	dataSet load(streamReader reader, unsigned long maxSizeBufferLoad);
};
#endif // !defined(imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_)
