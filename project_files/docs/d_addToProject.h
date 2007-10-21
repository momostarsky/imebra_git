/*
$fileHeader$
*/

/*!

\page add_to_project Adding Imebra to your project

\section add_to_project_introduction Introduction

Imebra is not distributed as a dynamic module and probably will never be.
This is due to the CPP language used to build the library and to the different
 conventions used by different compilers when they deal with the C++ function
 names.

Because of this, all the Imebra source files must be linked to your project by
 you. If you use the same C++ compiler to build your application and the Imebra
 library then you could create a dynamic module that includes the Imebra library.

The following sections describes how to include the Imebra source code in your
 project and how to call its functions.


\section add_to_project_common Prerequisites (common to all the platorms)

Imebra heavily uses the stl library; if your development environment doesn't provide 
 a modern stl, try to install stlport (http://www.stlport.org).
 Visual Studio 6 and Embedded Visual C++ 4 need stlport.

Imebra also needs the standard C library.


\section add_to_project_win32 Prerequisites for Windows (desktop version)

The path to the window.h file must be in the list of paths searched by the "include"
 statement.

The library uses the functions TryEnterCriticalSection() and SwitchToThread()
 which require the definition of the symbol _WIN32_WINNT in the C++ preprocessor.
_WIN32_WINNT has to be set to 0x0400 or greater.
If you are compiling the library for Windows CE then the symbol _WIN32_WINNT doesn't
 have to be defined.


\section add_to_project_evc4 Prerequisites for Embedded Visual C++ 4 (EVC4)

In order to compile the Imebra library with Embedded Visual C++ 4 (EVC4), a
 reliable STL library must be installed.

The suggested STL library is STLPort (http://www.stlport.org). Please note that
 the STLPort library needs the EVC4 service pack 4 and the RTTI patch for EVC4,
 available on the Microsoft's website and called RITTI.EXE.


\section add_to_project_posix Prerequisites for the Posix systems

Imebra uses the iconv and the pthreads libraries.
Please take care of updating the list of paths searched by the "include" statement.
The following headers are necessary:
- iconv.h
- pthread.h
- sched.h

The application must be linked to the iconv and the pthread libraries.


\section add_to_project_files Adding the source files to your project

Imebra is part of the Puntoexe Library and all its source code files are located
 in subfolders of the "puntoexe_library" directory, included in the distribution
 package.

The first step to add the Imebra library to your project is to add all the files
 in the following directories to your project:
 - puntoexe_library/imebra/src
 - puntoexe_library/base/src

The files in those directories are cpp source files.
<b>You must disable the use of the precompiled header for all the imebra source
   files.</b>

The files in the following directories are header files and don't need to be
 included in your project, but nothing harmful happen if you do include them
 (please note that EVC4 needs them):
 - puntoexe_library/imebra/include
 - puntoexe_library/base/include

The compiler must support the RTTI.

If you are compiling the application on Windows, define the preprocessor symbol
 WIN32 (_WIN32_WCE on EVC4) in your project's properties.

If you are compiling the application for Windows NT, 2000, XP or Vista, then
 define the preprocessor symbol _WIN32_WINNT to 0x0400 or greater.


\section add_to_project_checklist Adding Imebra to your project: Checklist

Please check that all the following tasks have been performed:
- A modern STL library is available and the path to its header files has been
  added to the paths searched by the "include" statement
- Iconv and Pthread are available on Posix systems (non necessary on Windows systems)
- All the cpp files in the directory "puntoexe_library/base/src" have been added 
  to your project
- All the cpp files in the directory "puntoexe_library/imebra/src" have been 
  added to your project
- When compiling on Windows (desktop versions) define the symbol WIN32 in the
  preprocessor definitions
- When compiling for Windows Mobile define the symbol _WIN32_WCE in the 
  preprocessor definitions
- When compiling for windows Desktop define the symbol _WIN32_WINNT to 0x0400
  or greater
- Enable the RTTI informations in the C++ compiler
- Include the file "puntoexe_library/imebra/imebra.h" in all the files that
  reference an imebra class


\section add_to_project_header Calling an imebra function from your application

If you want to call or reference an Imebra class or function you have to include
 the Imebra header to all the files that intend to deal with Imebra.

For your convenience, a single include file called "imebra.h" is available in
 the directory "puntoexe_library/imebra/include".
The "imebra.h" file includes all the main header files used by the Imebra sources.

If your compiler supports the precompiled headers, then a better place where to
 include "imebra.h" could be the source file used to generate the precompiled
 headers (usually "stdafx.h" in the Microsoft Visual C++ compiler).


\section add_to_project_references The Imebra objects reference counter

Most of the Imebra classes derive from the object puntoexe::baseObject.
This object has a reference counter that keeps track of he number of variables
 that reference it. When the reference counter reaches 0 it means that no variable
 is referencing the object and it can be deleted.

Your application should not try to increase/decrease the reference counter
 "manually" by using the addRef() and release() methods, but it should use
 the smart pointer provided by Imebra (see \ref add_to_project_ptr).


\section add_to_project_ptr The Imebra smart pointer

Most of the Imebra functions use a smart pointer in order to count the references
 to an object.

The smart pointer is declared in the namespace puntoexe and is a class called
 ptr (puntoexe::ptr).

Why does Imebra use a custom implementation of the smart pointer when there are
 already some out there?
Because the pointer is used also to track object that should be removed but in 
 practice are not; for instance, the puntoexe::memory classes sometime are not
 deleted when they counter reaches 0, but they are stored in puntoexe::memoryPool
 and reused later.
Each Imebra object can veto its deletion by returning false when a call to 
 puntoexe::baseObject::preDelete() is made.

So, your application should use puntoexe::ptr instead of increasing/decreasing
 the reference counters "manually" by calling puntoexe::baseObject::addRef() and
 puntoexe::baseObject::release().


\section add_to_project_nameSpaces The namespaces

All the base services classes of the Imebra library are declared in the namespace 
 \ref puntoexe, while the normal classes are in the namespace puntoexe::imebra.

So, to create a dataSet, you should use the following line:
\code
puntoexe::ptr<puntoexe::imebra::dataSet> myDataset(new puntoexe::imebra::dataSet);
\endcode

Or you could use the C++ statement "using" in order to declare the namespace that
 your application is going to use.


\section add_to_project_errors Managing the Imebra exceptions

When an error occurs the Imebra library throws an exception.
Some exceptions are catched and solved by the library, but some of them could
 reach your application.

In this case, your application should catch the exception and try to resolve
 the error or display a message to the user or, in the worst case, quit.

All the Imebra exceptions are tracked by the statically allocated object
 puntoexe::exceptionsManager.
This object follows an exception while it travels through all the functions until
 it finally reach your application: when your application catch an Imebra exception
 it MUST query the puntoexe::exceptionsManager in order to retrieve extended 
 informations related to the exception.

The informations returned by puntoexe::exceptionsManager include the complete
 stack dump at the moment of the creation of the exception and the reason
 of the error. Those informations could be logged somewhere by your application,
 specially if the exception cannot be handled and the application will quit.

Please note that your application MUST query puntoexe::exceptionsManager for the 
 extend informations even if they are not used.

*/