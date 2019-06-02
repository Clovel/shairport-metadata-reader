/**
 * Base64Encoder
 */

/* Include --------------------------------------------- */
#include "LiteralConverter.hpp"

#include <string>
#include <sstream>
#include <iostream>

/* Defines --------------------------------------------- */
#define LITERAL_MASK 0xFF

/* Variable declarations ------------------------------- */

/* Class implementation -------------------------------- */
namespace tools {
    std::string LiteralConverter::multiCharLiteralToString(const int &pLiteral) {
        /* TODO : Find less heavy implementation */

        std::stringstream lSStream;
        lSStream << std::hex << pLiteral;
        std::string lHex = lSStream.str();
        size_t lHexSize = lHex.length();

        std::string lOutput;
        
        for(unsigned int i = 0U; lHexSize > i; i += 2) {
            std::string lByte = lHex.substr(i, 2U);
            const char c = (char)(int)std::strtol(lByte.c_str(), NULL, 16);

            lOutput.push_back(c);
        }

        return lOutput;
    }

    int LiteralConverter::stringToMultiCharLiteral(const std::string &pString) {
        /* TODO */
        std::string lStr(pString);
        unsigned int i = 0U;
        int lLiteral = 0;
        const int toto = 'c\0';
        (void)toto;

        while(0U < lStr.length()) {
            char c = lStr[lStr.length() - 1];
            lStr.pop_back();
            std::cout << "[DEBUG] c = " << (char)c << ", lStr.length() = " << lStr.length() << std::endl;
            lLiteral += c << 8*i++;
            std::cout << "[DEBUG] lLiteral = " << lLiteral << std::endl;
        }

        return lLiteral;
    }
}