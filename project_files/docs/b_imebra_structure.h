/*
$fileHeader$
*/

/*!

\page imebra_structure The Imebra's structure

\section imebra_structure_introduction Introduction

Imebra has been designed to work with Dicom structures, but because images have a
 great importance in the Dicom world, it also includes some image compression and
 decompression functions.

At the moment, 2 codecs are distributed with imebra:

- a Dicom codec
- a Jpeg codec

When a codec reads a stream, it generates a Dicom structure (from now on "dataSet", 
 see \ref puntoexe::imebra::dataSet) in memory and fill it with all the informations 
 available in the stream; please note that also the jpeg codec generates a Dicom 
 structure.

If some images are embedded in the stream being parsed, then they are loaded
 into the \ref puntoexe::imebra::dataSet, but they are not decompressed nor 
 interpreted; in order to retrieve an image from the dataSet, the application must 
 call the function \ref puntoexe::imebra::dataSet::getImage() that retrieves the 
 image from the dataSet and decompresses it using the appropriate codec.

Other functions in the dataSet allow the application to read or write into
 the Dicom tags, or to store new images into the dataSet 
 (\ref puntoexe::imebra::dataSet).


\section imebra_structure_dataSet The dataSet

The dataSet is a collection of Dicom tags organized in groups.
Each group is represented by its ID, which SHOULD be unique in the dataset: datasets
 created with older application may contain several groups with the same ID, but
 more recent applications use sequences to obtain the same result of storing
 several objects of the same type (e.g.: a sequence of images, or a sequence of
 LUTs).

The information stored in the dataSet (\ref puntoexe::imebra::dataSet) 
 represents the content of one or more related Dicom objects: for instance it
 could include the informations of a patient and the images of one of its exams.

The information related to one object could be distributed in several groups, and
 the dataSet has access to all the groups and tags it contains: this is why 
 the dataSet supplies several functions that pick up related informations with 
 one function call.
For instance, the images (the attributes are stored in the group 0x28 while the
 pixels are in the group 0x7fe0) can be retrieved from the dataSet with a call
 to \ref puntoexe::imebra::dataSet::getImage().


\section imebra_structure_groups The groups

One group is a collection of Dicom tags. Each group is identified by a numeric ID.
When a group appears several times in a dataSet, then it is identified also by
 a progressive number (called order in the library).
The information about the order is not stored in the Dicom stream but is generated
 by the library while a Dicom structure is created.

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
