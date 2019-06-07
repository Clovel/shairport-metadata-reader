/**
 * RawJPG
 */

/* Include --------------------------------------------- */
#include "RawJPG.hpp"

#include <iostream>

/* Defines --------------------------------------------- */

/* Class implentation ---------------------------------- */
std::ostream &operator<<(std::ostream &pOs, const RawJPG &pRawJPG) {
    pOs << "RawJPG data : " << pRawJPG.rawData();
    
    return pOs;
}

RawJPG::RawJPG() {
    /* Empty on purpose */
}

RawJPG::RawJPG(const std::string &pStr) : mRawData(pStr)
{
    /* Empty on purpose */
}

RawJPG::~RawJPG() {
    /* Empty on purpose */
}

void RawJPG::print(void) const {
    std::cout << "[INFO ] RawJPG value is : " << *this << std::endl;
}

/* Getters */
std::string RawJPG::rawData(void) const {
    return mRawData;
}

bool RawJPG::isComplete(void) const {
    return mComplete;
}

/* Setters */
void RawJPG::setRawData(const std::string &pStr) {
    mRawData = pStr;
}

void RawJPG::setCompleted(const bool &pComplete) {
    mComplete = pComplete;
}
