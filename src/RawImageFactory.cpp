/**
 * RawImageFactory
 */

/* Include --------------------------------------------- */
#include "RawImageFactory.hpp"

#include <iostream>

/* Defines --------------------------------------------- */

/* Support functions ----------------------------------- */

/* Class implentation ---------------------------------- */
void RawImageFactory::clear(void) {
    mRawData.clear();
    mIsComplete = false;
}

