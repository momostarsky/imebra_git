%rename(assign) operator=;

%module imebra

%{
#include "../../imebra/include/imebra.h"
#include "dataSet_swig.h"
#include "baseStream_swig.h"
#include "stream_swig.h"
#include "streamReader_swig.h"
#include "codecFactory_swig.h"
#include "dicomDir_swig.h"
#include "exceptions_swig.h"
%}
%include <std_string.i>
%include <std_wstring.i>
%include "dataSet_swig.h"
%include "baseStream_swig.h"
%include "stream_swig.h"
%include "streamReader_swig.h"
%include "codecFactory_swig.h"
%include "dicomDir_swig.h"
%include "exceptions_swig.h"
