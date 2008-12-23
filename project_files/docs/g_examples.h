/*
$fileHeader$
*/

/*!

\example dicom2jpeg/dicom2jpeg.cpp
This application converts dicom file into one or more jpeg files.\n
Usage:
\code
dicom2jpeg dicomFileName jpegFileName [-presentation]
\endcode
- dicomFileName: the name of the dicom file to convert
- jpegFileName: the name of the resulting jpeg file
- -presentation: applies the presentation VOI/LUT to the image before saving it
  into the jpeg file


\example dicomdirItems/dicomdirItems.cpp
This application reads a DICOMDIR file and output the file's content in
 XML format to the standard output stream.\n
Usage:
\code
dicomdirItems dicomdirFile
\endcode
- dicomdirFile: the name of the dicom file containing the DICOMDIR structure

In the generated XML file, all the information regarding the DICOMDIR structure
 is enclosed in the root tag <dicomdir>.

Each DICOMDIR item is enclosed in the tag <record>, which has the attributes
 id (unique numeric id) and type (could be "IMAGE", "SERIES", "PATIENT" and
 others. See puntoexe::imebra::directoryRecord::tDirectoryRecordType for
 more information).\n
A <record> item can include:
- a <children> item which includes the children records (a sequence of 0 or
  more <record> items
- a <file> item which specifies the name of the file referenced by the record
- a <class> item which specifies the class UID
- a <instance> item which specifies the instance UID
- a <transfer> item which specifies the transfer syntax
- one or more <group> items, containing the record's tags

A <group> item has the attribute id which specifies the dicom group id in
 decimal format.
A <group> item may contain 0 or more <tag> items.\n
Each tag has the attribute id which specifies the tag id in decimal format.\n
The <tag> item contains the dicom tag's content.



*/