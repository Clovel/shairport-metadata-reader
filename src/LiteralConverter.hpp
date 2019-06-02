/**
 * LiteralConverter
 */

#ifndef TOOLS_LITERALCONVERTER_HPP
#define TOOLS_LITERALCONVERTER_HPP

/* Include --------------------------------------------- */
#include <string>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
namespace tools {
    class LiteralConverter {
        public:
            static std::string multiCharLiteralToString(const int &pLiteral);
            static int stringToMultiCharLiteral(const std::string &pString);
    };
}

#endif /* TOOLS_LITERALCONVERTER_HPP */
