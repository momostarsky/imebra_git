Adding Imebra to your project
=============================

Add Imebra to a C++ project
---------------------------

In order to use Imebra in your C++ application your app must include the file imebra/imebra.h, which in turn includes
all the other necessary files. You should also link your project with the imebra library.


Add Imebra to an Android project
--------------------------------

Imebra can be compiled as a Jar library. A precompiled Jar library is available at http://imebra.com.

The Jar library also contains the native code compiled from the C++ source files.

In order to use Imebra in your Android project, simply include the imebra_android_jni.jar library in
your project's folder app/libs and in your code call System.loadLibrary("imebra_lib") before using any of the Imebra methods.



