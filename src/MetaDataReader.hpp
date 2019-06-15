/**
 * MetaDataReader
 */

#ifndef METADATAREADER_HPP
#define METADATAREADER_HPP

/* Include --------------------------------------------- */
#include <string>
#include <iosfwd>

#include <cstdio>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
namespace tools {
    class Base64Encoder;
}

namespace metadata {
    class MetaData;

    class MetaDataReader {
        public:
            MetaDataReader(std::ifstream * const pStream);
            virtual ~MetaDataReader();

            /* Getters */
            std::ifstream *fileStream(void) const;

            /* Setters */
            void setFileStream(std::ifstream * const pStream);

            bool readHeader(MetaData * const pMetaData);
            bool readBase64Data(const MetaData * const pMetaData, std::string &pDecodedData);
            bool processTags(MetaData * const pMetaData, const std::string &pPayload);

        private:
            bool readEndTag(void) const;
            bool checkBase64EndSection(void) const;

            std::ifstream *mFileStream;

            tools::Base64Encoder *mBase64Encoder;
    };
}

#endif /* METADATAREADER_HPP */
