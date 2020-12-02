Adding DICOMHERO to your project
================================

Add DICOMHERO to a C++ project
------------------------------

In order to use DICOMHERO your C++ applications must include the file dicomhero6/dicomhero6.h, which in turn includes
all the other necessary files. You should also link your project with the DICOMHERO library built following the instructions
outlined in :ref:`compiling-dicomhero-label`.

On Windows, the preprocessor macro NOMINMAX has to be defined before including the header file <windows.h>: you can
define the macro in the Solution's configuration (Configuration properties/C-C++/Preprocessor definitions).


Add DICOMHERO to an Android project
-----------------------------------

DICOMHERO can be compiled as a AAR library which contains both the C++ source code and the necessary Java wrapper: 
a precompiled AAR library is available at http://dicomhero.com, or you can compile it yourself by following the instructions 
outlined in Compiling DICOMHERO.

In order to use DICOMHERO in your Android project, simply copy the dicomhero6jni-debug|release.aar library in your project’s folder app/libs, then right click on the library in Android Studio and select “Add as library”.

In your code call System.loadLibrary(“dicomhero6_lib”) before using any of the DICOMHERO methods.

All the DICOMHERO classes are in the package “com.dicomhero6”.


Add DICOMHERO to a Java project
-------------------------------

Compile DICOMHERO by following the instructions at :ref:`compiling-dicomhero-java-linux`.

In order to use DICOMHERO in your Java project, simply add the Java source code in "wrappers/javaWrapper/src" to your application.

In your code call System.loadLibrary(“dicomhero6jni”) before using any of the Imebra methods.
All the Imebra classes are in the package “com.dicomhero6”.

When launching your application, define the property "java.library.path" with the value of the folder containing the DICOMHERO JNI shared library (libdicomhero6jni.so).


