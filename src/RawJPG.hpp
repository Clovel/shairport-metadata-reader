/**
 * RawJPG
 */

#ifndef RAW_JPG_HPP
#define RAW_JPG_HPP

/* Include --------------------------------------------- */
#include <string>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
class RawJPG {
    public:
        RawJPG();
        RawJPG(const std::string &pStr);
        virtual ~RawJPG();

        void print(void) const;

        /* Getters */
        std::string rawData(void) const;
        bool isComplete(void) const;

        /* Setters */
        void setRawData(const std::string &pStr);
        void setCompleted(const bool &pStr);

    private:
        std::string mRawData;
        bool mComplete;
};

std::ostream &operator<<(std::ostream &pOs, const RawJPG &pRawJPG);

#endif /* RAW_JPG_HPP */
