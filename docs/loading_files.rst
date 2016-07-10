Loading files
=============

Imebra can read 2 kinds of files:

- DICOM files
- Jpeg files

In order to do this, it supplies two different codecs able to parse the two different streams.
Both the codes store the parsed content into an :cpp:class:`imebra::DataSet` class (yes, also the Jpeg codec).

Imebra chooses automatically the correct codec according to the stream content.

In order to create an :cpp:class:`imebra::DataSet` from a stream you should use the class :cpp:class:`imebra::CodecFactory`.

.. code-block:: c++

    std::unique_ptr<imebra::DataSet> loadedDataSet(imebra::CodecFactory::load("DicomFile.dcm"));

This line loads the file DicomFile.dcm.

Imebra allows to perform a "lazy loading", which leaves the data on the input stream and loads it in memory
only when necessary; large tags that are not needed are discarded from memory until they are needed once again.

This allows to process large DICOM files, by loading large tags only when they are needed and is completely transparent
to the client application.

To enable the "lazy loading", specify the maximum size of the tags that must be loaded immediately. The following line
leaves all the tags bigger than 2048 bytes on the stream and loads them only when needed:

.. code-block:: c++

    std::unique_ptr<imebra::DataSet> loadedDataSet(imebra::CodecFactory::load("DicomFile.dcm", 2048));




