/**
 * RawJPEG
 */

/* Include --------------------------------------------- */
#include "RawJPEG.hpp"

#include <iostream>

/* Defines --------------------------------------------- */

/* Class implentation ---------------------------------- */
std::ostream &operator<<(std::ostream &pOs, const RawJPEG &pRawJPEG) {
    pOs << "RawJPEG data : " << pRawJPEG.rawData();
    
    return pOs;
}

RawJPEG::RawJPEG() {
    /* Empty on purpose */
}

RawJPEG::RawJPEG(const std::string &pStr) : mRawData(pStr)
{
    /* Empty on purpose */
}

RawJPEG::~RawJPEG() {
    /* Empty on purpose */
}

void RawJPEG::print(void) const {
    std::cout << "[INFO ] RawJPEG value is : " << *this << std::endl;
}

/* Getters */
std::string RawJPEG::rawData(void) const {
    return mRawData;
}

bool RawJPEG::isComplete(void) const {
    return mComplete;
}

/* Setters */
void RawJPEG::setRawData(const std::string &pStr) {
    mRawData = pStr;
}

void RawJPEG::setCompleted(const bool &pComplete) {
    mComplete = pComplete;
}
