%rename(assign) operator=;

%module imebra

/* This tells SWIG to treat char ** as a special case when used as a parameter
   in a function call */
%typemap(in) char ** (jint size) {
	int i = 0;
	size = (*jenv)->GetArrayLength(jenv, $input);
	$1 = (char **) malloc((size+1)*sizeof(char *));
	/* make a copy of each string */
	for (i = 0; i<size; i++) {
		jstring j_string = (jstring)(*jenv)->GetObjectArrayElement(jenv, $input, i);
		const char * c_string = (*jenv)->GetStringUTFChars(jenv, j_string, 0);
		$1[i] = malloc((strlen(c_string)+1)*sizeof(char));
		strcpy($1[i], c_string);
		(*jenv)->ReleaseStringUTFChars(jenv, j_string, c_string);
		(*jenv)->DeleteLocalRef(jenv, j_string);
	}
	$1[i] = 0;
}

/* This cleans up the memory we malloc'd before the function call */
%typemap(freearg) char ** {
	int i;
	for (i=0; i<size$argnum-1; i++)
	  free($1[i]);
	free($1);
}

/* This allows a C function to return a char ** as a Java String array */
%typemap(out) char ** {
	int i;
	int len=0;
	jstring temp_string;
	const jclass clazz = (*jenv)->FindClass(jenv, "java/lang/String");

	while ($1[len]) len++;
	jresult = (*jenv)->NewObjectArray(jenv, len, clazz, NULL);
	/* exception checking omitted */

	for (i=0; i<len; i++) {
	  temp_string = (*jenv)->NewStringUTF(jenv, *result++);
	  (*jenv)->SetObjectArrayElement(jenv, jresult, i, temp_string);
	  (*jenv)->DeleteLocalRef(jenv, temp_string);
	}
}

/* These 3 typemaps tell SWIG what JNI and Java types to use */
%typemap(jni) char ** "jobjectArray"
%typemap(jtype) char ** "String[]"
%typemap(jstype) char ** "String[]"

/* These 2 typemaps handle the conversion of the jtype to jstype typemap type
   and vice versa */
%typemap(javain) char ** "$javainput"
%typemap(javaout) char ** {
	return $jnicall;
  }


%{
#include "../../imebra/include/imebra.h"
#include "dataSet_swig.h"
#include "baseStream_swig.h"
#include "stream_swig.h"
#include "streamReader_swig.h"
#include "codecFactory_swig.h"
%}
%include <std_string.i>
%include <std_wstring.i>
%include "dataSet_swig.h"
%include "baseStream_swig.h"
%include "stream_swig.h"
%include "streamReader_swig.h"
%include "codecFactory_swig.h"
