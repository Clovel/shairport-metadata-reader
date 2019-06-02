/**
 * Main source file
 */

/* Includes -------------------------------------------- */
#include "Base64Encoder.hpp"
#include "NamedPipe.hpp"
#include "MetaDataReader.hpp"
#include "MetaData.hpp"

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

    NamedPipe lPipe(lFilePath);
    int lOpened = lPipe.openPipe();
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
    metadata::MetaDataReader lMetaDataReader(lPipe.file());

    /* Initializing OpenCV for Artwork */
    cv::Mat matrixJprg;
    cv::namedWindow("Artwork");
    bool lArtworkFound = false;

    std::cout << "[INFO ] Starting main loop... " << std::endl;
    for(;;) {
        if(lMetaDataReader.readHeader(&lMetaData)) {
            /* Got header */

            std::string lDecodedB64Data;
            if(lMetaDataReader.readBase64Data(&lMetaData, lDecodedB64Data)) {
                /* Got Base64 data */ 
            } else {
                std::cout << "[ERROR] Failed to read Base64Data !" << std::endl;
            }

            /* Processing all tags */
            if(lMetaDataReader.processTags(&lMetaData, lDecodedB64Data)) {
                /*  */
            } else {
                std::cout << "[WARN ] Unexpected behaviour when processing tags !" << std::endl;
            }
        } else {
            std::cout << "[ERROR] Could not read metadata header from pipe !" << std::endl;
        }
    }

    std::cout << "[EXIT ] Stopping program..." << std::endl;

    return EXIT_SUCCESS;
}