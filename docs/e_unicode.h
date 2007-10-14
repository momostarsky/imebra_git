/*
$fileHeader$
*/

/*!

\page imebra_unicode Imebra & Unicode

\section add_to_project_introduction Introduction

The Dicom standard supports several charsets, including the unicode (UTF8 encoded).

Imebra uses the following approach when dealing with tags that could have been 
 encoded using one of the Dicom charsets:
- when the dataset is loaded (see \ref puntoexe::imebra::dataSet), a special 
   attribute in all the tags is updated with the charsets supported by the dataset.
- when a dataset is created, the application can decide the charsets that can be 
   used in the dataset: all the new tags will use the charsets specified in the 
   dataset
- when an application writes a value in a tag, it can change the tag's charsets: 
   before a dataset is saved all the tag's charsets are analyzed and checked for 
   inconsistence or invalid charsets combinations and the tag 0008,0005 is 
   updated with the dataset's charsets.

The conversion from/to the dataSet defined charsets happens when a dataHandler 
 is created or destroyed: while the dataHandler is "alive", the strings are 
 kept in unicode format and converted to ansi if a non-unicode function is called.

The conversion uses MultiByteToWideChars/WideCharsToMultiByte on Windows and 
 iconv on Posix systems.


\section imebra_unicode_dataset How to initalize the dataSet

When the dataSet is loaded (see \ref puntoexe::imebra::dataSet) from a stream, 
 then the list of used charsets will be set automatically: immediatly after the download 
 the tag 0008,0005 is checked and its content is transferred in the charsets list.

If the dataSet is created by the application then the list of charsets should be 
 specified: just create a list with the type \ref puntoexe::imebra::tCharsetsList 
 (is a std::list of std::wstring) and fill the list with the charsets that should 
 be stored in the tag 0008,0005, then pass the list to the function 
 dataSet::setCharsetsList() (see \ref puntoexe::imebra::charsetsList::setCharsetsList() 
 since dataSet derives from \ref puntoexe::imebra::charsetsList).

If the application writes in the dataSet some values that need different charsets
 from the ones already specified, then new charsets will be added to the dataSet
 if they are compatible with the charsets already specified. If the needed charsets
 cannot be added then an exception of type \ref puntoexe::imebra::charsetsListException 
 will be thrown; if a transaction is active when the exception is thrown then all the 
 modifications will be rolled back (see \ref imebra_transactions).


\section imebra_unicode_wstring The std::wstring

Imebra uses the std::wstring classes to deal with Unicode strings.

std::wstring stores a string of wchar_t elements; because a wchar_t can store
 only 16 bits values and Unicode uses 20 bits values, the strings are encoded
 using UTF-16.

This means that the Unicode values up to 0xFFFF are encoded using one wchar_t,
 while the Unicode values above 0xFFFF are encoded in two wchar_t elements.

*/