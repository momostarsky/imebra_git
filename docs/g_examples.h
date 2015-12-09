/*
$fileHeader$
*/

/*!

\example dicom2jpeg/dicom2jpeg.cpp
This application converts dicom file into one or more jpeg files, or into movies.\n

<b>FFMPEG</b>
To convert dicom files into movies this application needs the open source
 program ffmpeg, available for Windows and linux platforms.\n
Ffmpeg is not redistributed with Imebra and must be downloaded from here:
- http://ffmpeg.mplayerhq.hu/ (Linux)
- http://ffmpeg.arrozcru.org/ (Windows)
- http://winff.org/html/ (Linux and Windows, with GUI)

<b>Usage</b>
\code
dicom2jpeg dicomFileName jpegFileName [-ffmpeg mpegPath [mpegOptions]]
\endcode
- dicomFileName: the name of the dicom file to convert
- jpegFileName: the name of the resulting jpeg file
- mpegPath: the path to the ffmpeg executable
- mpegOptions: the list of options to be passed to ffmpeg, using the ffmpeg format.
  The input file and the frame rate are added automatically by dicom2jpeg

<b>Examples</b>

The following command converts a dicom file named "input.dcm" to a jpeg file named 
 "output.jpg". If the file output.jpg already exists then it will be overwritten.
\code
dicom2jpeg input.dcm output.jpg
\endcode

The following code converts a multiframe file named "multiframe.dcm" to 
 several jpeg files named "output.jpg", "output1.jpg", "output2.jpg", ...,
 "outputN.jpg" (N=number of frames-1)
\code
dicom2jpeg multiframe.dcm output.jpg
\endcode

The following command converts a multiframe file named "multiframe.dcm" to 
 a swf movie named "movie.swf".\n
Before producing the movie, dicom2jpeg creates a serie of jpg images
 named output0.jpg, output1.jpg, ..., outputN.jpg (N=number of frames-1).
Then dicom2jpeg executes ffmpeg and specifies the created jpg images as
 input images and also specifies the frame rate; other options must be
 specified in the call to dicom2jpeg.
\code
dicom2jpeg multiframe.dcm output.jpg -ffmpeg ffmpeg.exe movie.swf
\endcode




\example dicomdirItems/dicomdirItems.cpp
This application reads a DICOMDIR file and output the file's content in
 XML format to the standard output stream.

<b>Usage</b>
\code
dicomdirItems dicomdirFile
\endcode
- dicomdirFile: the name of the dicom file containing the DICOMDIR structure

In the generated XML file, all the information regarding the DICOMDIR structure
 is enclosed in the root tag "dicomdir".

Each DICOMDIR item is enclosed in the tag "record", which has the attributes
 id (unique numeric id) and type (could be "IMAGE", "SERIES", "PATIENT" and
 others. See puntoexe::imebra::directoryRecord::tDirectoryRecordType for
 more information).\n
A "record" item can include:
- a "children" item which includes the children records (a sequence of 0 or
  more "record" items
- a "file" item which specifies the name of the file referenced by the record
- a "class" item which specifies the class UID
- a "instance" item which specifies the instance UID
- a "transfer" item which specifies the transfer syntax
- one or more "group" items, containing the record's tags

A "group" item has the attribute id which specifies the dicom group id in
 decimal format.
A "group" item may contain 0 or more "tag" items.\n
Each tag has the attribute id which specifies the tag id in decimal format.\n
The "tag" item contains the dicom tag's content.



\example changeTransferSyntax/changeTransferSyntax.cpp
This application reads a dicom file and writes it back to disk using a different
 transfer syntax.

<b>Usage</b>
\code
changeTransferSyntax originalDicomFile outputDicomFile transferSyntaxEnum
\endcode
- originalDicomFile: the name of the dicom file to be converted
- outputDicomFile: the name of the generated dicom file
- transferSyntaxEnum: the id of the transfer syntax used to generate the dicom file\n
  The possible values are:
  - 0 = Explicit VR little endian
  - 1 = Explicit VR big endian
  - 2 = RLE compression
  - 3 = Jpeg baseline (8 bits lossy)
  - 4 = Jpeg extended (12 bits lossy)
  - 5 = Jpeg lossless NH

*/
