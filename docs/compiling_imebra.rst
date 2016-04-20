Compiling Imebra
================

If you want to compile Imebra from the source code, then you shoud download the Imebra Source Distribution.
The result of the Imebra compilation is a shared library for your operating system of choice.

The Imebra Source Distribution includes:

- the source code for the library
- the source code for the tests
- pre-built documentation
- pre-generated JNI headers for Java


Tools needed to build Imebra
----------------------------

In order to build the library from the Imebra Source Distribution you need:

- a modern C++ compiler (GCC, clang, Visual Studio, etc)
- CMake version 2.8 or newer
- JDK (only if you want to build the Java version)
- Android SDK & NDK (only if you want to build the Android version)


Compiling the C++ version of Imebra
-----------------------------------

Follow those steps:

# Create a folder that will contain the result of the compilation (artifacts)
# cd into the artifacts folder
# execute cmake with the path to the Imebra's library folder as parameter
# launch make

::

    cd artifacts/folder
    cmake path/to/imebra/library
    make .





