.. _changes-log-label:

Changes log
===========

Version |release| (this version)
--------------------------------

- Fixed bug #125 (Documentation: The Java examples use the methods setUnicodeString and getUnicodeString and finalize)
- Fixed bug #126 (Documentation: Wrong call to getLut in the examples)
- Fixed bug #127 (Documentation: wrong Java Example for writing a Tag into a DataSet)
- Fixed bug #129 (Documentation: The example that retrieves the LUTs out never exit from the loop)

Version 4.0.2.1
---------------

- Fixed bug #122 (Failure to open a file with Java Wrappers)
- Fixed bug #123 (SWIG translates the Java String to UTF16 and not UTF32 when filling std::wstring)
- Fixef bug #124 (Java charset conversion fails)

Version 4.0.1.6
---------------

- Fixed bug #121 (Wrong Java examples in the documentation)
- Improved test units
- Improved the documentation for the class DataSet
- Improved the section "Compiling Imebra" of the documentation

Version 4.0.1.1
---------------

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


