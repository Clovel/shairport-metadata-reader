/**
 * MetaDataReader
 */

/* Include --------------------------------------------- */
#include "MetaDataReader.hpp"
#include "MetaData.hpp"

#include "Base64Encoder.hpp"

#include <cstdio>
#include <cstdint>

/* Class implementation -------------------------------- */
namespace metadata {
    MetaDataReader::MetaDataReader(FILE * const mFile) : 
        mFile(mFile), 
        mBase64Encoder(&tools::Base64Encoder::instance())
    {
        /* Empty */
    }

    MetaDataReader::~MetaDataReader() {
        mFile = nullptr;
    }

    /* Getters */
    FILE *MetaDataReader::file(void) const {
        return mFile;
    }

    /* Setters */
    void MetaDataReader::setFile(FILE *pFile) {
        mFile = pFile;
    }

    bool MetaDataReader::readHeader(MetaData * const pMetaData) {
        char lStr[1024];

        /* Get the header */
        if(std::fgets(lStr, 1024, mFile)) {
            /* Decipher the header's contents */
            uint32_t lType = 0U, lCode = 0U, lLength = 0U;

            int lResult = std::sscanf(lStr, "<item><type>%8x</type><code>%8x</code><length>%u</length>", &lType, &lCode, &lLength);
            if(3 == lResult) {
                /* We got all three values */

                /* TODO : Check data validity */

                pMetaData->setType(lType);
                pMetaData->setCode(lCode);
                pMetaData->setLength(lLength);

                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool MetaDataReader::readBase64Data(const MetaData * const pMetaData, std::string &pDecodedData) {
        /* Check if the data that follows is Base64 data */
        if(0 == std::fscanf(mFile, "<data encoding=\"base64\">")) {
            /* Base 64 data */

            /* TODO : Why this step ? */
            int lC = std::fgetc(mFile);
            (void)lC; /* Useless until proven otherwise */

            /* Calculate the size of the Base64 data */
            /* TODO : Find equation source */
            size_t lB64Length = 4 * ((pMetaData->length() + 2) / 3);

            /* Allocate memory for the Base64 data */
            char *lB64Data = (char *)std::malloc(lB64Length + 1);

            /* Was memory allocation successful ? */
            if(nullptr != lB64Data) {
                /* It was ! */

                /* Read the Base64 data */
                if(std::fgets(lB64Data, lB64Length + 1, mFile)) {
                    /** It seems that we have found B64 data 
                     * printf("Looks like we got it, with a buffer size of %u.\n",b64size);
                     * puts(lB64Buffer);
                     * printf("\n");
                     */

                    std::string lB64DataString(lB64Data);

                    /* If it is not a picture, decode the Base64 data */
                    if('PICT' != pMetaData->code()) {
                        //int lInputLength = 32768, lOutputLength = 32768; /* TODO : Magic number */
                        /**
                         * WARNING : These arbitrary values come from the 
                         * original example from @mikebrady on GitHub : 
                         * https://github.com/mikebrady/shairport-sync-metadata-reader
                         * 
                         * I opened an issue (#17) to ask if the difference in value is intentional. 
                         * 
                         * Anyway this value will be overwitten. 
                         * 
                         * FOLLOW-UP : @mikebradu answered. lInputLength = 32768. He also said : 
                         * "Thanks for the post. It's a mistake 
                         * I was thinking of 32768. You are right that is can be overwritten 
                         * It will be replaced by the true size of the incoming picture 
                         * data if less than 32768 bytes remain. 
                         * Typically, though, pictures are larger, 
                         * so this code has the effect of breaking the job of decoding 
                         * an incoming picture into chunks that won't exceed 32768 bytes."
                         * 
                         * Finally, I chose to not use these indexes, 
                         * but use std::string and size detection
                         */

                        pDecodedData = mBase64Encoder->decode(lB64DataString);
                    } else {
                        /* It is a picture ! */
                        /* TODO : Decode picture */

                        /* For now, return false */
                        return false;
                    }

                    return true;
                } else {
                    return false; /* Base64 data read failed ! */
                }
            } else {
                /* Memory allocation failed ! */
                return false;
            }
        } else {
            /* No Base64 data */
            return false;
        }
    }

    bool MetaDataReader::readEndTag(void) const {
        char lEndTag[64];
        const int lRc = std::fscanf(mFile, "%64s", lEndTag);
        if("</data></item>" == std::string(lEndTag)) {
            /* End data tag not seen, \"%s\" seen instead.\n */
        }
    }
}