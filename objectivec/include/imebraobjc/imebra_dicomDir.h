/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcDicomDir__INCLUDED_)
#define imebraObjcDicomDir__INCLUDED_

#import <Foundation/Foundation.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
    class DataSet;
    class DicomDirEntry;
    class DicomDir;
}
#endif

typedef NS_ENUM(unsigned int, ImebraDirectoryRecordType_t)
{
    ImebraDicomDirPatient,
    ImebraDicomDirStudy,
    ImebraDicomDirSeries,
    ImebraDicomDirImage,
    ImebraDicomDirOverlay,
    ImebraDicomDirModality_lut,
    ImebraDicomDirVoi_lut,
    ImebraDicomDirCurve,
    ImebraDicomDirTopic,
    ImebraDicomDirVisit,
    ImebraDicomDirResults,
    ImebraDicomDirInterpretation,
    ImebraDicomDirStudy_component,
    ImebraDicomDirStored_print,
    ImebraDicomDirRt_dose,
    ImebraDicomDirRt_structure_set,
    ImebraDicomDirRt_plan,
    ImebraDicomDirRt_treat_record,
    ImebraDicomDirPresentation,
    ImebraDicomDirWaveform,
    ImebraDicomDirSr_document,
    ImebraDicomDirKey_object_doc,
    ImebraDicomDirSpectroscopy,
    ImebraDicomDirRaw_data,
    ImebraDicomDirRegistration,
    ImebraDicomDirFiducial,
    ImebraDicomDirMrdr,
    ImebraDicomDirEndOfDirectoryRecordTypes
};


@class ImebraDataSet;

@interface ImebraDicomDirEntry: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::DicomDirEntry* m_pDicomDirEntry;
}

    -(id)initWithImebraDicomDirEntry:(imebra::DicomDirEntry*)pDicomDirEntry;

#endif
    -(void)dealloc;

    -(ImebraDataSet*)getEntryDataSet;

    -(ImebraDicomDirEntry*)getNextEntry;

    -(ImebraDicomDirEntry*)getFirstChildEntry;

    -(void)setNextEntry:(ImebraDicomDirEntry*)pNextEntry error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)setFirstChildEntry:(ImebraDicomDirEntry*)pFirstChildEntry error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(NSArray*)getFileParts:(NSError**)pError;

    -(void)setFileParts:(NSArray*)pFileParts error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(ImebraDirectoryRecordType_t)getType:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(NSString*)getTypeString:(NSError**)pError;

@end


@interface ImebraDicomDir: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::DicomDir* m_pDicomDir;
}

    -(id)initWithImebraDicomDir:(imebra::DicomDir*)pDicomDir;
#endif

    -(id)init;

    -(id)initFromDataSet:(ImebraDataSet*)pDataSet error:(NSError**)pError;

    -(void)dealloc;

    -(ImebraDicomDirEntry*)getNewEntry:(ImebraDirectoryRecordType_t)recordType error:(NSError**)pError;

    -(ImebraDicomDirEntry*)getFirstRootEntry:(NSError**)pError;

    -(void)setFirstRootEntry:(ImebraDicomDirEntry*)firstEntryRecord error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(ImebraDataSet*)updateDataSet:(NSError**)pError;

@end

#endif // imebraObjcDicomDir__INCLUDED_
