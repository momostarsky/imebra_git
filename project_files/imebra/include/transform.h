/*
$fileHeader$
*/

/*! \file transform.h
    \brief Declaration of the base class used by all the transforms.
 
*/

#if !defined(imebraTransform_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_)
#define imebraTransform_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_

#include "baseTransform.h"
#include "dataSet.h"

#include <map>


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

class image;

/// \namespace puntoexe::imebra::transforms
/// \brief This namespace contains all the transforms
///         of the imebra library.
///
/// A transform is an object that takes some images as
///  input parameters and returns some images as a
///  result of a transformation or analysis.
///
///////////////////////////////////////////////////////////
namespace transforms
{

///////////////////////////////////////////////////////////
/// \brief This is the base class for the transforms.
///
/// A transform can process several input images and
///  reply with several output images.
///
/// Sometimes the transform needs to know the dataSet
///  related to the images being processed; in this case
///  the function transform::declareDataSet() must be
///  called.
///
///////////////////////////////////////////////////////////
class transform : public baseTransform
{

public:
	/// \brief Declare an input image for the transform
	///
	/// The transform will use the input image for its
	///  purposes when the application will call 
	///  doTransform().
	///
	/// @param imageNumber the transform can work with more
	///                     than one input image.
	///                    This parameter specifies the
	///                     parameter's ID.
	///                    If another image was already stored
	///                     with this parameter's ID, then it
	///                     will be released.
	/// @param pInputImage the image to use as the transform's 
	///                     input parameter
	///
	///////////////////////////////////////////////////////////
	virtual void declareInputImage(long imageNumber, ptr<image> pInputImage);

	/// \brief Declare an output image for the transform
	///
	/// The transform will store the results in the output
	///  image.
	///
	/// @param imageNumber the transform can work with more
	///                     than one output image.
	///                    This parameter specifies the
	///                     parameter's ID.
	///                    If another image was already stored
	///                     with this parameter's ID, then it
	///                     will be released
	/// @param pOutputImage the image to use as the transform's 
	///                     output parameter
	///
	///////////////////////////////////////////////////////////
	virtual void declareOutputImage(long imageNumber, ptr<image> pOutputImage);
	
	/// \brief Retrieve an image used as input parameter.
	///
	/// @param imageNumber the ID of the input parameter to
	///                     retrieve
	/// @return            the image used as input parameter
	///                     or 0 if the input parameter has
	///                     not been defined
	///
	///////////////////////////////////////////////////////////
	ptr<image> getOutputImage(long imageNumber);

	/// \brief Retrieve an image used as output parameter.
	///
	/// @param imageNumber the ID of the output parameter to
	///                     retrieve.
	/// @return            the image used as output parameter
	///                     or 0 if the output parameter has
	///                     not been defined
	///
	///////////////////////////////////////////////////////////
	ptr<image> getInputImage(long imageNumber);


	/// \brief Executes the transform.
	///
        /// \deprecated Use baseTransform::doTransform() instead.
        ///
	///////////////////////////////////////////////////////////
	virtual void doTransform();

private:
	typedef std::map<int, ptr<image> > tImagesMap;
	tImagesMap m_inputImages;
	tImagesMap m_outputImages;

};


///////////////////////////////////////////////////////////
/// \brief This is the base class of the exceptions thrown
///         by the classes derived from transform.
///
///////////////////////////////////////////////////////////
class transformException: public std::runtime_error
{
public:
	transformException(const std::string& message): std::runtime_error(message){}
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown by the transforms that
///         need a defined dataSet (see declareDataSet())
///         but don't have any.
///
///////////////////////////////////////////////////////////
class transformExceptionDataSetNotDefined: public transformException
{
public:
	transformExceptionDataSetNotDefined(const std::string& message): transformException(message){}
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown by a transforms when an
///         input image is required but hasn't been defined
///         (see declareInputImage()).
///
///////////////////////////////////////////////////////////
class transformExceptionDataInputImageDefined: public transformException
{
public:
	transformExceptionDataInputImageDefined(const std::string& message): transformException(message){}
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown by a transforms when an
///         output image is required but hasn't been 
///         defined (see declareOutputImage()).
///
///////////////////////////////////////////////////////////
class transformExceptionOutputImageNotDefined: public transformException
{
public:
	transformExceptionOutputImageNotDefined(const std::string& message): transformException(message){}
};


} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraTransform_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_)
