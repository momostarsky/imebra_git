#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringPN.o \
	${OBJECTDIR}/CImbx_tests/decimalStringHandlerTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringST.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME2ToRGB.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transformsChain.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/streamController.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/criticalSection.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/buffer.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/waveform.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/data.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/colorTransform.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringUI.o \
	${OBJECTDIR}/CImbx_tests/streamBitsTest.o \
	${OBJECTDIR}/CImbx_tests/transactionTest.o \
	${OBJECTDIR}/CImbx_tests/dataSetTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/charsetConversion.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/modalityVOILUT.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/codecFactory.o \
	${OBJECTDIR}/CImbx_tests/jpegCodecTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/LUT.o \
	${OBJECTDIR}/CImbx_tests/bitTransformTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/exception.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToYBRPARTIAL.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerDateTime.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataGroup.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME1ToMONOCHROME2.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/streamWriter.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dibCodec.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringSH.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringUT.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/huffmanTable.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/image.o \
	${OBJECTDIR}/CImbx_tests/dateTimeHandlerTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/streamReader.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transformHighBit.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/codec.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/VOILUT.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerString.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToYBRFULL.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/charsetsList.o \
	${OBJECTDIR}/CImbx_tests/dicomCodecTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transform.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/colorTransformsFactory.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringDS.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dicomCodec.o \
	${OBJECTDIR}/CImbx_tests/numericHandlerTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringLO.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME1ToRGB.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandler.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/baseStream.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringAE.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/YBRFULLToRGB.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringAS.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transaction.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringCS.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/PALETTECOLORToRGB.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/viewHelper.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dicomDir.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerDate.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/thread.o \
	${OBJECTDIR}/CImbx_tests/paletteTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/jpegCodec.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/baseObject.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToPALETTECOLOR.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transformBuffers.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/drawBitmap.o \
	${OBJECTDIR}/CImbx_tests/huffmanTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/stream.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/memory.o \
	${OBJECTDIR}/CImbx_tests/dicomDirTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME2ToYBRFULL.o \
	${OBJECTDIR}/CImbx_tests/unicodeStringHandlerTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerDateTimeBase.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dicomDict.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/YBRFULLToMONOCHROME2.o \
	${OBJECTDIR}/CImbx_tests/ageStringHandlerTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToMONOCHROME2.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/YBRPARTIALToRGB.o \
	${OBJECTDIR}/CImbx_tests/memoryStreamTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/memoryStream.o \
	${OBJECTDIR}/CImbx_tests/bufferTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerTime.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataSet.o \
	${OBJECTDIR}/CImbx_tests/CImbx_tests.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringUnicode.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringIS.o \
	${OBJECTDIR}/CImbx_tests/exceptionsTest.o \
	${OBJECTDIR}/CImbx_tests/buildImageForTest.o \
	${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringLT.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread -lcppunit

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/GNU-Linux-x86/tests

dist/Debug/GNU-Linux-x86/tests: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o dist/Debug/GNU-Linux-x86/tests ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringPN.o: ../imebra/src/dataHandlerStringPN.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringPN.o ../imebra/src/dataHandlerStringPN.cpp

${OBJECTDIR}/CImbx_tests/decimalStringHandlerTest.o: CImbx_tests/decimalStringHandlerTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/decimalStringHandlerTest.o CImbx_tests/decimalStringHandlerTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringST.o: ../imebra/src/dataHandlerStringST.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringST.o ../imebra/src/dataHandlerStringST.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME2ToRGB.o: ../imebra/src/MONOCHROME2ToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME2ToRGB.o ../imebra/src/MONOCHROME2ToRGB.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transformsChain.o: ../imebra/src/transformsChain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transformsChain.o ../imebra/src/transformsChain.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/streamController.o: ../base/src/streamController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/streamController.o ../base/src/streamController.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/criticalSection.o: ../base/src/criticalSection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/criticalSection.o ../base/src/criticalSection.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/buffer.o: ../imebra/src/buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/buffer.o ../imebra/src/buffer.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/waveform.o: ../imebra/src/waveform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/waveform.o ../imebra/src/waveform.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/data.o: ../imebra/src/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/data.o ../imebra/src/data.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/colorTransform.o: ../imebra/src/colorTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/colorTransform.o ../imebra/src/colorTransform.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringUI.o: ../imebra/src/dataHandlerStringUI.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringUI.o ../imebra/src/dataHandlerStringUI.cpp

${OBJECTDIR}/CImbx_tests/streamBitsTest.o: CImbx_tests/streamBitsTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/streamBitsTest.o CImbx_tests/streamBitsTest.cpp

${OBJECTDIR}/CImbx_tests/transactionTest.o: CImbx_tests/transactionTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/transactionTest.o CImbx_tests/transactionTest.cpp

${OBJECTDIR}/CImbx_tests/dataSetTest.o: CImbx_tests/dataSetTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/dataSetTest.o CImbx_tests/dataSetTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/charsetConversion.o: ../base/src/charsetConversion.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/charsetConversion.o ../base/src/charsetConversion.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/modalityVOILUT.o: ../imebra/src/modalityVOILUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/modalityVOILUT.o ../imebra/src/modalityVOILUT.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/codecFactory.o: ../imebra/src/codecFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/codecFactory.o ../imebra/src/codecFactory.cpp

${OBJECTDIR}/CImbx_tests/jpegCodecTest.o: CImbx_tests/jpegCodecTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/jpegCodecTest.o CImbx_tests/jpegCodecTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/LUT.o: ../imebra/src/LUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/LUT.o ../imebra/src/LUT.cpp

${OBJECTDIR}/CImbx_tests/bitTransformTest.o: CImbx_tests/bitTransformTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/bitTransformTest.o CImbx_tests/bitTransformTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/exception.o: ../base/src/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/exception.o ../base/src/exception.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToYBRPARTIAL.o: ../imebra/src/RGBToYBRPARTIAL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToYBRPARTIAL.o ../imebra/src/RGBToYBRPARTIAL.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerDateTime.o: ../imebra/src/dataHandlerDateTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerDateTime.o ../imebra/src/dataHandlerDateTime.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataGroup.o: ../imebra/src/dataGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataGroup.o ../imebra/src/dataGroup.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME1ToMONOCHROME2.o: ../imebra/src/MONOCHROME1ToMONOCHROME2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME1ToMONOCHROME2.o ../imebra/src/MONOCHROME1ToMONOCHROME2.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/streamWriter.o: ../base/src/streamWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/streamWriter.o ../base/src/streamWriter.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dibCodec.o: ../imebra/src/dibCodec.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dibCodec.o ../imebra/src/dibCodec.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringSH.o: ../imebra/src/dataHandlerStringSH.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringSH.o ../imebra/src/dataHandlerStringSH.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringUT.o: ../imebra/src/dataHandlerStringUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringUT.o ../imebra/src/dataHandlerStringUT.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/huffmanTable.o: ../base/src/huffmanTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/huffmanTable.o ../base/src/huffmanTable.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/image.o: ../imebra/src/image.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/image.o ../imebra/src/image.cpp

${OBJECTDIR}/CImbx_tests/dateTimeHandlerTest.o: CImbx_tests/dateTimeHandlerTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/dateTimeHandlerTest.o CImbx_tests/dateTimeHandlerTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/streamReader.o: ../base/src/streamReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/streamReader.o ../base/src/streamReader.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transformHighBit.o: ../imebra/src/transformHighBit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transformHighBit.o ../imebra/src/transformHighBit.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/codec.o: ../imebra/src/codec.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/codec.o ../imebra/src/codec.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/VOILUT.o: ../imebra/src/VOILUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/VOILUT.o ../imebra/src/VOILUT.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerString.o: ../imebra/src/dataHandlerString.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerString.o ../imebra/src/dataHandlerString.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToYBRFULL.o: ../imebra/src/RGBToYBRFULL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToYBRFULL.o ../imebra/src/RGBToYBRFULL.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/charsetsList.o: ../imebra/src/charsetsList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/charsetsList.o ../imebra/src/charsetsList.cpp

${OBJECTDIR}/CImbx_tests/dicomCodecTest.o: CImbx_tests/dicomCodecTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/dicomCodecTest.o CImbx_tests/dicomCodecTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transform.o: ../imebra/src/transform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transform.o ../imebra/src/transform.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/colorTransformsFactory.o: ../imebra/src/colorTransformsFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/colorTransformsFactory.o ../imebra/src/colorTransformsFactory.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringDS.o: ../imebra/src/dataHandlerStringDS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringDS.o ../imebra/src/dataHandlerStringDS.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dicomCodec.o: ../imebra/src/dicomCodec.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dicomCodec.o ../imebra/src/dicomCodec.cpp

${OBJECTDIR}/CImbx_tests/numericHandlerTest.o: CImbx_tests/numericHandlerTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/numericHandlerTest.o CImbx_tests/numericHandlerTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringLO.o: ../imebra/src/dataHandlerStringLO.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringLO.o ../imebra/src/dataHandlerStringLO.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME1ToRGB.o: ../imebra/src/MONOCHROME1ToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME1ToRGB.o ../imebra/src/MONOCHROME1ToRGB.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandler.o: ../imebra/src/dataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandler.o ../imebra/src/dataHandler.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/baseStream.o: ../base/src/baseStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/baseStream.o ../base/src/baseStream.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringAE.o: ../imebra/src/dataHandlerStringAE.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringAE.o ../imebra/src/dataHandlerStringAE.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/YBRFULLToRGB.o: ../imebra/src/YBRFULLToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/YBRFULLToRGB.o ../imebra/src/YBRFULLToRGB.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringAS.o: ../imebra/src/dataHandlerStringAS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringAS.o ../imebra/src/dataHandlerStringAS.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transaction.o: ../imebra/src/transaction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transaction.o ../imebra/src/transaction.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringCS.o: ../imebra/src/dataHandlerStringCS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringCS.o ../imebra/src/dataHandlerStringCS.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/PALETTECOLORToRGB.o: ../imebra/src/PALETTECOLORToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/PALETTECOLORToRGB.o ../imebra/src/PALETTECOLORToRGB.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/viewHelper.o: ../imebra/src/viewHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/viewHelper.o ../imebra/src/viewHelper.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dicomDir.o: ../imebra/src/dicomDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dicomDir.o ../imebra/src/dicomDir.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerDate.o: ../imebra/src/dataHandlerDate.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerDate.o ../imebra/src/dataHandlerDate.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/thread.o: ../base/src/thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/thread.o ../base/src/thread.cpp

${OBJECTDIR}/CImbx_tests/paletteTest.o: CImbx_tests/paletteTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/paletteTest.o CImbx_tests/paletteTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/jpegCodec.o: ../imebra/src/jpegCodec.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/jpegCodec.o ../imebra/src/jpegCodec.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/baseObject.o: ../base/src/baseObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/baseObject.o ../base/src/baseObject.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToPALETTECOLOR.o: ../imebra/src/RGBToPALETTECOLOR.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToPALETTECOLOR.o ../imebra/src/RGBToPALETTECOLOR.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transformBuffers.o: ../imebra/src/transformBuffers.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/transformBuffers.o ../imebra/src/transformBuffers.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/drawBitmap.o: ../imebra/src/drawBitmap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/drawBitmap.o ../imebra/src/drawBitmap.cpp

${OBJECTDIR}/CImbx_tests/huffmanTest.o: CImbx_tests/huffmanTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/huffmanTest.o CImbx_tests/huffmanTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/stream.o: ../base/src/stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/stream.o ../base/src/stream.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/memory.o: ../base/src/memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/memory.o ../base/src/memory.cpp

${OBJECTDIR}/CImbx_tests/dicomDirTest.o: CImbx_tests/dicomDirTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/dicomDirTest.o CImbx_tests/dicomDirTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME2ToYBRFULL.o: ../imebra/src/MONOCHROME2ToYBRFULL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/MONOCHROME2ToYBRFULL.o ../imebra/src/MONOCHROME2ToYBRFULL.cpp

${OBJECTDIR}/CImbx_tests/unicodeStringHandlerTest.o: CImbx_tests/unicodeStringHandlerTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/unicodeStringHandlerTest.o CImbx_tests/unicodeStringHandlerTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerDateTimeBase.o: ../imebra/src/dataHandlerDateTimeBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerDateTimeBase.o ../imebra/src/dataHandlerDateTimeBase.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dicomDict.o: ../imebra/src/dicomDict.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dicomDict.o ../imebra/src/dicomDict.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/YBRFULLToMONOCHROME2.o: ../imebra/src/YBRFULLToMONOCHROME2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/YBRFULLToMONOCHROME2.o ../imebra/src/YBRFULLToMONOCHROME2.cpp

${OBJECTDIR}/CImbx_tests/ageStringHandlerTest.o: CImbx_tests/ageStringHandlerTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/ageStringHandlerTest.o CImbx_tests/ageStringHandlerTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToMONOCHROME2.o: ../imebra/src/RGBToMONOCHROME2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/RGBToMONOCHROME2.o ../imebra/src/RGBToMONOCHROME2.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/YBRPARTIALToRGB.o: ../imebra/src/YBRPARTIALToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/YBRPARTIALToRGB.o ../imebra/src/YBRPARTIALToRGB.cpp

${OBJECTDIR}/CImbx_tests/memoryStreamTest.o: CImbx_tests/memoryStreamTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/memoryStreamTest.o CImbx_tests/memoryStreamTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/memoryStream.o: ../base/src/memoryStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../base/src/memoryStream.o ../base/src/memoryStream.cpp

${OBJECTDIR}/CImbx_tests/bufferTest.o: CImbx_tests/bufferTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/bufferTest.o CImbx_tests/bufferTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerTime.o: ../imebra/src/dataHandlerTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerTime.o ../imebra/src/dataHandlerTime.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataSet.o: ../imebra/src/dataSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataSet.o ../imebra/src/dataSet.cpp

${OBJECTDIR}/CImbx_tests/CImbx_tests.o: CImbx_tests/CImbx_tests.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/CImbx_tests.o CImbx_tests/CImbx_tests.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringUnicode.o: ../imebra/src/dataHandlerStringUnicode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringUnicode.o ../imebra/src/dataHandlerStringUnicode.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringIS.o: ../imebra/src/dataHandlerStringIS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringIS.o ../imebra/src/dataHandlerStringIS.cpp

${OBJECTDIR}/CImbx_tests/exceptionsTest.o: CImbx_tests/exceptionsTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/exceptionsTest.o CImbx_tests/exceptionsTest.cpp

${OBJECTDIR}/CImbx_tests/buildImageForTest.o: CImbx_tests/buildImageForTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/CImbx_tests
	$(COMPILE.cc) -g -o ${OBJECTDIR}/CImbx_tests/buildImageForTest.o CImbx_tests/buildImageForTest.cpp

${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringLT.o: ../imebra/src/dataHandlerStringLT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/home/paolo/NetBeansProjects/imebra/project_files/tests/../imebra/src/dataHandlerStringLT.o ../imebra/src/dataHandlerStringLT.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/tests

# Subprojects
.clean-subprojects:
