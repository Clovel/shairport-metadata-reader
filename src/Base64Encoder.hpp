/**
 * Base64Encoder
 */

#ifndef TOOLS_BASE64ENCODER_HPP
#define TOOLS_BASE64ENCODER_HPP

/* Include --------------------------------------------- */
#include <string>

#include <cstddef>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
namespace tools {
    class Base64Encoder {
        public:
            virtual ~Base64Encoder();

            static Base64Encoder &instance(void);

            /* Getters */
            static inline bool isBase64(unsigned char c);

            /* Setters */

            /* Encode/Decode */
        
            std::string encode(const unsigned char * pData, const unsigned int &pInputLength) const;
            std::string encode(const std::string &pStr) const;
            std::string decode(std::string const& encoded_string) const;

        private:
            Base64Encoder();

            static const std::string sEncodingTable;
            static const int sModTable[3];
    };
}

#endif /* TOOLS_BASE64ENCODER_HPP */
