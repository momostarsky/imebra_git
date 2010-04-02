#
# Generated Makefile - do not edit!
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
AS=

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release_64
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringUT.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerTime.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dicomDict.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/exception.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/waveform.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringAS.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerDateTime.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataSet.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/YBRPARTIALToRGB.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringUnicode.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/thread.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dicomCodec.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandler.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringST.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/buffer.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/memoryStream.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/drawBitmap.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringAE.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToMONOCHROME2.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/streamReader.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transaction.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dibCodec.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transformBuffers.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transformHighBit.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToYBRFULL.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/streamController.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/viewHelper.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringUI.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerString.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/charsetConversion.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringLO.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringIS.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transformsChain.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToYBRPARTIAL.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/baseObject.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/codecFactory.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME1ToRGB.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/charsetsList.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringPN.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/criticalSection.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME1ToMONOCHROME2.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/codec.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME2ToYBRFULL.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringDS.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringSH.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/baseStream.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/modalityVOILUT.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerDate.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transform.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringLT.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/image.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataGroup.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/colorTransformsFactory.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerDateTimeBase.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/YBRFULLToMONOCHROME2.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToPALETTECOLOR.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/streamWriter.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/jpegCodec.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/data.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dicomDir.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringCS.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/huffmanTable.o \
	${OBJECTDIR}/dicom2jpeg.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/memory.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME2ToRGB.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/stream.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/LUT.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/YBRFULLToRGB.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/colorTransform.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/PALETTECOLORToRGB.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/VOILUT.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release_64.mk dist/Release_64/GNU-Linux-x86/dicom2jpeg

dist/Release_64/GNU-Linux-x86/dicom2jpeg: ${OBJECTFILES}
	${MKDIR} -p dist/Release_64/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dicom2jpeg ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringUT.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringUT.o ../../imebra/src/dataHandlerStringUT.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerTime.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerTime.o ../../imebra/src/dataHandlerTime.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dicomDict.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dicomDict.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dicomDict.o ../../imebra/src/dicomDict.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/exception.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/exception.o ../../base/src/exception.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/waveform.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/waveform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/waveform.o ../../imebra/src/waveform.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringAS.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringAS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringAS.o ../../imebra/src/dataHandlerStringAS.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerDateTime.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerDateTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerDateTime.o ../../imebra/src/dataHandlerDateTime.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataSet.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataSet.o ../../imebra/src/dataSet.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/YBRPARTIALToRGB.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/YBRPARTIALToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/YBRPARTIALToRGB.o ../../imebra/src/YBRPARTIALToRGB.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringUnicode.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringUnicode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringUnicode.o ../../imebra/src/dataHandlerStringUnicode.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/thread.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/thread.o ../../base/src/thread.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dicomCodec.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dicomCodec.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dicomCodec.o ../../imebra/src/dicomCodec.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandler.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandler.o ../../imebra/src/dataHandler.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringST.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringST.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringST.o ../../imebra/src/dataHandlerStringST.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/buffer.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/buffer.o ../../imebra/src/buffer.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/memoryStream.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/memoryStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/memoryStream.o ../../base/src/memoryStream.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/drawBitmap.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/drawBitmap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/drawBitmap.o ../../imebra/src/drawBitmap.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringAE.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringAE.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringAE.o ../../imebra/src/dataHandlerStringAE.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToMONOCHROME2.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/RGBToMONOCHROME2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToMONOCHROME2.o ../../imebra/src/RGBToMONOCHROME2.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/streamReader.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/streamReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/streamReader.o ../../base/src/streamReader.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transaction.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/transaction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transaction.o ../../imebra/src/transaction.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dibCodec.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dibCodec.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dibCodec.o ../../imebra/src/dibCodec.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transformBuffers.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/transformBuffers.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transformBuffers.o ../../imebra/src/transformBuffers.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transformHighBit.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/transformHighBit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transformHighBit.o ../../imebra/src/transformHighBit.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToYBRFULL.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/RGBToYBRFULL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToYBRFULL.o ../../imebra/src/RGBToYBRFULL.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/streamController.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/streamController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/streamController.o ../../base/src/streamController.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/viewHelper.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/viewHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/viewHelper.o ../../imebra/src/viewHelper.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringUI.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringUI.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringUI.o ../../imebra/src/dataHandlerStringUI.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerString.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerString.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerString.o ../../imebra/src/dataHandlerString.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/charsetConversion.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/charsetConversion.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/charsetConversion.o ../../base/src/charsetConversion.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringLO.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringLO.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringLO.o ../../imebra/src/dataHandlerStringLO.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringIS.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringIS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringIS.o ../../imebra/src/dataHandlerStringIS.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transformsChain.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/transformsChain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transformsChain.o ../../imebra/src/transformsChain.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToYBRPARTIAL.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/RGBToYBRPARTIAL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToYBRPARTIAL.o ../../imebra/src/RGBToYBRPARTIAL.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/baseObject.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/baseObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/baseObject.o ../../base/src/baseObject.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/codecFactory.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/codecFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/codecFactory.o ../../imebra/src/codecFactory.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME1ToRGB.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/MONOCHROME1ToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME1ToRGB.o ../../imebra/src/MONOCHROME1ToRGB.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/charsetsList.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/charsetsList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/charsetsList.o ../../imebra/src/charsetsList.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringPN.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringPN.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringPN.o ../../imebra/src/dataHandlerStringPN.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/criticalSection.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/criticalSection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/criticalSection.o ../../base/src/criticalSection.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME1ToMONOCHROME2.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/MONOCHROME1ToMONOCHROME2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME1ToMONOCHROME2.o ../../imebra/src/MONOCHROME1ToMONOCHROME2.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/codec.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/codec.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/codec.o ../../imebra/src/codec.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME2ToYBRFULL.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/MONOCHROME2ToYBRFULL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME2ToYBRFULL.o ../../imebra/src/MONOCHROME2ToYBRFULL.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringDS.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringDS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringDS.o ../../imebra/src/dataHandlerStringDS.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringSH.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringSH.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringSH.o ../../imebra/src/dataHandlerStringSH.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/baseStream.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/baseStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/baseStream.o ../../base/src/baseStream.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/modalityVOILUT.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/modalityVOILUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/modalityVOILUT.o ../../imebra/src/modalityVOILUT.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerDate.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerDate.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerDate.o ../../imebra/src/dataHandlerDate.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transform.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/transform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/transform.o ../../imebra/src/transform.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringLT.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringLT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringLT.o ../../imebra/src/dataHandlerStringLT.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/image.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/image.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/image.o ../../imebra/src/image.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataGroup.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataGroup.o ../../imebra/src/dataGroup.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/colorTransformsFactory.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/colorTransformsFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/colorTransformsFactory.o ../../imebra/src/colorTransformsFactory.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerDateTimeBase.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerDateTimeBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerDateTimeBase.o ../../imebra/src/dataHandlerDateTimeBase.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/YBRFULLToMONOCHROME2.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/YBRFULLToMONOCHROME2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/YBRFULLToMONOCHROME2.o ../../imebra/src/YBRFULLToMONOCHROME2.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToPALETTECOLOR.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/RGBToPALETTECOLOR.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/RGBToPALETTECOLOR.o ../../imebra/src/RGBToPALETTECOLOR.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/streamWriter.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/streamWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/streamWriter.o ../../base/src/streamWriter.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/jpegCodec.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/jpegCodec.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/jpegCodec.o ../../imebra/src/jpegCodec.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/data.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/data.o ../../imebra/src/data.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dicomDir.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dicomDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dicomDir.o ../../imebra/src/dicomDir.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringCS.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/dataHandlerStringCS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/dataHandlerStringCS.o ../../imebra/src/dataHandlerStringCS.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/huffmanTable.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/huffmanTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/huffmanTable.o ../../base/src/huffmanTable.cpp

${OBJECTDIR}/dicom2jpeg.o: nbproject/Makefile-${CND_CONF}.mk dicom2jpeg.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/dicom2jpeg.o dicom2jpeg.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/memory.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/memory.o ../../base/src/memory.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME2ToRGB.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/MONOCHROME2ToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/MONOCHROME2ToRGB.o ../../imebra/src/MONOCHROME2ToRGB.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/stream.o: nbproject/Makefile-${CND_CONF}.mk ../../base/src/stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/base/src/stream.o ../../base/src/stream.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/LUT.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/LUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/LUT.o ../../imebra/src/LUT.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/YBRFULLToRGB.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/YBRFULLToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/YBRFULLToRGB.o ../../imebra/src/YBRFULLToRGB.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/colorTransform.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/colorTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/colorTransform.o ../../imebra/src/colorTransform.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/PALETTECOLORToRGB.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/PALETTECOLORToRGB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/PALETTECOLORToRGB.o ../../imebra/src/PALETTECOLORToRGB.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/VOILUT.o: nbproject/Makefile-${CND_CONF}.mk ../../imebra/src/VOILUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/imebra/src/VOILUT.o ../../imebra/src/VOILUT.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release_64
	${RM} dist/Release_64/GNU-Linux-x86/dicom2jpeg

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
