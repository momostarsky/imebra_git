#
# This script allows to build and install the Python version
# of the DICOMHERO library.
#
# The Python version of DICOMHERO is composed by the DICOMHERO C++
# code and by Python wrappers generated with SWIG.
#
# To install DICOMHERO:
#
#    cd dicomhero6_folder
#    python setup.py install
#
# To install on a local folder (don't need administrator 
# permissions):
#
#    cd dicomhero6_folder
#    python setup.py install --user
#
# To uninstall DICOMHERO:
#
#    pip uninstall dicomhero6
#
# DICOMHERO is distributed under GPLv2 license.
# Commercial licenses are available at https://dicomhero.com
#
#-----------------------------------------------------------------

from distutils.core import setup, Extension
from distutils.sysconfig import get_python_inc
import sys
import os

# Get all the DICOMHERO C++ source files
#---------------------------------------
def get_sources(root_folder):
    modules_files = []

    for root, subdirs, files in os.walk(root_folder):
        for file in files:
            if file.endswith(".cpp") or file == "python_wrapper.cxx":
                modules_files.append(os.path.join(root, file))

    return modules_files


# Set proper libraries and flags according to the OS
#---------------------------------------------------
include_directories = []
include_directories.append(get_python_inc(plat_specific=1))
include_directories.append("./library/include")
librariesArray = []
compileFlags = []

print(include_directories)

if sys.platform.startswith('linux'):
    librariesArray.append('pthread')
    compileFlags = ["-std=c++11", "-Wall", "-Wextra", "-Wpedantic", "-Wconversion", "-Wfloat-equal"]

if sys.platform.startswith('darwin'):
    librariesArray.append('iconv')
    compileFlags = ["-std=c++11", "-Wall", "-Wextra", "-Wpedantic", "-Wconversion", "-Wfloat-equal"]

if sys.platform.startswith('win'):
    librariesArray.append('kernel32')

dicomhero_sources = get_sources("./library")
dicomhero_sources.extend(get_sources("./wrappers/pythonWrapper"))

# Define the C++ module
#----------------------
dicomheroModule = Extension('_dicomhero6',
                    define_macros = [('MAJOR_VERSION', '$major_version$'),
                                     ('MINOR_VERSION', '$minor_version$')],
                    libraries = librariesArray,
                    sources = dicomhero_sources,
                    extra_compile_args = compileFlags,
                    include_dirs= include_directories)

# Define the package
#-------------------
setup (name = 'dicomhero6',
       version = '$major_version$.$minor_version$',
       description = 'DICOMHERO library for Python',
       author = 'Paolo Brandoli',
       author_email = 'paolo@binarno.com',
       url = 'https://dicomhero.com',
       long_description = '''
DICOMHERO Dicom Library.
''',
       ext_modules = [dicomheroModule],
       packages = ['dicomhero6'],
       package_dir = {'dicomhero6': './wrappers/pythonWrapper'})

