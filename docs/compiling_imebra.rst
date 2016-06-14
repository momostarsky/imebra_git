Compiling Imebra
================

If you want to compile Imebra from the source code, then you should download the Imebra Source Distribution.
The result of the Imebra compilation is a shared library for your operating system of choice.

The Imebra Source Distribution includes:

- the source code for the library
- the source code for the tests
- pre-built documentation
- pre-generated JNI headers for Java


Prerequisites
-------------

In order to build the library from the Imebra Source Distribution you need:

- a modern C++ compiler (GCC, clang, Visual Studio, etc)
- CMake version 2.8 or newer (https://cmake.org/)
- JDK (only if you want to build the Java version)
- Android SDK & NDK (only if you want to build the Android version)

Compiling the C++ version of Imebra
-----------------------------------

The library folder contains a CMakeLists file, which contains the information needed by
CMake to generata a solution file for your platform (a make file, a VisualStudio solution, etc).

To generate the solution file for your platform, execute the following steps:

1. Create a folder that will contain the result of the compilation (artifacts)
2. cd into the created artifacts folder
3. execute cmake with the path to the Imebra's library folder as parameter
3. execute cmake with the --build option

For instance:
::

    md artifacts
    cd artifacts
    cmake imebra_location/library
    cmake --build .

The first CMake command will generate a solution file for the your platform: this will be a 
make file on Linux, a VisualStudio solution of Windows, an XCode project on Mac.

The second CMake command with the --build option will launch make, VisualStudio or the build
chain defined on your machine.







