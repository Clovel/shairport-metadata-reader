/**
 * MetaDataReader
 */

#ifndef METADATAREADER_HPP
#define METADATAREADER_HPP

/* Include --------------------------------------------- */
#include <string>

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
            MetaDataReader(FILE * const pFile);
            virtual ~MetaDataReader();

            /* Getters */
            FILE *file(void) const;

            /* Setters */
            void setFile(FILE *pFile);

            bool readHeader(MetaData * const pMetaData);
            bool readBase64Data(const MetaData * const pMetaData, std::string &pDecodedData);
            bool readEndTag(void) const;
        private:
            FILE *mFile;

            tools::Base64Encoder *mBase64Encoder;
    };
}

#endif /* METADATAREADER_HPP */