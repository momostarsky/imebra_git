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

    std::unique_ptr<imebra::DataSet> loadedDataSet(imebra::CodecFactory::load("DicomFile.dcm", 2048));

This line loads the file DicomFile.dcm.

