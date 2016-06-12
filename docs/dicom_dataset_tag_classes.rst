DICOM dataSet & tags classes
============================

This section describes the classes responsible for retrieving and setting the information from/to
a DICOM structure, represented by the class imebra::DataSet.

The DICOM structure contains several different pieces of information (tags), which collectively describe
one or more DICOM objects (images, studies, etc).

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
