/**
 * RawJPEG
 */

/* Include --------------------------------------------- */
#include "RawJPEGFactory.hpp"
#include "RawImageFactory.hpp"

#include <iostream>

/* Defines --------------------------------------------- */

/* Support functions ----------------------------------- */
static bool checkJPEGEnding(const std::string &pStr) {
    return ((char)0xFF == (char)pStr.at(pStr.length() - 2)) && ((char)0xD9 == (char)pStr.at(pStr.length() - 1));
}

/* Class implentation ---------------------------------- */
RawJPEGFactory::RawJPEGFactory() {
    /* Empty on purpose */
}

RawJPEGFactory::~RawJPEGFactory() {
    /* Empty on purpose */
}

std::string RawJPEGFactory::append(const std::string pStr) {
    if(mIsComplete) {
        /* If the file is already complete, clear data before appending to the buffer */
        clear();
    }

    mRawData.append(pStr);

    mIsComplete = checkJPEGEnding(mRawData);

    return mIsComplete ? mRawData : std::string();
}

