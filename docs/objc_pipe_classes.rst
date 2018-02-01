Pipes and custom streams
========================

The ImebraPipe class can be used to provide custom streams for the ACSE and DIMSE services.

A separate thread must be used to feed a ImebraPipe (to supply a custom reading stream) or to 
sink data from a ImebraPipe (to provide a custom writing stream).


ImebraPipe
----------
.. doxygenclass:: ImebraPipe
   :members:


