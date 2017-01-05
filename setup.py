from distutils.core import setup, Extension
import sys
import os

def get_sources(root_folder):
    modules_files = []

    for root, subdirs, files in os.walk(root_folder):
        for file in files:
            if file.endswith(".cpp") or file == "python_wrapper.cxx":
                modules_files.append(os.path.join(root, file))

    return modules_files


# set proper libraries according to OS
librariesArray = []

if sys.platform.startswith('linux'):
    librariesArray.append('pthread')

if sys.platform.startswith('darwin'):
    librariesArray.append('iconv')

if sys.platform.startswith('win'):
    librariesArray.append('kernel32')

imebra_sources = get_sources("./library")
imebra_sources.extend(get_sources("./wrappers"))

imebraModule = Extension('_imebra',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    libraries = librariesArray,
                    sources = imebra_sources,
                    extra_compile_args = ["-std=c++0x", "-Wall", "-Wextra", "-Wpedantic", "-Wconversion", "-Wfloat-equal"],
                    include_dirs= ["./library/include"])

setup (name = 'imebra',
       version = '1.0',
       description = 'Imebra library for Python',
       author = 'Paolo Brandoli',
       author_email = 'paolo@binarno.com',
       url = 'https://imebra.com',
       long_description = '''
Imebra Dicom Library.
''',
       ext_modules = [imebraModule],
       packages = ['imebra'],
       package_dir = {'imebra': './wrappers/pythonWrapper'})

