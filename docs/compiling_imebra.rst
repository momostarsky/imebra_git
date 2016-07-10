Compiling Imebra
================

This section explain how to compile Imebra from the source distribution.

The result of the Imebra compilation is a shared library for your operating system of choice.

The Imebra Source Distribution includes:

- the source code for the library
- the source code for the tests
- pre-built documentation
- pre-generated JNI headers for Java


Compiling the C++ version of Imebra
-----------------------------------

Prerequisites
.............

In order to build the library from the Imebra Source Distribution you need:

- a modern C++ compiler (GCC, clang, Visual Studio, etc)
- CMake version 2.8 or newer (https://cmake.org/)
- JDK (only if you want to build the Java version)
- Android SDK & NDK (only if you want to build the Android version)

Building Imebra
...............

The library folder contains a CMakeLists file, which contains the information needed by
CMake to generata a solution file for your platform (a make file, a VisualStudio solution, etc).

To generate the Imebra shared library, execute the following steps:

1. Create a folder that will contain the result of the compilation (artifacts)
2. cd into the created artifacts folder
3. execute cmake with the path to the Imebra's library folder as parameter
3. execute cmake with the --build option, and on Windows optionally specify the build configuration

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

On Windows, the last cmake command can be followed by --config release or --config debug, like
this:
::

    cmake --build . --config release

or
::

    cmake --build . --config debug



Compiling the Android version of Imebra
---------------------------------------

Prerequisites
.............

In order to build the Android version of Imebra you need:

- the Android SDK
- the Android NDK

Building Imebra
...............

The Android version of the library needs both the Java source code (located in the wrappers/javaWrapper folder)
and the C++ source code (located in the library folder)

To generate the Imebra Jar library:

1. cd into the Imebra wrappers/javaWrapper folder
2. run ant and define the properties sdk.dir and ndk.dir so they point to the home folders of the Android SDK and NDK respectively
3. the produced JAR will be located in the folder wrappers/javaWrapper/out/artifacts

For instance:
::

    cd wrappers/javaWrapper
    ant -Dsdk.dir=path/to/Android/SDK -Dndk.dir=path/to/Android/NDK
    


Compiling the test units
------------------------

Prerequisites
.............

In order to build and execute the tests you need:

- a compiled gtest library and its include file (get it here https://github.com/google/googletest)
- the compiled C++ version of Imebra

Building the tests
..................

To compile te tests, execute the following steps:

1. create a folder that will contain the test units executable
2. cd into the created folder
3. run cmake with the path to the tests/CMakeLists.txt as parameter. You can also define the
   CMake variables imebra_library, gtest_library and gtest_include with the path to the
   imebra library, gtest library and gtest include folder respectively
4. run cmake --build .

For instance:
::

    md tests_artifacts
    cd tests_artifacts
    cmake -Dimebra_library="path/to/imebra/library" -Dgtest_library="path/to/gtest/library" -Dgtest_include="path/to/gtest/include" imebra_location/tests
    cmake --build .






