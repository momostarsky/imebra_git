/*
$fileHeader$
*/

/*! \mainpage $imebraVersion$ open source Dicom library

\image html logo.png
\image latex logo.png "" width=10cm

\section copyright Copyright

Copyright 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011 by Paolo Brandoli.

Imebra is available for free under the \ref freebsd_license.

You can download the latest version of imebra from http://imebra.com


\section section_donation Donations

Want to keep Imebra free and updated? Consider making a donation to the developer.

- <a href="https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=paolo%2ebrandoli%40gmail%2ecom&lc=GB&item_name=Imebra&currency_code=EUR&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHosted">Donations via Paypal</a>
- <a href="http://www.amazon.co.uk/wishlist/1GESO4Z6VYG4W">Amazon wishlist</a>


\section section_Introduction Introduction

Imebra is an open source Dicom library.
The library has been designed to handle Dicom files, but it includes also some
 classes that manage jpeg and other image files.

At the moment the library provides the following features:
- dicom files parser and builder
- jpeg files parser and builder
- image decompression and compression in the following formats:
  - jpeg baseline (8 bits per color channel lossy)
  - jpeg baseline extended (12 bits per color channel lossy)
  - jpeg lossless (up to 16 bits per color channel lossless)
  - raw dicom (up to 16 bits per color channel lossless)
  - rle dicom (up to 16 bits per color channel lossless)
- multi platform
- self contained (the library uses only functions from the standard C library
                  and the standard template library)
- color space conversion
- support for nested datasets (sequences)
- support for Unicode and different Dicom charsets
- DICOMDIR parser and writer
- support for transactions
- load larger tags only when necessary


\section is_not What Imebra does NOT do?

- the library doesn't check for a Dicom stream validity; this feature will be
   introduced with the support for dicom objects.
- the library doesn't support network communication


\section start Where to start

After reading the \ref license_agreement, you should read the \ref quick_tour
 and the section \ref imebra_structure.

A guide that will help you to include Imebra in your project can be
 found in \ref add_to_project.

If you want to build the examples and the test units you should read \ref compile_examples.

A detailed reference of the C++ classes that compose Imebra is included in
 this manual.


\section changeLog Changes log

\subsection version_current Changes for version $imebraVersion$

- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/88">#88</a> (32-bit warnings / general pointer size concerns)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/90">#90</a> (transactionsManager doesn't lock the manager)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/92">#92</a> (Wrong check for ac frequencies in the IDCT method of the Jpeg codec)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/93">#93</a> (Some files contain jpeg compressed images without the jpeg termination tag)
- Minor optimizations in the jpegCodec::readBlock method
- Minor optimizations in the template function dataHandlerNumeric::copyFromInt32Interleaved
- Remove exception logging functions from the inline method streamReader::readBits()
- Corrected modalityVOILUT to accept only monochromatic images


\subsection version_2011_09_18_22_24_41 Changes for version 2011-09-18_22-24-41

- Updated to compile with Visual Studio on x64 arch
- Improved performances of IDCT
- Improved performance of Jpeg decoder
- Improved the performances of the huffman decoder


\subsection version_2011_06_29_23_24_13 Changes for version 2011-06-29_23-24-13

- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/84">#84</a> (VOILUT returns always a MONOCHROME2 image)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/85">#85</a> (GetImage() fails when a file contains a single frame splitted across several buffers and the offset table is empty)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/86">#86</a> (The automatic build doesn't set the product name in the source files)


\subsection version_2011_04_18_22_48_29 Changes for version 2011-04-18_22-48-29

- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/73">#76</a> (The example in quick_tour_tag Let's read or set a tag in the dataSet is wrong)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/77">#77</a> (modalityVOILUT::isEmpty returns true when a LUT is used in the transform)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/78">#78</a> (When VOILUT is empty it should simply copy the input image into the output one)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/79">#79</a> (In puntoexe::imebra::transforms::modalityVOILUT there is no need to call DeclareDataSet)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/82">#82</a> (Finding the index.html file in the documentation folder is difficult)
- Added explanatory images for the documentation of the class drawBitmap
- Updated the documentation for puntoexe::imebra::drawBitmap
- Updated the test units for puntoexe::imebra::drawBitmap
- Added several Dicom tags used in radiology to dicomDict.cpp.\n
  Patch by Derek Dolney, Ph.D. (Division of Medical Physics - Department of Radiation Oncology - University of Pennsylvania)
- All the transforms now act as puntoexe::imebra::transforms::transformHighBit when puntoexe::imebra::transforms::transform::isEmpty() returns true


\subsection version_2011_03_01_21_54_48 Changes for version 2011-03-01_21-54-48


- Improved tests of the Dicom codec (now test all the bit depths)
- Added detailed documentation for compilation of the examples
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/73">#73</a> (The Dicom codec returns black images when highbit=31)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/74">#74</a> (When the transfer syntax as implicit VRs then the VR for image data should be OW)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/74">#75</a> (The dataset doesn't set the b2complement flag when the data is stored in signed 32bit)


\subsection version_2011_01_22_13_58_55 Changes for version 2011-01-22_13-58-55


- License changed from GPL3 to FreeBSD
- new folders structure
- puntoexe::imebra::image now returns a puntoexe::imebra::handlers::dataHandlerNumericBase instead of puntoexe::imebra::handlers::imageHandler
- breaking changes in puntoexe::imebra::handlers::dataHandlerNumeric
- breaking changes in puntoexe::imebra::transforms::transform (now the transforms work with new dataHandlerNumeric)
- The palette tags now are embedded in the puntoexe::imebra::image objects
- Added the example changeTransferSyntax
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/59">#59</a> (Old Dicom formats may not be recognized)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/61">#61</a> (directoryRecord must have a method setFilePart())
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/62">#62</a> (Speed up the drawBitmap class)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/63">#63</a> (Regression when reading uncompressed non interleaved images)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/65">#65</a> (When a tag is set twice using the default VR in a transaction then the second write operation resets the VR)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/66">#66</a> (The dataset doesn't consider the planar configuration)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/67">#67</a> (When an undefined-length sequence doesn't contains the end-of-sequence then an exception is thrown when the end of the file is reached)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/68">#68</a> (drawBitmap should be able to draw b/w images)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/71">#71</a> (File Meta should always use Explicit VR Little Endian Transfer Syntax)


\subsection version_0_0_48 Changes for version 0.0.48


- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/44">#44</a> (Add the "const" modifier to all the relevant functions in the data handlers)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/55">#55</a> (Add const qualifier to functions that require them)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/56">#56</a> (The external lock in baseObject may create circular references)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/57">#57</a> (RGBToPALETTECOLOR causes memory leaks)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/58">#58</a> (The destructors of objects derived from baseObject must be protected, since they can be deleted only by themself)
- Increased the speed of CopyFromInt32Interleaved
- Increased the speed of dicomCodec::ReadPixel when bitsAllocated == 8 or 16
- Improved the speed of streamWriter::write()
- Increased the speed of streamWriter::writeBits
- The file reading related function now return the read byte or bits by value 


\subsection version_0_0_47 Changes for version 0.0.47


- Makefiles for the example applications are being provided
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/33">#33</a> (When launched without parameters, dicomdirItems should display the version)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/42">#42</a> (When a dicomdir destructor is called, the it delete all the children elements. This may cause a stack overflow when an element call release on the next sibling item and the number of siblings is high)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/46">#46</a> (Checking for LUT validity will help dicom2jpeg to ignore the LUT if it contains invalid data)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/49">#49</a> (The codepage "CHAR" used to indicate the locale charset in charsetConversion.cpp causes an exception during the initialization of ICONV. The usage of "" instead of "char" works properly)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/50">#50</a> (mbxInt32 and imbxUint32 are wrongly mapped to long and unsigned long. It should be mapped to int and unsigned int)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/51">#51</a> (wrong parameters in memset)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/52">#52</a> (The charset conversion uses different error reporting in ICONV and Windows API)


\subsection version_0_0_46 Changes for version 0.0.46


- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/32">#32</a> (When launched without parameters, dicom2jpeg should display the version)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/34">#34</a> (The on-line documentation should have to Google Analytics tracking code)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/37">#37</a> (Change the title of the documentation to: Imebra - Open source dicom
  library)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/39">#39</a> (The class dataHandlerNumeric calculates the wrong size)


\subsection version_0_0_45 Changes for version 0.0.45


- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/1">#1</a> (The library's version should be visible in the source code)
- Added DICOMDIR creator/parser
- Added an example that extract a DICOMDIR to an XML file
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/4">#4</a> (A sequence tag should have the type set to SQ, but the
  writer uses the first buffer's type, therefore the data type is incorrect)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/5">#5</a> (When writing sequences, the tag's length is not calculated correctly)
- Fixes <a href="http://bitbucket.org/puntoexe/imebra/issue/6">#6</a> (dicomCodec::getDataSetLength doesn't calculate the correct size)
- dicom2jpeg can now invoke ffmpeg and create movies
- Mercurial is now used as version control (was SVN)
- Corrected documentation
- Changed open source license to Affero GPL 3


\subsection version_0_0_44 Changes for version 0.0.44 (Beta)


- Added the function puntoexe::imebra::transforms::VOILUT::getCenterWidth()
- The jpegCodec returns an image with color space "YBR_FULL" when the image is
  compressed in lossy mode and the dataset specifies the color space "RGB"
- Enhanced precision in the RGB to YBR_FULL color conversion
- Enhanced precision in the YBR_FULL to RGB color conversion
- Several optimization in the uncompressed Dicom image decoder
- Added the class puntoexe::imebra::trasforms::transformBuffersInPlace
- puntoexe::imebra::VOILUT and puntoexe::imebra::modalityVOILUT now derive
  from puntoexe::imebra::trasforms::transformBuffersInPlace
- puntoexe::imebra::viewHelper releases the dataset when no images are displayed
- Several optimizations in the Jpeg image decoder
- puntoexe::streamReader::read() throws an exception when the end of file is
  reached
- added puntoexe::streamReader::endReached()
- Several optimizations in puntoexe::streamReader
- Several optimizations in the Huffman decoder


\subsection version_0_0_41 Changes for version 0.0.41 (Alpha)


- Added the example dicom2jpeg


\subsection version_0_0_40 Changes for version 0.0.40 (Alpha)


- Closes #12 (Subsampled images are saved/loaded incorrectly by the jpeg codec)
- Closes #13 (When saving a jpeg image from a dataset and it doesn't need to be converted an exception is thrown)
- Closes #14 (When saving an image the subsampling flags don't match the quality)


\subsection version_0_0_38 Changes for version 0.0.38 (Alpha)


- Removed dependence from charsetsList in data, buffer, dataSet, dataGroup, dataHandler
- Closes #9 (The lossless jpeg codec saves corrupted images)
- Closes #10 (A basic offset table is added even when it shouldn't)
- Now non encapsulated images are saved one after another even when their length is odd: no padding bytes are inserted
- closes #11 (The 32 bits tag's length is truncated (only the lower 16 bits are correct) )
- The images build during the test units had a reduced range. Corrected
- Now the jpeg codec creates the offset table when loading an image


\subsection version_0_0_36 Changes for version 0.0.36 (Alpha)


- Closes #7 (memoryPool isn't thread safe)
- The memory string now is managed by an auto_ptr
- In the memoryPool minimized the number of moved pointers when a memory object is reused
- The dataSet doesn't need to retrieve the images handlers anymore when updating the offsets table
- The dicom codec doesn't need to retrieve the handlers anymore when calculating the tag size
- viewHelper now accepts a null pointer as image
- VOILUT now returns the right voilut description
- puntoexe::memory hides the string of bytes
- Added the class puntoexe::imebra::waveform to handle waveforms embedded in puntoexe::imebra::dataSet
- Added SWIG headers (partial)


\subsection version_0_0_35 Changes for version 0.0.35 (Alpha)


- Closes #4 (The function jpegCodec::writeTag() always writes a tagId=0 on high-endian architectures)
- Closes #5 (The unit test streamBitsTest doesn't flush the write buffer)
- puntoexe::imebra::transforms::VOILUT now disables any VOI/LUT if 
   puntoexe::imebra::transforms::VOILUT::setVOILUT is called with an ID=0


\subsection version_0_0_34 Changes for version 0.0.34 (Alpha)


- Closes #2 (The code assumes that wchar_t is 2 bytes long, while some systems have wchar_t=4 bytes long)
- Closes #3 (Usage of ICONV should check for return value E2BIG)
- Added casting operators () to puntoexe::ptr


\subsection version_0_0_33 Changes for version 0.0.33 (Alpha)


- Corrected the ptr class so baseObject compiles on GCC
- Corrected thread (removed orphan functions)
- Now charsetConversion throws an exception if a charset is not
   supported by the system


\subsection version_0_0_32 Changes for version 0.0.32 (Alpha)


- The PDF documentation is back


\subsection version_0_0_31 Changes for version 0.0.31 (Alpha)


- The smart pointer \ref puntoexe::ptr is able to cast the object's type.
- The reference counter in puntoexe::baseObject now is set to 0 at
   construction time and should be increased by the application.
  It doesn't affect your code if you used the smart pointer puntoexe::ptr.
- Updated the documentation to reflect recent changes
- The criticalSection now has its own class
- Added the class thread


\subsection version_0_0_30 Changes for version 0.0.30 (Alpha)


- Now the library doesn't fail when the dataset has an empty
   images' offset table
- Now the Dicom codec doesn't switch to implicit datatype when 
   a tag without datatype is found in the group 0x0002.\n
  The tag without datatype is still recognized. This solves a problem 
   with dicom files generated by DicomWorks


\subsection version_0_0_29 Changes for version 0.0.29 (Alpha)


- Added the function puntoexe::imebra::handlers::data::getBufferSize()
- Added the function puntoexe::imebra::buffer::getBufferSizeBytes()
- Now the functions in puntoexe::imebra::dataSet that need the buffer
   size use the new buffer's functions instead of retrieving a data
   handler


\subsection version_0_0_28 Changes for version 0.0.28 (Alpha)


- Breaking change: introduced the puntoexe::streamReader and the 
  puntoexe::streamWriter to control the puntoexe::baseStream objects
- Breaking change: now puntoexe::imebra::dataSet throws the exception
  puntoexe::imebra::dataSetImageDoesntExist when a non existing frame
  is requested with puntoexe::imebra::dataSet::getImage()
- corrected a bug that was crashing the library when an empty tag was
  read
- corrected a bug that was causing a deadlock when 
  puntoexe::WaitForMultipleObjects was used (used by the transactions)
- Added the load on demand for the bigger tags
- Now the library handles correcly the images that are fragmented in several
  data items
- Improvement in the Jpeg codec's performances
- Now image::create() returns a writable datahandler: this avoid the need
  to ask for a writable data handler and improves the speed
- added puntoexe::memoryPool::flush()
- now the stream names can be in unicode format


\subsection version_0_0_27 Changes for version 0.0.27 (Alpha)


- Corrected the sample \ref quick_tour_image
- Corrected a bug in the memoryManager's destructor
- Now the memory manager's parameters can be configured with preprocessor
   definitions


\subsection version_0_0_26 Changes for version 0.0.26 (Alpha)


- Replaced "informations" with "information" and "infos" with "info" \n
  The function exceptionsManager::getExceptionInfos became exceptionsManager::getExceptionInfo \n
  The function exceptionsManager::clearExceptionInfos became exceptionsManager::clearExceptionInfo
- Corrected an issue in the RLE Dicom codec: \n
  after reading a segment the decoder was seeking to the wrong position in the
  dicom file, while writing it was writing wrong offsets
- Improved performances in the Jpeg IDCT function


\subsection version_0_0_25 Changes for version 0.0.25 (Alpha)


- Introduced common lock objects
- Introduced the transactions
- Compiles also on Embedded Visual C++ 4 (requires STLPORT, see 
  sourceforge.net/projects/stlport)
- Introduced the view helper class


\subsection version_0_0_24 Changes for version 0.0.24 (Alpha)


- Introduced support for Unicode and different dicom charsets
- Modified several files to solve problems with Borland C++ Builder 2006
- The dicom codec now uses a dataHandlerRaw to read the tags from the file 
   (previously it was using a normal dataHandler)
- Updated the documentation
- Modified the exceptionManager: now it store a list of objects instead of a
   list of strings


\subsection version_0_0_22 Changes for version 0.0.22 (Alpha)


- Corrected the transformHighBit class
- Modified the exceptionsManager (now it stores the messages per thread and not
   per exception)



*/


