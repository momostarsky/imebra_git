#
# This application reads the part 6 of the Dicom standard (in XML format) and generates the enumeration file
# enumerating all the known tags and the Dicom dictionary definition file.
#
#-----------------------------------------------------------------------------------------------------------

import xml.etree.ElementTree as ET
import getopt
import sys

#
# Main
#
#-----
def main():

    xml_file = None
    include_folder = None
    implementation_folder = None
    try:
        opts, args = getopt.getopt(sys.argv[1:], "", ["help", "xml=", "includeFolder=", "implementationFolder="])
    except getopt.GetoptError as err:
        # print help information and exit:
        print str(err)
        usage()
        sys.exit(2)

    for option, value in opts:
        if option == '--help':
            usage()
            sys.exit(0)

        if option == '--xml':
            xml_file = value

        if option == '--includeFolder':
            include_folder = value

        if option == "--implementationFolder":
            implementation_folder = value

    if xml_file is None:
        print "Missing xml file"
        usage()
        sys.exit(2)

    if include_folder is None:
        print "Missing include folder"
        usage()
        sys.exit(2)

    if implementation_folder is None:
        print "Missing implementation folder"
        usage()
        sys.exit(2)

    # Read the Dictionary file (part 6)
    #----------------------------------
    tree = ET.parse(xml_file)

    # Generate the enumeration file
    #------------------------------
    enumeration_file = open(include_folder + '/tagsEnumeration.h', 'w')
    enumeration_file.write(
        '/*\n'
        '/*\n'
        'Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.\n'
        '\n'
        'Imebra is available for free under the GNU General Public License.\n'
        '\n'
        'The full text of the license is available in the file license.rst\n'
        ' in the project root folder.\n'
        '\n'
        'If you do not want to be bound by the GPL terms (such as the requirement\n'
        ' that your application must also be GPL), you may purchase a commercial\n'
        ' license for Imebra from the Imebra’s website (http://imebra.com).\n'
        '*/\n'
        '/* This file was automatically generated\n'
        '*/\n'
        '\n'
        '#if !defined(imebraTagsEnumeration__INCLUDED_)\n'
        '#define imebraTagsEnumeration__INCLUDED_\n'
        'namespace imebra\n'
        '{\n'
        '\n'
        '/// \\brief Enumerates the tags stored in the DicomDictionary.\n'
        '///\n'
        '/// Can be used with TagId to create an ID for a known tag.\n'
        '///\n'
        '/// Unlike other enumerations, each item starts with an uppercase letter, to\n'
        '/// reflect the tag name used in the Dicom standard.\n'
        '///\n'
        '///////////////////////////////////////////////////////////////////////////////\n'
        'enum class tagId_t: std::uint32_t\n'
        '{\n')

    # Write the tags dictionary
    #--------------------------
    dictionary_file = open(implementation_folder + '/tagsDescription.h', 'w')
    dictionary_file.write(
        '/*\n'
        '$fileHeader$\n'
        '*/\n'
        '/* This file was automatically generated\n'
        '*/\n'
        '\n'
        '#if !defined(imebraTagsDescription__INCLUDED_)\n'
        '#define imebraTagsDescription__INCLUDED_\n'
        '\n'
        '#include "../include/imebra/definitions.h"\n'
        '\n'
        'namespace imebra\n'
        '{\n'
        '\n'
        'namespace implementation\n'
        '{\n'
        '\n'
        '/// \\brief Tags description and VR.\n'
        '///\n'
        '///////////////////////////////////////////////////////////////////////////////\n'
        'struct tagDescription_t\n'
        '{\n'
        '    const   std::uint32_t m_tagId;     ///< Tag group and id\n'
        '    const   wchar_t* m_tagDescription; ///< Tag description\n'
        '    const   char* m_tagKeyword;        ///< Tag keyword\n'
        '    tagVR_t m_vr;                      ///< Default VR\n'
        '};\n'
        ''
        'static const tagDescription_t m_tagsDescription[] = \n'
        '    {\n'

    )


    # Read all the tables containing definitions of the tags
    #-------------------------------------------------------
    extract_table(tree.getroot(), enumeration_file, dictionary_file)

    # Write the enumeration's footer
    #-------------------------------
    enumeration_file.write(
        '    endOfEnumerations = 0\n'
        '};\n'
        '\n'
        '} //namespace imebra\n'
        '\n'
        '#endif // imebraTagsEnumeration__INCLUDED_\n'
        '\n')

    # Write the dictionary's footer
    #------------------------------
    dictionary_file.write(
        '        {0, 0, 0, tagVR_t::defaultType}\n'
        '    };\n'
        '\n'
        '} // namespace implementation\n'
        '\n'
        '} // namespace imebra\n'
        '\n'
        '#endif // imebraTagsDescription__INCLUDED_\n'
        '\n'
    )

def extract_table(root, enumeration_file, dictionary_file):
    enumeration = {}
    definition = {}

    for chapter in root.findall('{http://docbook.org/ns/docbook}chapter'):

        for table in chapter.findall('{http://docbook.org/ns/docbook}table'):
            body = table.find('{http://docbook.org/ns/docbook}tbody')
            for row in body.findall('{http://docbook.org/ns/docbook}tr'):

                columns = row.findall('{http://docbook.org/ns/docbook}td')
                paragraphs = []
                for column in columns:
                    text = column.find('{http://docbook.org/ns/docbook}para').text
                    if text is None:
                        break
                    paragraphs.append(text.encode('ascii', 'ignore'))

                if len(paragraphs) >= 5 and paragraphs[0] is not None and paragraphs[0].startswith('(') and paragraphs[0].endswith(')'):
                    group = paragraphs[0][1:5].replace('x', '0')
                    id = paragraphs[0][6:10]
                    enumeration_item = paragraphs[2] + '_' + group + '_' + id

                    vr = paragraphs[3].split(' ')[0]
                    if len(vr) != 2:
                        vr = 'defaultType'

                    enumeration[paragraphs[0]] = '    ' + enumeration_item + ' = 0x' + group + id + ', ///< ' + paragraphs[1] + ' ' + paragraphs[0] + '\n'
                    definition[paragraphs[0]] = '        { 0x' + group + id + ', L"' + paragraphs[1] + '", "' + paragraphs[2] + '", tagVR_t::' + vr + '},\n'

    for id in sorted(enumeration.keys()):
        enumeration_file.write(enumeration[id])
        dictionary_file.write(definition[id])

def usage():
    print "Usage: imera_generate_dictionary --xml=path_to_part6.xml --includeFolder=path_to_imebra_include --implementationFolder=path_to_imebra_implementation"

if __name__ == "__main__":
    main()
