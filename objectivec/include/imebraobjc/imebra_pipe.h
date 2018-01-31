/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcPipe__INCLUDED_)
#define imebraObjcPipe__INCLUDED_

#import "imebra_baseStreamInputOutput.h"
#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class Pipe;
}
#endif

@class ImebraReadMemory;
@class ImebraReadWriteMemory;

@interface ImebraPipe: ImebraBaseStreamInputOutput

    -(id)initWithBufferSize:(unsigned int)circularBufferSize;

    ///
    /// \brief Copy data into the Pipe so it can be retrieved by a
    ///        codec via a StreamReader.
    ///
    /// \param buffer the data to copy into the Pipe's buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) feed:(ImebraReadMemory*)buffer error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));


    ///
    /// \brief Read data from the Pipe. The data can be pushed into the pipe via
    ///        a StreamWriter.
    ///
    /// \param buffer   a buffer that will contain the read data. The method will
    ///                 try to read as many bytes as the buffer size
    /// \return the number of bytes read from the pipe, which may be less than the
    ///         buffer's size
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned int) sink:(ImebraReadWriteMemory*)buffer error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Wait for the specified amount of time or until the internal buffer
    ///        is empty (all the data fed has been retrieved by the StreamReader
    ///        or by sink()), whichever comes first, then call terminate().
    ///
    /// Subsequent read and write operations will fail by throwing the
    /// exception StreamClosedError.
    ///
    /// \param timeoutMilliseconds the maximum time to wait until the internal
    ///                            buffer is empty, in milliseconds
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) close: (unsigned int) timeoutMilliseconds error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Instruct any pending operation to terminate.
    ///
    /// Current and subsequent read and write operations will fail by
    /// throwing the exception StreamClosedError.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) terminate;

@end

#endif // !defined(imebraObjcPipe__INCLUDED_)
