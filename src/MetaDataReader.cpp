/**
 * MetaDataReader
 */

/* Include --------------------------------------------- */
#include "MetaDataReader.hpp"
#include "MetaData.hpp"

#include "Base64Encoder.hpp"
#include "LiteralConverter.hpp"

#include "RawJPEGFactory.hpp"
#include "RawJPEG.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cmath>

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

/* Variable declaration -------------------------------- */

/* Class implementation -------------------------------- */
namespace metadata {
    MetaDataReader::MetaDataReader(std::ifstream * const pStream) : 
        mFileStream(pStream), 
        mBase64Encoder(&tools::Base64Encoder::instance()),
        mJPEGFactory(new RawJPEGFactory)
    {
        /* Empty */
    }

    MetaDataReader::~MetaDataReader() {
        mFileStream = nullptr;

        if(mJPEGFactory != nullptr) {
            delete mJPEGFactory;
        }
        mJPEGFactory = nullptr;
    }

    /* Getters */
    std::ifstream *MetaDataReader::fileStream(void) const {
        return mFileStream;
    }

    /* Setters */
    void MetaDataReader::setFileStream(std::ifstream * const pStream) {
        mFileStream = pStream;
    }

    bool MetaDataReader::readHeader(MetaData * const pMetaData) {
        std::string lStr;

        /* Get the header */
        if(std::getline(*mFileStream, lStr)) {
            /* Decipher the header's contents */
            uint32_t lType = 0U, lCode = 0U, lLength = 0U;

            int lResult = std::sscanf(lStr.c_str(), "<item><type>%8x</type><code>%8x</code><length>%u</length>", &lType, &lCode, &lLength);
            if(3 == lResult) {
                /* We got all three values */

                /* TODO : Check data validity */

                pMetaData->setType(lType);
                pMetaData->setCode(lCode);
                pMetaData->setLength(lLength);

                return true;
            } else {
                /* Header data is not correct */
                return false;
            }
        } else {
            /* getline failed */
            return false;
        }
    }

    bool MetaDataReader::readBase64Data(const MetaData * const pMetaData, std::string &pDecodedData) {
        (void)pMetaData;
        
        /* Check if the data that follows is Base64 data */
        static const std::string lB64StartTag = "<data encoding=\"base64\">";
        static const std::string lB64EndTag   = "</data></item>";
        
        std::string lReadStr;

        if(std::getline(*mFileStream, lReadStr)) {
            if(lB64StartTag == lReadStr) {
                /* Base 64 data */

                /* Allocate memory for the Base64 data */
                // char *lB64Data = (char *)std::malloc(lB64Length + 1);
                std::string lB64Str, lB64FullStr;

                /* Read the Base64 data */
                /* This data is maybe segmented and thus need several reads */
                bool lReadSuccess = false;
                while ((lReadSuccess = std::getline(*mFileStream, lB64Str).good())) {
                    lB64FullStr += lB64Str;
                    if(lB64FullStr.length() >= lB64EndTag.length()) {
                        if(0 == lB64FullStr.compare(lB64FullStr.length() - lB64Str.length(), lB64FullStr.length(), lB64Str)) {
                            /* Got all the data */
                            break;
                        }
                    }
                }

                if(lReadSuccess) {
                    /* Decode the Base64 data */
                    pDecodedData = mBase64Encoder->decode(lB64FullStr);
                } else {
                    //std::cout << "[ERROR] Failed to read the Base64 data !" << std::endl;
                    return false;
                }

                // if(!checkBase64EndSection()) {
                //     std::cout << "[ERROR] Unexpected characters at the end of a Base64 section." << std::endl;

                //     /* TODO : Return ? */
                // }
            } else {
                /* No Base64 data */
                std::cout << "[ERROR] There is no Base64 data !" << std::endl;
                std::cout << "        Instead, read : " << lReadStr << std::endl;
                return false;
            }
        } else {
            /* TODO : Read went wrong */
        }

        return true;
    }

    bool MetaDataReader::processTags(MetaData * const pMetaData, const std::string &pPayload) {
        static bool sImageReadInProgress = false;
        std::string lImageFactoryResult;

        /** From @mikebrady's example : 
         * "this has more information about tags, which might be relevant:
         * https://code.google.com/p/ytrack/wiki/DMAP"
         */
        switch(pMetaData->code()) {
            case MD_CODE_PERSISTENT_ID: 
                {
                    uint32_t lPersistentID = ntohl(*(uint32_t *)pPayload.c_str());
                    pMetaData->setPersistentID(lPersistentID);
                    //std::cout << "[INFO ] Persistent ID: \"" << lPersistentID << "\"" << std::endl;
                }
                break;
            case MD_CODE_URL:
                pMetaData->setURL(pPayload);
                //std::cout << "[INFO ] URL: \"" << pPayload << "\"" << std::endl;
                break;
            case MD_CODE_ALBUM_NAME:
                pMetaData->setAlbumName(pPayload);
                //std::cout << "[INFO ] Album Name: \"" << pPayload << "\"" << std::endl;
                break;
            case MD_CODE_ARTIST:
                pMetaData->setArtist(pPayload);
                //std::cout << "[INFO ] Artist: \"" << pPayload << "\"" << std::endl;
                break;
            case MD_CODE_COMMENT:
                pMetaData->setComment(pPayload);
                //std::cout << "[INFO ] Comment: \"" << pPayload << "\"" << std::endl;
                break;
            case MD_CODE_GENRE:
                pMetaData->setGenre(pPayload);
                //std::cout << "[INFO ] Genre: \"" << pPayload << "\"" << std::endl;
                break;
            case MD_CODE_TITLE:
                pMetaData->setTitle(pPayload);
                //std::cout << "[INFO ] Title: \"" << pPayload << "\"" << std::endl;
                break;
            case MD_CODE_COMPOSER:
                pMetaData->setComposer(pPayload);
                //std::cout << "[INFO ] Composer: \"" << pPayload << "\"" << std::endl;
                break;
            case MD_CODE_FILE_TYPE:
                pMetaData->setFileType(pPayload);
                //std::cout << "[INFO ] File kind: \"" << pPayload << "\"" << std::endl;
                break;
            case MD_CODE_SORT_AS:
                pMetaData->setSortAs(pPayload);
                //std::cout << "[INFO ] Sort as: \"" << pPayload << "\"" << std::endl;
                break;
            case MD_CODE_PICTURE:
                if( ((char)0xFF == (char)pPayload[0]) && ((char)0xD8 == (char)pPayload[1]) ) {
                    std::cout << "[INFO ] New picture received, is a JPEG" << std::endl;

                    /* Checking if a read was in progress */
                    if(sImageReadInProgress) {
                        /* A JPEG is still being read. 
                         * Discarding the previous data */
                        std::cout << "[WARN ] A JPEG was being read, but a new one arrived. Discarding previous data..." << std::endl;
                        mJPEGFactory->clear();
                        sImageReadInProgress = false;
                    }

                    /* Giving the segment of data to the JPEG factory */
                    lImageFactoryResult = mJPEGFactory->append(pPayload);

                    /* Check if the image is complete */
                    if(!lImageFactoryResult.empty()) {
                        /* Data read is no longer in progress */
                        sImageReadInProgress = false;
                        mJPEGFactory->clear();
                    }
                } else if("\211PNG\r\n\032\n" == pPayload.substr(0UL, 8U)) {
                    std::cout << "[INFO ] Picture received, is a PNG " << std::endl;
                }
                //std::cout << "[DEBUG] pPayload[0] = " << std::hex << (int)pPayload[0] << ", pPayload[1] = " << (int)pPayload[1] << std::dec << std::endl;
                //std::cout << "[DEBUG] pPayload.substr(0UL, 8U) = " << pPayload.substr(0UL, 8U) << std::endl;
                std::cout << "[INFO ] Picture received, length " << pMetaData->length() << " bytes." << std::endl;
                // std::cout << "[DEBUG] PICT data dump :" << std::endl << pPayload << std::endl;

                /* Check if the image is complete, write it for debug */
                if(!lImageFactoryResult.empty()) {
                    FILE *lImageFile = fopen("/tmp/shairport-artwork.jpg", "w+");
                    fwrite(pPayload.c_str(), pMetaData->length(), 1, lImageFile);
                }
                break;
            case MD_CODE_CLIENT_IP:
                pMetaData->setClientIP(pPayload);
                //std::cout << "[INFO ] Client's IP: \"" << pPayload << "\"" << std::endl;
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
                    /** There are still lots of code that are not yet supported. */
                    //std::cout << "[DEBUG] Unknown metadata code : " << pMetaData->code() << " (" << tools::LiteralConverter::multiCharLiteralToString(pMetaData->code()) << ")" << std::endl;
                    return false; /* TODO : Is this the expected behaviour ? */
                }
        }

        return true;
    }

    bool MetaDataReader::checkBase64EndSection(void) const {
        char lStr[1024];

        /** From @mikebrady's example : 
         * "Now, there will either be a line feed or nothing at the end of this line
         * it's not necessarily XML, but it's what Shairport Sync puts out, 
         * and it makes life a bit easier. 
         * So, if there's something there and it's not just a linefeed, it's an error."
         */

        /* TODO : Magic numbers */

        return !((mFileStream->get(lStr, 1024)) && ((std::strlen(lStr) != 1) || (lStr[0] != 0x0A)));
    }
}