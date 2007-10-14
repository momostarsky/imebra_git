/*
$fileHeader$
*/

/*! \file charsetsList.h
    \brief Declaration of the the base class for the classes that need to be
            aware of the Dicom charsets.

*/

#if !defined(imebraCharsetsList_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraCharsetsList_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <stdexcept>
#include <string>
#include <list>

namespace puntoexe
{

namespace imebra
{

/// \brief Defines a list of widechar strings.
///
/// It is used to set or retrieve a list of charsets
///
///////////////////////////////////////////////////////////
typedef std::list<std::wstring> tCharsetsList;


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for the classes that
///         need to deal with the Dicom charsets.
///
/// The class supplies a list of charsets and exposes
///  two functions used to set or retrieve the list of
///  charsets.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class charsetsList
{
public:
	/// \brief Defines the charsets that should be used by
	///         the object.
	///
	/// The valid charsets are:
	/// - ""
    /// - "ISO_IR 6"
	/// - "ISO_IR 100"
	/// - "ISO_IR 101"
	/// - "ISO_IR 109"
	/// - "ISO_IR 110"
	/// - "ISO_IR 144"
	/// - "ISO_IR 127"
	/// - "ISO_IR 126"
	/// - "ISO_IR 138"
	/// - "ISO_IR 148"
	/// - "ISO_IR 13"
	/// - "ISO_IR 166"
	/// - "ISO 2022 IR 6"
	/// - "ISO 2022 IR 100"
	/// - "ISO 2022 IR 101"
	/// - "ISO 2022 IR 109"
	/// - "ISO 2022 IR 110"
	/// - "ISO 2022 IR 144"
	/// - "ISO 2022 IR 127"
	/// - "ISO 2022 IR 126"
	/// - "ISO 2022 IR 138"
	/// - "ISO 2022 IR 148"
	/// - "ISO 2022 IR 13"
	/// - "ISO 2022 IR 166"
	/// - "ISO 2022 IR 87"
	/// - "ISO 2022 IR 159"
	/// - "ISO 2022 IR 149"
	/// - "ISO_IR 192" (UTF-8)
	/// - "GB18030"
	///
	/// @param pCharsetsList  a list of charsets that can be
	///                        used by the dicom object.
	///                       The default charsets must be 
	///                        the first item in the list
	///
	///////////////////////////////////////////////////////////
	virtual void setCharsetsList(tCharsetsList* pCharsetsList) = 0;
	
	/// \brief Retrieve the charsets used by the dicom object.
	///
	/// If during the operation an error is detected (diffetent
	///  objects use different default charsets) then
	///  the exception charsetListExceptionDiffDefault is 
	///  thrown.
	///
	/// @param pCharsetsList  a pointer to a list that will
	///                        be filled with the used 
	///                        charsets
	///
	///////////////////////////////////////////////////////////
	virtual void getCharsetsList(tCharsetsList* pCharsetsList) = 0;

protected:	
	void updateCharsets(tCharsetsList* pCharsetsList, tCharsetsList* pDestinationCharsetsList);
	void copyCharsets(tCharsetsList* pSourceCharsetsList, tCharsetsList* pDestinationCharsetsList);

	tCharsetsList m_charsets;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the class charsetsList.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class charsetsListException: public std::runtime_error
{
public:
	charsetsListException(std::string message): std::runtime_error(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when a conversion from
///         an unicode string causes the dicom dataSet
///         to change its default charset.
///
/// For instace, the default charset is ISO IR 6 but a
///  value written by the application in one tag causes
///  the default charset to switch to ISO 2022 IR 100.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class charsetListExceptionDiffDefault: public charsetsListException
{
public:
	charsetListExceptionDiffDefault(std::string message): charsetsListException(message){}
};


} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraCharsetsList_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)

