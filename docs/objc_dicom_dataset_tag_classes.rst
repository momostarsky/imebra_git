DICOM dataSet & tags classes
============================

This section describes the classes and methods responsible for retrieving and setting the information that composes the
DICOM structure, represented by the class :cpp:class:`ImebraDataSet`.

Each individual piece of information is stored into a tag (see :cpp:class:`ImebraTag`) inside the DICOM structure.


ImebraDataSet
-------------
.. doxygenclass:: ImebraDataSet
   :members:

ImebraTag
---------
.. doxygenclass:: ImebraTag
   :members:

ImebraTagId
-----------
.. doxygenclass:: ImebraTagId
   :members:

ImebraReadingDataHandler
------------------------
.. doxygenclass:: ImebraReadingDataHandler
   :members:

ImebraReadingDataHandlerNumeric
-------------------------------
.. doxygenclass:: ImebraReadingDataHandlerNumeric
   :members:

ImebraWritingDataHandler
------------------------
.. doxygenclass:: ImebraWritingDataHandler
   :members:

ImebraWritingDataHandlerNumeric
-------------------------------
.. doxygenclass:: ImebraWritingDataHandlerNumeric
   :members:
