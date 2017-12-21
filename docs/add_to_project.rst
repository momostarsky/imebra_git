Adding Imebra to your project
=============================

Add Imebra to a C++ project
---------------------------

In order to use Imebra in your C++ applications your app must include the file imebra/imebra.h, which in turn includes
all the other necessary files. You should also link your project with the imebra library built following the instructions
outlined in :ref:`compiling-imebra-label`.

On Windows, the preprocessor macro NOMINMAX has to be defined before including the header file <windows.h>: you can
define the macro in the Solution's configuration (Connfiguration properties/C-C++/Preprocessor definitions).








