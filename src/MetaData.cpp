/**
 * MetaData
 */

/* Include --------------------------------------------- */
#include "MetaData.hpp"

/* Defines --------------------------------------------- */

/* Class implentation ---------------------------------- */
namespace metadata {
    MetaData::MetaData() {
        /* Empty */
    }

    MetaData::~MetaData() {
        /* Empty */
    }

    /* Getters */
    uint32_t MetaData::type(void) const {
        return mType;
    }

    uint32_t MetaData::code(void) const {
        return mCode;
    }

    uint32_t MetaData::length(void) const {
        return mLength;
    }

    /* Setters */
    void MetaData::setType(const uint32_t &pType) {
        mType = pType;
    }
    void MetaData::setCode(const uint32_t &pCode) {
        mCode = pCode;
    }
    void MetaData::setLength(const uint32_t &pLength) {
        mLength = pLength;
    }
}