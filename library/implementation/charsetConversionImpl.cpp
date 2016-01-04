#include "charsetConversionImpl.h"
#include "exceptionImpl.h"
#include "../include/imebra/exceptions.h"

namespace puntoexe
{

namespace imebra
{

std::string dicomConversion::convertFromUnicode(const std::wstring& unicodeString, charsetsList::tCharsetsList* pCharsets)
{
    PUNTOEXE_FUNCTION_START(L"dicomConversion::convertFromUnicode");

    // Check for the dicom charset's name
    ///////////////////////////////////////////////////////////
    if(pCharsets->empty())
    {
        throw std::logic_error("The charsets list must be set before converting from unicode");
    }

    // Setup the conversion objects
    ///////////////////////////////////////////////////////////
    std::unique_ptr<defaultCharsetConversion> localCharsetConversion(new defaultCharsetConversion(pCharsets->front()));

    // Get the escape sequences from the unicode conversion
    //  engine
    ///////////////////////////////////////////////////////////
    const charsetDictionary::escapeSequences_t& escapes(localCharsetConversion->getDictionary().getEscapeSequences());

    // Returned string
    ///////////////////////////////////////////////////////////
    std::string rawString;
    rawString.reserve(unicodeString.size());

    // Convert all the chars. Each char is tested with the
    //  active charset first, then with other charsets if
    //  the active one doesn't work
    ///////////////////////////////////////////////////////////
    for(size_t scanString = 0; scanString != unicodeString.size(); ++scanString)
    {
        // Get the UNICODE char. On windows the code may be spread
        //  across 2 16 bit wide codes.
        ///////////////////////////////////////////////////////////
        std::wstring code(size_t(1), unicodeString[scanString]);

        // Check UTF-16 extension (Windows only)
        ///////////////////////////////////////////////////////////
        if(sizeof(wchar_t) == 2)
        {
            if(code[0] >= 0xd800 && code[0] <=0xdfff && scanString < (unicodeString.size() - 1))
            {
                code += unicodeString[++scanString];
            }
        }

        // Check composed chars extension (diacritical marks)
        ///////////////////////////////////////////////////////////
        while(scanString < (unicodeString.size() - 1) && unicodeString[scanString + 1] >= 0x0300 && unicodeString[scanString + 1] <= 0x036f)
        {
            code += unicodeString[++scanString];
        }

        // Remember the return string size so we can check if we
        //  added something to it
        ///////////////////////////////////////////////////////////
        size_t currentRawSize(rawString.size());
        rawString += localCharsetConversion->fromUnicode(code);
        if(rawString.size() != currentRawSize)
        {
            // The conversion succeeded: continue with the next char
            ///////////////////////////////////////////////////////////
            continue;
        }

        // Find the escape sequence
        ///////////////////////////////////////////////////////////
        for(charsetDictionary::escapeSequences_t::const_iterator scanEscapes(escapes.begin()), endEscapes(escapes.end());
            scanEscapes != endEscapes;
            ++scanEscapes)
        {
            try
            {
                std::unique_ptr<defaultCharsetConversion> testEscapeSequence(new defaultCharsetConversion(scanEscapes->second));
                std::string convertedChar(testEscapeSequence->fromUnicode(code));
                if(!convertedChar.empty())
                {
                    rawString += scanEscapes->first;
                    rawString += convertedChar;

                    localCharsetConversion.reset(testEscapeSequence.release());

                    // Add the dicom charset to the charsets
                    ///////////////////////////////////////////////////////////
                    bool bAlreadyUsed = false;
                    for(charsetsList::tCharsetsList::const_iterator scanUsedCharsets = pCharsets->begin(); scanUsedCharsets != pCharsets->end(); ++scanUsedCharsets)
                    {
                        if(*scanUsedCharsets == scanEscapes->second)
                        {
                            bAlreadyUsed = true;
                            break;
                        }
                    }
                    if(!bAlreadyUsed)
                    {
                        pCharsets->push_back(scanEscapes->second);
                    }
                    break;
                }
            }
            catch(::imebra::charsetConversionExceptionNoSupportedTable)
            {
                continue;
            }
        }
    }

    return rawString;

    PUNTOEXE_FUNCTION_END();

}

std::wstring dicomConversion::convertToUnicode(const std::string& value, const charsetsList::tCharsetsList& charsets)
{
    PUNTOEXE_FUNCTION_START(L"dicomConversion::convertToUnicode");

    // Should we take care of the escape sequences...?
    ///////////////////////////////////////////////////////////
    if(charsets.empty())
    {
        throw std::logic_error("The charsets list must be set before converting to unicode");
    }

    // Initialize the conversion engine with the default
    //  charset
    ///////////////////////////////////////////////////////////
    std::unique_ptr<defaultCharsetConversion> localCharsetConversion(new defaultCharsetConversion(charsets.front()));

    // Only one charset is present: we don't need to check
    //  the escape sequences
    ///////////////////////////////////////////////////////////
    if(charsets.size() == 1)
    {
        return localCharsetConversion->toUnicode(value);
    }

    // Here we store the value to be returned
    ///////////////////////////////////////////////////////////
    std::wstring returnString;
    returnString.reserve(value.size());

    // Get the escape sequences from the unicode conversion
    //  engine
    ///////////////////////////////////////////////////////////
    const charsetDictionary::escapeSequences_t& escapeSequences(localCharsetConversion->getDictionary().getEscapeSequences());

    // Position and properties of the next escape sequence
    ///////////////////////////////////////////////////////////
    size_t escapePosition = std::string::npos;
    std::string escapeString;
    std::string isoTable;

    // Scan all the string and look for valid escape sequences.
    // The partial strings are converted using the dicom
    //  charset specified by the escape sequences.
    ///////////////////////////////////////////////////////////
    for(size_t scanString = 0; scanString < value.size(); /* empty */)
    {
        // Find the position of the next escape sequence
        ///////////////////////////////////////////////////////////
        if(escapePosition == std::string::npos)
        {
            escapePosition = value.size();
            for(charsetDictionary::escapeSequences_t::const_iterator scanEscapes(escapeSequences.begin()), endEscapes(escapeSequences.end());
                scanEscapes != endEscapes;
                ++scanEscapes)
            {
                size_t findEscape = value.find(scanEscapes->first, scanString);
                if(findEscape != std::string::npos && findEscape < escapePosition)
                {
                    escapePosition = findEscape;
                    escapeString = scanEscapes->first;
                    isoTable = scanEscapes->second;
                }
            }
        }

        // No more escape sequences. Just convert everything
        ///////////////////////////////////////////////////////////
        if(escapePosition == value.size())
        {
            return returnString + localCharsetConversion->toUnicode(value.substr(scanString));
        }

        // The escape sequence can wait, now we are still in the
        //  already activated charset
        ///////////////////////////////////////////////////////////
        if(escapePosition > scanString)
        {
            returnString += localCharsetConversion->toUnicode(value.substr(scanString, escapePosition - scanString));
            scanString = escapePosition;
            continue;
        }

        // Move the char pointer to the next char that has to be
        //  analyzed
        ///////////////////////////////////////////////////////////
        scanString = escapePosition + escapeString.length();
        escapePosition = std::string::npos;

        // An iso table is coupled to the found escape sequence.
        ///////////////////////////////////////////////////////////
        localCharsetConversion.reset(new defaultCharsetConversion(isoTable));
    }

    return returnString;

    PUNTOEXE_FUNCTION_END();

}

}

}


