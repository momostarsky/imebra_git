/*
$fileHeader$
*/

/*! \file transformsChain.h
    \brief Declaration of the class transformsChain.

*/

#if !defined(imebraTransformsChain_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_)
#define imebraTransformsChain_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_

#include <list>
#include "transform.h"

namespace puntoexe
{

namespace imebra
{

namespace transforms
{


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Executes a sequence of transforms.
///
/// Before calling doTransform, specify the sequence
///  by calling addTransform().
/// Each specified transforms take the output of the 
///  previous transform as input.
///
/// When all the transforms have been defined, call
///  endTransformsChain().
///
/// The first defined transform takes the input images
///  defined in the transformsChain object, the last
///  defined transforms uses the output images defined
///  in the transformsChain object.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class transformsChain: public transform
{
public:
	transformsChain();

	// Declare an input image for the transform
	///////////////////////////////////////////////////////////
	virtual void declareInputImage(long imageNumber, ptr<image> pInputImage);

	// Declare an output image for the transform
	///////////////////////////////////////////////////////////
	virtual void declareOutputImage(long imageNumber, ptr<image> pOutputImage);

	// Set the dataset to use for the transformations
	///////////////////////////////////////////////////////////
	virtual void declareDataSet(ptr<dataSet> pDataSet);
	
	// Start the transform
	///////////////////////////////////////////////////////////
	virtual void doTransform();

	/// \brief Add a transform to the transforms chain.
	///
	/// The added transform will take the output of the 
	///  previously added transform as an input image and will
	///  supply its output to the next added transform or as
	///  an output of the transformsChain if it is the
	///  last added transform.
	///
	/// After all the transforms have been added the 
	///  application must call endTransformsChain() before
	///  calling doTransform().
	///
	/// @param pTransform the transform to be added to
	///                    transformsChain
	///
	///////////////////////////////////////////////////////////
	void addTransform(ptr<transform> pTransform);

	/// \brief Returns true if no transform has been defined
	///
	/// @return true if the transforms chain is empty and will
	///               not perform any transformation
	///
	///////////////////////////////////////////////////////////
	virtual bool isEmpty();

	/// \brief Tells to the transformsChain object that no more 
	///         transforms will be added to the chain.
	///
	/// This function MUST be called after all the transforms
	///  have been added to the chain by addTransform() and
	///  before calling doTransform().
	///
	///////////////////////////////////////////////////////////
	void endTransformsChain();

protected:
	typedef std::list<ptr<transform> > tTransformsList;
	tTransformsList m_transformsList;
	bool m_bEndTransformsChainCalled;
};


} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraTransformsChain_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_)
