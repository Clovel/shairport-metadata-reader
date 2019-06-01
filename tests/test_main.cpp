/* Includes -------------------------------------------- */
#include "Base64Encoder.hpp"

/* C++ system */
#include <iostream>
#include <string>

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

    return 0;
}

int test_base64_decode_encode(void) {
    const std::string lStr = "UGFjayBteSBib3ggd2l0aCBmaXZlIGRvemVuIGxpcXVvciBqdWdz"; // "Pack my box with five dozen liquor jugs", encoded w/ https://www.base64encode.org

    tools::Base64Encoder lEncoder = tools::Base64Encoder::instance();

    std::string lDecodedStr = lEncoder.decode(lStr);
    std::cout << "[INFO ] Decoded string is " << lDecodedStr << std::endl;

    std::string lEncodedStr = lEncoder.encode(reinterpret_cast<const unsigned char *>(lDecodedStr.c_str()), lDecodedStr.length());
    std::cout << "[INFO ] Encoded string is " << lEncodedStr << std::endl;

    assert(lStr == lEncodedStr);

    return 0;
}

int test_base64_decode(void) {
    const std::string lStr = "UGFjayBteSBib3ggd2l0aCBmaXZlIGRvemVuIGxpcXVvciBqdWdz"; // "Pack my box with five dozen liquor jugs", encoded w/ https://www.base64encode.org
    const std::string lExpectedStr = "Pack my box with five dozen liquor jugs";

    tools::Base64Encoder lEncoder = tools::Base64Encoder::instance();

    std::string lDecodedStr = lEncoder.decode(lStr);
    std::cout << "[INFO ] Decoded string is " << lDecodedStr << std::endl;

    assert(lExpectedStr == lDecodedStr);

    return 0;
}

int test_base64_encode(void) {
    const std::string lStr = "Pack my box with five dozen liquor jugs";
    const std::string lExpectedStr = "UGFjayBteSBib3ggd2l0aCBmaXZlIGRvemVuIGxpcXVvciBqdWdz"; // "Pack my box with five dozen liquor jugs", encoded w/ https://www.base64encode.org

    tools::Base64Encoder lEncoder = tools::Base64Encoder::instance();

    std::string lEncodedStr = lEncoder.encode(reinterpret_cast<const unsigned char *>(lStr.c_str()), lStr.length());
    std::cout << "[INFO ] Decoded string is " << lEncodedStr << std::endl;

    assert(lExpectedStr == lEncodedStr);

    return 0;
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
        default:
            fprintf(stdout, "[INFO ] test #%d not available\n", test_num);
            fflush(stdout);
            break;
    }

    return result;
}