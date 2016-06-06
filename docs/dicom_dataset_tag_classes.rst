DICOM dataSet & tags classes
============================

This section describes the classes responsible for retrieving and setting the information from/to
a DICOM structure, represented by the class imebra::DataSet.

The DICOM structure can contain several different pieces of information (tags), which collectively describe
one or more DICOM objects (images, studies, etc).

DICOM tags are organized in groups: tags belonging to the same group are stored close together in the
DICOM stream.

All the public methods in Imebra use the class TagId to identify specific DICOM tags.

DataSet
-------
.. doxygenclass:: imebra::DataSet
   :members:

Tag
---
.. doxygenclass:: imebra::Tag
   :members:

TagId
-----
.. doxygenclass:: imebra::TagId
   :members:

ReadingDataHandler
------------------
.. doxygenclass:: imebra::ReadingDataHandler
   :members:

ReadingDataHandlerNumeric
-------------------------
.. doxygenclass:: imebra::ReadingDataHandlerNumeric
   :members:

WritingDataHandler
------------------
.. doxygenclass:: imebra::WritingDataHandler
   :members:

WritingDataHandlerNumeric
-------------------------
.. doxygenclass:: imebra::WritingDataHandlerNumeric
   :members:
