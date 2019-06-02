/**
 * MetaDataReader
 */

/* Include --------------------------------------------- */
#include "MetaDataReader.hpp"
#include "MetaData.hpp"

#include "Base64Encoder.hpp"

#include <iostream>

#include <cstdio>
#include <cstring>
#include <cstdint>

/* Typedefs -------------------------------------------- */
typedef enum _metaDataCodes {
    MD_CODE_PERSISTENT_ID = 'mper',
    MD_CODE_URL = 'asul',
    MD_CODE_ALBUM_NAME = 'asal',
    MD_CODE_ARTIST = 'asar',
    MD_CODE_COMMENT = 'ascm',
    MD_CODE_GENRE = 'asgn',
    MD_CODE_TITLE = 'minm',
    MD_CODE_COMPOSER = 'ascp',
    MD_CODE_FILE_TYPE = 'asdt',
    MD_CODE_SORT_AS = 'assn',
    MD_CODE_PICTURE = 'PICT',
    MD_CODE_CLIENT_IP = 'clip'
} MetaDataCode_t;

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

                        std::cout << "[WARN ] The data is a picture, not decoding..." << std::endl;

                        /* Storing the picture data in the output string */
                        pDecodedData = lB64DataString;
                    }
                } else {
                    std::cout << "[ERROR] Failed to read the Base64 data !" << std::endl;
                    return false; /* Base64 data read failed ! */
                }

                /* Free the memory allocated for the char buffer */
                std::free((void *)lB64Data);
            } else {
                /* Memory allocation failed ! */
                std::cout << "[ERROR] Failed to allocate memory for the Base64 char buffer !" << std::endl;

                return false;
            }

            /* Get the end of data tag */
            if(!readEndTag()) {
                std::cout << "[ERROR] End of data tag not found !" << std::endl;

                /* TODO : Return ? */
            }

            if(!checkBase64EndSection()) {
                std::cout << "[ERROR] Unexpected characters at the end of a Base64 section." << std::endl;

                /* TODO : Return ? */
            }
        } else {
            /* No Base64 data */
            std::cout << "[ERROR] There is no Base64 data !" << std::endl;
            return false;
        }

        return true;
    }

    bool MetaDataReader::processTags(MetaData * const pMetaData, const std::string &pPayload) {
        switch(pMetaData->code()) {
            case MD_CODE_PERSISTENT_ID: 
                {
                    uint32_t v = ntohl(*(uint32_t *)pPayload.c_str());
                    pMetaData->setPersistentId(v);
                    printf("Persistent ID: \"%u\".\n", v);
                }
                break;
            case MD_CODE_URL:
                pMetaData->setURL(pPayload);
                printf("URL: \"%s\".\n", pPayload.c_str());
                break;
            case MD_CODE_ALBUM_NAME:
                pMetaData->setAlbumName(pPayload);
                printf("Album Name: \"%s\".\n", pPayload.c_str());
                break;
            case MD_CODE_ARTIST:
                pMetaData->setArtist(pPayload);
                printf("Artist: \"%s\".\n", pPayload.c_str());
                break;
            case MD_CODE_COMMENT:
                pMetaData->setComment(pPayload);
                printf("Comment: \"%s\".\n", pPayload.c_str());
                break;
            case MD_CODE_GENRE:
                pMetaData->setGenre(pPayload);
                printf("Genre: \"%s\".\n", pPayload.c_str());
                break;
            case MD_CODE_TITLE:
                pMetaData->setTitle(pPayload);
                printf("Title: \"%s\".\n", pPayload.c_str());
                break;
            case MD_CODE_COMPOSER:
                pMetaData->setComposer(pPayload);
                printf("Composer: \"%s\".\n", pPayload.c_str());
                break;
            case MD_CODE_FILE_TYPE:
                pMetaData->setFileType(pPayload);
                printf("File kind: \"%s\".\n", pPayload.c_str());
                break;
            case MD_CODE_SORT_AS:
                pMetaData->setSortAs(pPayload);
                printf("Sort as: \"%s\".\n", pPayload.c_str());
                break;
            case MD_CODE_PICTURE:
                /* TODO : What do we do here ? */
                printf("Picture received, length %u bytes.\n", pMetaData->length());
                break;
            case MD_CODE_CLIENT_IP:
                pMetaData->setClientIP(pPayload);
                printf("Client's IP: \"%s\".\n", pPayload.c_str());
                break;
            default:
                /* TODO : What do we do here ? */
                if (pMetaData->type() == 'ssnc') {
                    char typestring[5];
                    *(uint32_t *)typestring = htonl(pMetaData->type());
                    typestring[4]           = 0;
                    char codestring[5];
                    *(uint32_t *)codestring = htonl(pMetaData->code());
                    codestring[4]           = 0;
                    printf("\"%s\" \"%s\": \"%s\".\n", typestring, codestring, pPayload.c_str());
                } else {
                    /* TODO : What do we do here ? */
                    std::cout << "[DEBUG] Unknown metadata code : " << pMetaData->code() << std::endl;
                    return false; /* TODO : Is this the expected behaviour ? */
                }
        }

        return true;
    }

    bool MetaDataReader::readEndTag(void) const {
        char lEndTag[64];
        const int lRc = std::fscanf(mFile, "%64s", lEndTag);
        (void)lRc; /* Useless until proven otherwise */
        if("</data></item>" != std::string(lEndTag)) {
            /* End data tag not seen, \"%s\" seen instead.\n */
            std::printf("[ERROR] End data tag not seen, \"%s\" seen instead.\n", lEndTag);

            return false;
        }

        return true;
    }

    bool MetaDataReader::checkBase64EndSection(void) const {
        char lStr[1025];

        /** From @mikebrady's example : 
         * "Now, there will either be a line feed or nothing at the end of this line
         * it's not necessary XML, but it's what Shairport Sync puts out, 
         * and it makes life a bit easier. 
         * So, if there's something there and it's not just a linefeed, it's an error."
         */

        return !((std::fgets(lStr, 1024, mFile) != NULL) && ((std::strlen(lStr) != 1) || (lStr[0] != 0x0A)));
    }
}