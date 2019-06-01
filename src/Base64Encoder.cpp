/**
 * Base64Encoder
 */

/* Include --------------------------------------------- */
#include "Base64Encoder.hpp"

#include <cstring>
#include <cstdint>

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */
const std::string tools::Base64Encoder::sEncodingTable = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";
const int tools::Base64Encoder::sModTable[3] = { 0, 2, 1 };

/* Class implementation -------------------------------- */
namespace tools {
    Base64Encoder::Base64Encoder() {
        /* Empty */
    }

    Base64Encoder::~Base64Encoder() {
        /* Empty */
    }

    Base64Encoder &Base64Encoder::instance(void) {
        static Base64Encoder sEncoder;

        return sEncoder;
    }

    inline bool Base64Encoder::isBase64(unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }

    std::string Base64Encoder::encode(const unsigned char * pData, unsigned int &pInputLength) const {
        std::string lReturn;
        int i = 0, j = 0;

        unsigned char pCharArray3[3];
        unsigned char pCharArray4[4];

        while (pInputLength--) {
            pCharArray3[i++] = *(pData++);

            if (i == 3) {
                pCharArray4[0] = (pCharArray3[0] & 0xfc) >> 2;
                pCharArray4[1] = ((pCharArray3[0] & 0x03) << 4) + ((pCharArray3[1] & 0xf0) >> 4);
                pCharArray4[2] = ((pCharArray3[1] & 0x0f) << 2) + ((pCharArray3[2] & 0xc0) >> 6);
                pCharArray4[3] = pCharArray3[2] & 0x3f;

                for(i = 0; (i < 4) ; i++)
                    lReturn += sEncodingTable[pCharArray4[i]];

                i = 0;
            }
        }

        if (i) {
            for(j = i; j < 3; j++)
                pCharArray3[j] = '\0';

            pCharArray4[0] = (pCharArray3[0] & 0xfc) >> 2;
            pCharArray4[1] = ((pCharArray3[0] & 0x03) << 4) + ((pCharArray3[1] & 0xf0) >> 4);
            pCharArray4[2] = ((pCharArray3[1] & 0x0f) << 2) + ((pCharArray3[2] & 0xc0) >> 6);
            pCharArray4[3] = pCharArray3[2] & 0x3f;

            for (j = 0; (j < i + 1); j++)
                lReturn += sEncodingTable[pCharArray4[j]];

            while((i++ < 3))
                lReturn += '=';

        }

        return lReturn;
    }

    std::string Base64Encoder::decode(std::string const& encoded_string) const {
        int lInLength = encoded_string.size();
        int i = 0;
        int j = 0;
        int lIn = 0;
        unsigned char pCharArray4[4], pCharArray3[3];
        std::string lReturn;

        while (lInLength-- && ( encoded_string[lIn] != '=') && isBase64(encoded_string[lIn])) {
            pCharArray4[i++] = encoded_string[lIn]; lIn++;
            if (i ==4) {
                for (i = 0; i <4; i++)
                    pCharArray4[i] = sEncodingTable.find(pCharArray4[i]);

                pCharArray3[0] = (pCharArray4[0] << 2) + ((pCharArray4[1] & 0x30) >> 4);
                pCharArray3[1] = ((pCharArray4[1] & 0xf) << 4) + ((pCharArray4[2] & 0x3c) >> 2);
                pCharArray3[2] = ((pCharArray4[2] & 0x3) << 6) + pCharArray4[3];

                for (i = 0; (i < 3); i++)
                    lReturn += pCharArray3[i];
                    
                i = 0;
            }
        }

        if (i) {
            for (j = i; j <4; j++)
                pCharArray4[j] = 0;

            for (j = 0; j <4; j++)
                pCharArray4[j] = sEncodingTable.find(pCharArray4[j]);

            pCharArray3[0] = (pCharArray4[0] << 2) + ((pCharArray4[1] & 0x30) >> 4);
            pCharArray3[1] = ((pCharArray4[1] & 0xf) << 4) + ((pCharArray4[2] & 0x3c) >> 2);
            pCharArray3[2] = ((pCharArray4[2] & 0x3) << 6) + pCharArray4[3];

            for (j = 0; (j < i - 1); j++) lReturn += pCharArray3[j];
        }

        return lReturn;
    }
}