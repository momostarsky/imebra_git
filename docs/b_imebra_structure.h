/*
$fileHeader$
*/

/*!

\page imebra_structure Introduction to Imebra

\section imebra_structure_introduction Introduction

Imebra is a C++ library able to parse and build DICOM files (including DICOMDIR
 files). It also supplies the necessary codecs to decode and decode the images
 embedded in the DICOM files.

When Imebra reads a DICOM file then it generates a Dicom structure in memory
(from now on "dataSet", see \ref puntoexe::imebra::dataSet) and fills it with
 the information available in the file.

If images are embedded in the file being parsed then they are loaded
 into the \ref puntoexe::imebra::dataSet and can be decoded into raw buffers
 with the function \ref puntoexe::imebra::dataSet::getImage().

Other functions in the dataSet allow the application to read or write into
 the DICOM tags, or to store new images into the dataSet
 (\ref puntoexe::imebra::dataSet).


\section imebra_structure_dataSet The dataSet

The dataSet is a collection of DICOM tags organized in groups.

Each group is represented by the GROUP ID, which SHOULD be unique in the dataset:
 datasets created with older application may contain several groups with the same ID,
 but more recent applications use sequences to obtain the same result of storing
 several objects of the same type (e.g.: a sequence of images, or a sequence of
 LUTs).

The information stored in the dataset (\ref puntoexe::imebra::dataSet)
 represents the content of one or more related DICOM objects: for instance it
 could include the patient's data, the images and data of one of its exams.


\section imebra_structure_groups The groups

One group is a collection of Dicom tags. Each group is identified by a numeric ID.
When a group appears several times in a dataSet, then Imebra identifies it also with
 a progressive number (called order in the library).

The tags that belong to the same group are stored together in the Dicom stream.


\section imebra_structure_tags The tags

A tag stores an information related to a single attribute of the Dicom stream.
For instance, one tag could store the patient's name while another tag could store
 the patient's age.

Each tag is identified by a numeric ID: the tag's ID is unique inside a group
 (see \ref imebra_structure_groups).

The couple <b>group's ID/tag's ID</b> defines the purpose of the tag:
 for instance, the tag 0010,0010 (groupId=0x0010 and tagId=0x0010) is used
 to store the patient's name, and cannot be used for other purposes.

Some tags can store several records of the same type: for instance, the tag 7fe0,0010 
 (groupId=0x7fe0, tagId=0x0010) can store the data of several images.
 

\section imebra_structure_buffer The buffers

Usually, a dicom tag (see \ref imebra_structure_tags) stores only one item of
 information, but sometimes they can store more items; this happens when
 the tag has an undefined length in the data stream.

Each item is stored in a buffer, so when there are several items then
 several buffers are allocated in the tag.



\section imebra_structure_dataHandler The data handlers

A dataHandler (see \ref puntoexe::imebra::handlers::dataHandler) is connected to a 
 buffer and reads or writes data into it.

The dataHandler works on a local copy of the buffer; this avoid multithreading
 related problems.

The data handler can read or write the data in several formats (string, number,
 date, ...).

*/
