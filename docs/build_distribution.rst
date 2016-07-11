Creating a source distribution from the code in the VCS
=======================================================

This section describes how to create an Imebra Source Distribution containing the full
C++source code, the Java wrappers for Android, the HTML documentation, the test units code coverage
information.

The Imebra image is built on Ubuntu 16.04 with the following apt packages:

- mercurial
- doxygen
- g++
- lcov
- python
- python-pip
- libgtest-dev
- ant
- cmake
- swig

Additionally, two Python packages must be present (installable with pip):

- breathe
- sphinx_rtd_theme

In order to install the packages, type the following commands as root or prepend them with sudo:
::

    apt-get install mercurial
    apt-get install doxygen
    apt-get install g++
    apt-get install lcov
    apt-get install python
    apt-get install python-pip
    apt-get install python-sphinx
    pip install breathe
    pip install sphinx_rtd_theme
    apt-get install libgtest-dev
    apt-get install ant
    apt-get install cmake
    apt-get install swig

Then clone the Imebra mercurial repository:
::

    hg clone https://bitbucket.org/binarno/imebra

Finally, cd into the imebra folder and execute ant to build the source distribution that includes:

- full C++ source code
- generated Java source code for the Android wrapper
- html documentation
- unit tests
- code coverage report

::

    cd imebra
    ant


