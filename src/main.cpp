/**
 * Main source file
 */

/* Includes -------------------------------------------- */
#include "MetaDataReader.hpp"
#include "MetaData.hpp"

#include "Base64Encoder.hpp"
#include "NamedPipe.hpp"
#include "LiteralConverter.hpp"

#include <opencv2/opencv.hpp>

#include <fstream>
#include <iostream>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <unistd.h>
#include <arpa/inet.h>

/* Defines --------------------------------------------- */

/* Variable declarions --------------------------------- */

/* Extern variables ------------------------------------ */

/* Main function */
int main(const int argc, const char * const * const argv) {

    (void)argc;
    (void)argv;

    /* Opening NamedPipe */
    std::string lFilePath("/tmp/shairport-sync-metadata");
    std::ifstream lFileStream;
    lFileStream.open(lFilePath, std::ios_base::binary | std::ios_base::in);

    int lOpened = lFileStream.is_open();
    if(0 > lOpened) {
        std::cout << "[ERROR] Could not open file \"" << lFilePath << "\" (returned " << lOpened << ")" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "[INFO ] Opened file \"" << lFilePath << "\" ! " << std::endl;
    }

    /* Initializing the decoding table */
    tools::Base64Encoder lEncoder = tools::Base64Encoder::instance();

    /* Allocating a MetaData object */
    metadata::MetaData lMetaData;

    /* Initializing MetaDataReader */
    metadata::MetaDataReader lMetaDataReader(&lFileStream);

    /* Initializing OpenCV for Artwork */
    bool lBase64ReadSuccess = false;

    std::cout << "[INFO ] Starting main loop... " << std::endl;
    for(;;) {
        if(lMetaDataReader.readHeader(&lMetaData)) {
            /* Got header */

            std::cout << "[DEBUG] code : " << tools::LiteralConverter::multiCharLiteralToString(lMetaData.code()) << ", type : " << tools::LiteralConverter::multiCharLiteralToString(lMetaData.type()) << ", length : " << lMetaData.length() << std::endl;

            std::string lDecodedB64Data;
            lBase64ReadSuccess = lMetaDataReader.readBase64Data(&lMetaData, lDecodedB64Data);
            (void)lBase64ReadSuccess;
            // if(lBase64ReadSuccess) {
            //     /* Got Base64 data */
            //     std::cout << "[DEBUG] Decoded data : " << lDecodedB64Data << std::endl;
            // } else {
            //     std::cout << "[ERROR] Failed to read Base64Data !" << std::endl;
            // }

            /* Processing all tags */
            if(lMetaDataReader.processTags(&lMetaData, lDecodedB64Data)) {
                /* Print the metadata */
                //std::cout << std::endl << "[DEBUG] MetaData is : " << lMetaData << std::endl << std::endl;
            } 
            // else {
            //     std::cout << "[WARN ] Unexpected behaviour when processing tags !" << std::endl;
            // }
        } else {
            // std::cout << "[ERROR] Could not read metadata header from pipe !" << std::endl;
        }
    }

    std::cout << "[EXIT ] Stopping program..." << std::endl;

    return EXIT_SUCCESS;
}