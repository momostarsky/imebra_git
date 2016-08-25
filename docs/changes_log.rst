.. _changes-log-label:

Changes log
===========

Version |release| (this version)
--------------------------------

- Fixed bug #119 (Imebra does not create the tag 0002,0001 when writing a DICOM file)
- Fixed bug #120 (When creating an empty DataSet with unspecified transfer syntax then the transfer syntax is set to 1.2.840.10008.1.2.1)
- Added changes log

Version 4.0.0.11
----------------

- Added test for TransformsChain
- Improved string data handler tests
- Added test for VR UC
- Improved documentation

Version 4.0.0.8
---------------

- Documentation: renamed "Quick tour" to "Getting started"
- Closed bug #118 (Risks in the documentation are not ordered by mitigated total risk)

Version 4.0.0.6
---------------

- Improved documentation
- CMake: when compiling on Windows set the Kernel32 library in the compiler detection block, not in the charset conversion detection block

Version 4.0.0.4
---------------

- First public release of Imebra V4


