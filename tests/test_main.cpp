/* Includes -------------------------------------------- */
#include "Base64Encoder.hpp"
#include "LiteralConverter.hpp"

#include "RawJPEGFactory.hpp"

/* C++ system */
#include <iostream>
#include <fstream>
#include <string>
#include <exception>

/* C system */
#include <cstring>
#include <cassert>

/* Defines --------------------------------------------- */

/* Variable declaration -------------------------------- */

/* Support functions ----------------------------------- */
void print_usage(void) {
    /* TODO */
}

/* Test functions -------------------------------------- */
int test_base64_encode_decode(void) {
    const std::string lStr = "Pack my box with five dozen liquor jugs"; // According to Wikipedia, this one is used on NASA’s Space Shuttle. (32 letters)

    tools::Base64Encoder lEncoder = tools::Base64Encoder::instance();

    std::string lEncodedStr = lEncoder.encode(reinterpret_cast<const unsigned char *>(lStr.c_str()), lStr.length());
    std::cout << "[INFO ] Encoded string is " << lEncodedStr << std::endl;

    std::string lDecodedStr = lEncoder.decode(lEncodedStr);
    std::cout << "[INFO ] Decoded string is " << lDecodedStr << std::endl;

    assert(lStr == lDecodedStr);

    return EXIT_SUCCESS;
}

int test_base64_decode_encode(void) {
    const std::string lStr = "UGFjayBteSBib3ggd2l0aCBmaXZlIGRvemVuIGxpcXVvciBqdWdz"; // "Pack my box with five dozen liquor jugs", encoded w/ https://www.base64encode.org

    tools::Base64Encoder lEncoder = tools::Base64Encoder::instance();

    std::string lDecodedStr = lEncoder.decode(lStr);
    std::cout << "[INFO ] Decoded string is " << lDecodedStr << std::endl;

    std::string lEncodedStr = lEncoder.encode(reinterpret_cast<const unsigned char *>(lDecodedStr.c_str()), lDecodedStr.length());
    std::cout << "[INFO ] Encoded string is " << lEncodedStr << std::endl;

    assert(lStr == lEncodedStr);

    return EXIT_SUCCESS;
}

int test_base64_decode(void) {
    const std::string lStr = "UGFjayBteSBib3ggd2l0aCBmaXZlIGRvemVuIGxpcXVvciBqdWdz"; // "Pack my box with five dozen liquor jugs", encoded w/ https://www.base64encode.org
    const std::string lExpectedStr = "Pack my box with five dozen liquor jugs";

    tools::Base64Encoder lEncoder = tools::Base64Encoder::instance();

    std::string lDecodedStr = lEncoder.decode(lStr);
    std::cout << "[INFO ] Decoded string is " << lDecodedStr << std::endl;

    assert(lExpectedStr == lDecodedStr);

    return EXIT_SUCCESS;
}

int test_base64_encode(void) {
    const std::string lStr = "Pack my box with five dozen liquor jugs";
    const std::string lExpectedStr = "UGFjayBteSBib3ggd2l0aCBmaXZlIGRvemVuIGxpcXVvciBqdWdz"; // "Pack my box with five dozen liquor jugs", encoded w/ https://www.base64encode.org

    tools::Base64Encoder lEncoder = tools::Base64Encoder::instance();

    std::string lEncodedStr = lEncoder.encode(reinterpret_cast<const unsigned char *>(lStr.c_str()), lStr.length());
    std::cout << "[INFO ] Encoded string is " << lEncodedStr << std::endl;

    assert(lExpectedStr == lEncodedStr);

    lEncodedStr = lEncoder.encode(lStr);
    std::cout << "[INFO ] Encoded string is " << lEncodedStr << std::endl;

    assert(lExpectedStr == lEncodedStr);

    return EXIT_SUCCESS;
}

int test_literal_to_string(void) {
    const int lLiteral = 'abcd';
    const std::string lExpectedStr = "abcd";

    std::string lResult = tools::LiteralConverter::multiCharLiteralToString(lLiteral);

    assert(lExpectedStr == lResult);

    return EXIT_SUCCESS;
}

int test_string_to_literal(void) {
    const std::string lString = "abcd";
    const int lExpectedLiteral = 'abcd';

    int lResult = tools::LiteralConverter::stringToMultiCharLiteral(lString);

    assert(lExpectedLiteral == lResult);

    return 0;
}

int test_raw_jpeg_factory(void) {
    std::ifstream lInputFileStream;
    lInputFileStream.open("../../ressources/lena30.jpg", std::ios_base::in | std::ios_base::binary | std::ios_base::ate);
    if(lInputFileStream.fail() || !lInputFileStream.is_open()) {
        std::cout << "[ERROR] Failed to open ../../ressources/lena30.jpg" << std::endl;
        return EXIT_FAILURE;
    }

    std::string lRawJPEG;
    size_t lStrRawLength = lInputFileStream.tellg();
    std::cout << "[INFO ] lStrRawLength = " << lStrRawLength << std::endl;

    /* Allocating memory for the string in advance */
    try {
        lRawJPEG.reserve(lStrRawLength);
        } catch (const std::exception &e) {
        std::cout << "[ERROR] Excpetion \"" << e.what() << "\" occured during allocation !" << std::endl;
        return EXIT_FAILURE;
    }
    try {
        lInputFileStream.seekg(0, std::ios::beg);
    } catch (const std::bad_alloc &e) {
        std::cout << "[ERROR] Excpetion \"" << e.what() << "\" occured during seekg back to BOF !" << std::endl;
        return EXIT_FAILURE;
    }

    /* Getting the string */
    try {
        lRawJPEG.assign((std::istreambuf_iterator<char>(lInputFileStream)),
                std::istreambuf_iterator<char>());
    } catch (const std::exception &e) {
        std::cout << "[ERROR] Excpetion \"" << e.what() << "\" occured during data read !" << std::endl;
        return EXIT_FAILURE;
    }
    
    //std::cout << "[DEBUG] Raw contents are : " << lRawJPEG << std::endl;

    /* Instanciate a RawJPEGFactory */
    RawJPEGFactory lFactory;

    /* Segmenting the string */
    size_t lSegmentSize = lStrRawLength/100;
    size_t lLeftSize = lStrRawLength % 100;
    std::cout << "[DEBUG] lSegmentSize = " << lSegmentSize << ", lSegmentSize*100 = " << lSegmentSize*100 << ", left = " << lLeftSize << std::endl;

    /* Getting segments and appending them to the Facotry string */
    std::string lTmpStr, lAppendResult;
    for(unsigned int i = 0U; 100 > i; ++i) {
        lTmpStr = lRawJPEG.substr(i*lSegmentSize, lSegmentSize);
        lAppendResult = lFactory.append(lTmpStr);
        assert(std::string() == lAppendResult);
    }
    lTmpStr = lRawJPEG.substr(lStrRawLength - lLeftSize, lSegmentSize);
    lAppendResult = lFactory.append(lTmpStr);
    
    /* Check if the Factory returned the raw string */
    assert(std::string() != lAppendResult);

    /* Check if the Factory's result is equal to the original raw data */
    assert(lRawJPEG == lAppendResult);

    return EXIT_SUCCESS;
}


/* ----------------------------------------------------- */
/* main function --------------------------------------- */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv)
{
    /* Test function initialization */
    int test_num;
    int result = 0;

    if ((argc < 2) || (strcmp(argv[1], "--help") == 0)) {
        print_usage();
        return -1;
    }

    test_num = strtol(argv[1], NULL, 10);

    fprintf(stdout, "[INFO ] Executing test #%d\n", test_num);
    fflush(stdout);

    /* Main loop */
    switch (test_num) {
        case 0:
            result = test_base64_encode_decode();
            break;
        case 1:
            result = test_base64_decode_encode();
            break;
        case 2:
            result = test_base64_decode();
            break;
        case 3:
            result = test_base64_encode();
            break;
        case 4:
            result = test_literal_to_string();
            break;
        case 5:
            result = test_string_to_literal();
            break;
        case 6:
            result = test_raw_jpeg_factory();
            break;
        default:
            fprintf(stdout, "[INFO ] test #%d not available\n", test_num);
            fflush(stdout);
            break;
    }

    return result;
}