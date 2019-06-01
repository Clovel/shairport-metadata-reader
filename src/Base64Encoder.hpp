/**
 * Base64Encoder
 */

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
        
            std::string encode(unsigned char const* pData, unsigned int &pInputLength) const;
            std::string decode(std::string const& encoded_string) const;

        private:
            Base64Encoder();

            static const std::string sEncodingTable;
            static const int sModTable[3];

            char mEncodingTable[64];
            int mDecodingTable[256]; /* TODO : Magic number, Why 256 ? */
    };
}