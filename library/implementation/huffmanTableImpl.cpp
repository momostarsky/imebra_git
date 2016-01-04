/*
$fileHeader$
*/

/*! \file huffmanTable.cpp
    \brief Implementation of the huffman codec.

*/

#include "exceptionImpl.h"
#include "huffmanTableImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "../include/imebra/exceptions.h"

#include <list>
#include <string.h>

namespace puntoexe
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// huffmanTable
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
huffmanTable::huffmanTable(std::uint32_t maxValueLength)
{
	m_numValues=(1L<<(maxValueLength))+1L;

	reset();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Reset the class' attributes
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void huffmanTable::reset()
{
	PUNTOEXE_FUNCTION_START(L"huffmanTable::reset");

	m_valuesFreq.clear();
	m_valuesFreq.resize(m_numValues);

	m_orderedValues.resize(m_numValues);
	::memset(&(m_orderedValues[0]), 0, m_numValues*sizeof(m_orderedValues[0]));

	m_valuesToHuffman.resize(m_numValues);
	::memset(&(m_valuesToHuffman[0]), 0, m_numValues*sizeof(m_valuesToHuffman[0]));

	m_valuesToHuffmanLength.resize(m_numValues);
	::memset(&(m_valuesToHuffmanLength[0]), 0, m_numValues*sizeof(m_valuesToHuffmanLength[0]));

    m_valuesPerLength.fill(0);
    m_firstValidLength = 0;
    m_firstMinValue = 0xffffffff;
    m_firstMaxValue = 0xffffffff;
    m_firstValuesPerLength = 0;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Increase the frequency of one value
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void huffmanTable::incValueFreq(const std::uint32_t value)
{
	++(m_valuesFreq[value].m_freq);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Remove the last huffman code from the lengths table
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void huffmanTable::removeLastCode()
{
	// Find the number of codes
	///////////////////////////////////////////////////////////
	std::uint32_t codes = 0;
	std::uint32_t lastLength = 0;
	for(std::uint32_t scanLengths = 0; scanLengths < sizeof(m_valuesPerLength)/sizeof(m_valuesPerLength[0]); ++scanLengths)
    {
        if(m_valuesPerLength[scanLengths] == 0)
		{
			continue;
		}
        codes += m_valuesPerLength[scanLengths];
		lastLength = scanLengths;
	}
	if(lastLength == 0)
	{
		return;
	}
    m_valuesPerLength[lastLength]--;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the number of values for a specific length
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void huffmanTable::setValuesPerLength(std::uint32_t length, std::uint32_t numValues)
{
    if(length >= m_valuesPerLength.size())
    {
        throw ::imebra::huffmanExceptionCreateTable("Huffman code length too big");
    }
    m_valuesPerLength[length] = numValues;
}

void huffmanTable::addOrderedValue(size_t index, std::uint32_t value)
{
    if(index >= m_orderedValues.size())
    {
        throw ::imebra::huffmanExceptionCreateTable("Too many values in the huffman table");
    }
    m_orderedValues[index] = value;
}

std::uint32_t huffmanTable::getValuesPerLength(std::uint32_t length)
{
    return m_valuesPerLength[length];
}

std::uint32_t huffmanTable::getOrderedValue(size_t index)
{
    return m_orderedValues[index];
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Calculate the codes length
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void huffmanTable::calcHuffmanCodesLength(const std::uint32_t maxCodeLength)
{
	PUNTOEXE_FUNCTION_START(L"huffmanTable::calcHuffmanCodesLength");

	// Order the values by their frequency
	typedef std::map<huffmanTable::freqValue, bool, huffmanTable::freqValueCompare> tFreqOrderedMap;
	tFreqOrderedMap freqOrderedValues;

	for(size_t scanValues = 0; scanValues < m_valuesFreq.size(); ++scanValues)
	{
		if(m_valuesFreq[scanValues].m_freq != 0)
		{
			huffmanTable::freqValue key(m_valuesFreq[scanValues].m_freq, (std::uint32_t)scanValues);
			freqOrderedValues[key] = true;
		}
	}

	while(freqOrderedValues.size() > 1)
	{
		huffmanTable::freqValue key0(freqOrderedValues.begin()->first);
		freqOrderedValues.erase(freqOrderedValues.begin());
		huffmanTable::freqValue key1(freqOrderedValues.begin()->first);
		freqOrderedValues.erase(freqOrderedValues.begin());

		key0.m_freq += key1.m_freq;
		m_valuesFreq[key0.m_value].m_freq = key0.m_freq;
		m_valuesFreq[key1.m_value].m_freq = 0;
		m_valuesFreq[key0.m_value].m_codeLength++;

		freqOrderedValues[key0] = true;

		std::uint32_t chainedValue;
		for(chainedValue = key0.m_value; m_valuesFreq[chainedValue].m_nextCode != -1; /* empty */)
		{
			chainedValue = (std::uint32_t)m_valuesFreq[chainedValue].m_nextCode;
			m_valuesFreq[chainedValue].m_codeLength++;
		}
		m_valuesFreq[chainedValue].m_nextCode = key1.m_value;
		while(m_valuesFreq[chainedValue].m_nextCode != -1)
		{
			chainedValue = (std::uint32_t)m_valuesFreq[chainedValue].m_nextCode;
			m_valuesFreq[chainedValue].m_codeLength++;
		}
	}

	typedef std::map<huffmanTable::lengthValue, bool, huffmanTable::lengthValueCompare> tLengthOrderedMap;
    tLengthOrderedMap lengthOrderedValues ;
	for(size_t findValuesPerLength = 0; findValuesPerLength < m_valuesFreq.size(); ++findValuesPerLength)
	{
		if(m_valuesFreq[findValuesPerLength].m_codeLength != 0)
		{
			huffmanTable::lengthValue key(m_valuesFreq[findValuesPerLength].m_codeLength, (std::uint32_t)findValuesPerLength);
			lengthOrderedValues[key] = true;
			m_valuesPerLength[m_valuesFreq[findValuesPerLength].m_codeLength]++;
		}
	}

	long insertPosition = 0;
	for(tLengthOrderedMap::iterator scanLengths = lengthOrderedValues.begin(); scanLengths != lengthOrderedValues.end(); ++scanLengths)
	{
		m_orderedValues[insertPosition++] = scanLengths->first.m_value;
	}

	// Reduce the size of the codes' lengths
	for(std::uint32_t reduceLengths=sizeof(m_valuesPerLength)/sizeof(m_valuesPerLength[0]) - 1; reduceLengths>maxCodeLength; --reduceLengths)
	{
		while(m_valuesPerLength[reduceLengths] != 0)
		{
			std::int32_t reduceLengths1;
			for(reduceLengths1=reduceLengths-2; reduceLengths1 != -1 && m_valuesPerLength[reduceLengths1] == 0; --reduceLengths1){}

			if(reduceLengths1==-1)
			{
				break;
			}
			m_valuesPerLength[reduceLengths]-=2;
			m_valuesPerLength[reduceLengths-1]++;
			m_valuesPerLength[reduceLengths1+1]+=2;
			m_valuesPerLength[reduceLengths1]--;
		}
	}

	// Find the first available length
	for(m_firstValidLength = 1; m_firstValidLength != sizeof(m_valuesPerLength) / sizeof(m_valuesPerLength[0]); ++m_firstValidLength)
	{
		if(m_valuesPerLength[m_firstValidLength] != 0)
		{
			break;
		}
	}

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Calculate the huffman codes from the codes length
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void huffmanTable::calcHuffmanTables()
{
	PUNTOEXE_FUNCTION_START(L"huffmanTable::calcHuffmanTables");

	std::uint32_t huffmanCode = 0;

	std::uint32_t valueIndex = 0;

	::memset(m_minValuePerLength, 0xffffffff, sizeof(m_minValuePerLength));
	::memset(m_maxValuePerLength, 0xffffffff, sizeof(m_maxValuePerLength));
    m_firstValuesPerLength = 0;
    m_firstMinValue = 0xffffffff;
    m_firstMaxValue = 0xffffffff;
	m_firstValidLength = 0;
	for(std::uint32_t codeLength=1L; codeLength != sizeof(m_valuesPerLength)/sizeof(std::uint32_t); ++codeLength)
	{
		if(m_valuesPerLength[codeLength] != 0 && m_firstValidLength == 0)
		{
			m_firstValidLength = codeLength;
		}
		for(std::uint32_t generateCodes = 0; generateCodes<m_valuesPerLength[codeLength]; ++generateCodes)
		{
			if(generateCodes == 0)
			{
				m_minValuePerLength[codeLength]=huffmanCode;
			}
			m_maxValuePerLength[codeLength]=huffmanCode;
			m_valuesToHuffman[m_orderedValues[valueIndex]]=huffmanCode;
			m_valuesToHuffmanLength[m_orderedValues[valueIndex]]=codeLength;
			++valueIndex;
			++huffmanCode;
		}

		huffmanCode<<=1;

	}

    m_firstMinValue = m_minValuePerLength[m_firstValidLength];
    m_firstMaxValue = m_maxValuePerLength[m_firstValidLength];
    m_firstValuesPerLength = m_valuesPerLength[m_firstValidLength];

	PUNTOEXE_FUNCTION_END();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Read an Huffman code
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t huffmanTable::readHuffmanCode(streamReader* pStream)
{
    PUNTOEXE_FUNCTION_START(L"huffmanTable::readHuffmanCode");

    // Read initial number of bits
	std::uint32_t readBuffer(pStream->readBits(m_firstValidLength));

	// Validate the current Huffman code. If it's OK, then
	//  return the ordered value
	///////////////////////////////////////////////////////////
    if(readBuffer <= m_firstMaxValue)
	{
        return m_orderedValues[readBuffer - m_firstMinValue];
	}

    std::uint32_t orderedValue(m_firstValuesPerLength);

	// Scan all the codes sizes
	///////////////////////////////////////////////////////////
    for(std::uint8_t scanSize(m_firstValidLength + 1), missingBits(0); scanSize != sizeof(m_valuesPerLength)/sizeof(m_valuesPerLength[0]); ++scanSize)
	{
		++missingBits;

		// If the active length is empty, then continue the loop
		///////////////////////////////////////////////////////////
		if(m_valuesPerLength[scanSize] == 0)
		{
			continue;
		}

		readBuffer <<= missingBits;
		if(missingBits == 1)
		{
			readBuffer |= pStream->readBit();
		}
		else
		{
			readBuffer |= pStream->readBits(missingBits);
		}

		// Validate the current Huffman code. If it's OK, then
		//  return the ordered value
		///////////////////////////////////////////////////////////
		if(readBuffer<=m_maxValuePerLength[scanSize])
		{
			return m_orderedValues[orderedValue + readBuffer - m_minValuePerLength[scanSize]];
		}

		orderedValue += m_valuesPerLength[scanSize];

		// Reset the number of bits to read in one go
		///////////////////////////////////////////////////////////
		missingBits = 0;

	}

    PUNTOEXE_THROW(::imebra::huffmanExceptionRead, "Invalid huffman code found while reading from a stream");

    PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Write an Huffman code
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void huffmanTable::writeHuffmanCode(const std::uint32_t code, streamWriter* pStream)
{
	PUNTOEXE_FUNCTION_START(L"huffmanTable::writeHuffmanCode");

	if(m_valuesToHuffmanLength[code] == 0)
	{
        PUNTOEXE_THROW(::imebra::huffmanExceptionWrite, "Trying to write an invalid huffman code");
	}
	pStream->writeBits(m_valuesToHuffman[code], m_valuesToHuffmanLength[code]);

	PUNTOEXE_FUNCTION_END();
}

} // namespace puntoexe

