.. _changes-log-label:

Changes log
===========

Version |release| (this version)
--------------------------------

- Implemented enhancement #316 (Add functions to retrieve floats, uint8, uint16, int8, int16) as per SOP :ref:`DEVENH_2`
- Fixed bug #317 (readingDataHandlerStringAS::getAge does not properly check for the age units) as per SOP :ref:`FIXBUG_2`
- Implemented enhancement #318 (The data handler for VR "AT" should provide a way to retrieve the group and the id) as per sop :ref:`DEVENH_2`
- Implemented enhancement #319 (Remove the compilation warnings on Windows) as per sop :ref:`DEVENH_2`
- Fixed bug #321 (The test objectivec.stringToNSStringTest fails) as per SOP :ref:`FIXBUG_2`

Version 5.0.1.1
--------------------------------

- Fixed bug #307 (Remove the build-tools folder from the source code) as per SOP :ref:`FIXBUG_2`
- Implemented enhancement #308 (Remove non necessary files imebra_android.iml and ant.properties from the javaWrapper folder) as per SOP :ref:`DEVENH_2`
- Implemented enhancement #309 (Add information about the commercial license in the user manual) as per SOP :ref:`DEVENH_2`
- Implemented enhancement #310 (Migration from Mercurial to Git: change the SOPs & scripts to reflect the usage of Git instead of Mercurial) as per SOP :ref:`DEVENH_2`
- Implemented enhancement #311 (Use the bitbucket pipeline artifacts instead of uploading the generated file to dropbox) as per SOP :ref:`DEVENH_2`
- Implemented enhancement #312 (Add QtCreator .user files to gitignore) as per SOP :ref:`DEVENH_2`
- Fixed bug #313 (Fix the CMake install commands so the Cmake configuration is properly exported and reusable by other modules) as per SOP :ref:`FIXBUG_2`
- Fixed bug #314 (The identifier for the Apple compiler changed from clang to AppleClang, causing the compilation to fail) as per SOP :ref:`FIXBUG_2`


Version 5.0.1.0
--------------------------------

- Fixed bug #306 (The group length for groups 0 and 2 is mandatory) as per SOP :ref:`FIXBUG_2`

Version 5.0.0.0
--------------------------------

First public release of Imebra V5.

