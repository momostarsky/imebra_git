/*
$fileHeader$
*/

/*! \file modalityVOILUT.h
    \brief Declaration of the class ModalityVOILUT.

*/

#if !defined(imebraModalityVOILUT__INCLUDED_)
#define imebraModalityVOILUT__INCLUDED_

#include "transform.h"
#include "dataSet.h"
#include "definitions.h"

namespace imebra
{

class IMEBRA_API ModalityVOILUT: public Transform
{
    ModalityVOILUT(const ModalityVOILUT&) = delete;
    ModalityVOILUT& operator=(const ModalityVOILUT&) = delete;

public:
    ModalityVOILUT(const DataSet& dataset);
};

}

#endif // imebraModalityVOILUT__INCLUDED_
