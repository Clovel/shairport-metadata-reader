/**
 * MetaDataReader
 */

#ifndef METADATA_HPP
#define METADATA_HPP

/* Include --------------------------------------------- */
#include <string>

#include <cstdint>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
namespace metadata {
    class MetaData {
        public:
            MetaData();
            virtual ~MetaData();

            /* Getters */
            uint32_t type(void) const;
            uint32_t code(void) const;
            uint32_t length(void) const;

            /* Setters */
            void setType(const uint32_t &pType);
            void setCode(const uint32_t &pCode);
            void setLength(const uint32_t &pLength);
        private:
            uint32_t mType;
            uint32_t mCode;
            uint32_t mLength;
    };
}

#endif /* METADATA_HPP */
