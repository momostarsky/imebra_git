/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file pipe.cpp
    \brief Implementation of the DataSink and DataSource classes.

*/

#include "../include/imebra/pipeStream.h"
#include "../include/imebra/baseStreamInput.h"
#include "../include/imebra/baseStreamOutput.h"
#include "../implementation/pipeImpl.h"
#include "../implementation/baseStreamImpl.h"

namespace imebra
{

PipeStream::PipeStream(size_t circularBufferSize):
    m_pStream(std::make_shared<implementation::pipeSequenceStream>(circularBufferSize))
{
}

PipeStream::PipeStream(const PipeStream& source):
    m_pStream(getPipeStreamImplementation(source))
{
}

PipeStream& PipeStream::operator=(const PipeStream& source)
{
    m_pStream = getPipeStreamImplementation(source);
    return *this;
}

void PipeStream::close(unsigned int timeoutMilliseconds)
{
     m_pStream->close(timeoutMilliseconds);
}

const std::shared_ptr<implementation::pipeSequenceStream>& getPipeStreamImplementation(const PipeStream& stream)
{
    return stream.m_pStream;
}

BaseStreamInput PipeStream::getStreamInput()
{
    return BaseStreamInput(std::make_shared<implementation::pipeSequenceStreamInput>(m_pStream));
}

BaseStreamOutput PipeStream::getStreamOutput()
{
    return BaseStreamOutput(std::make_shared<implementation::pipeSequenceStreamOutput>(m_pStream));
}

}

