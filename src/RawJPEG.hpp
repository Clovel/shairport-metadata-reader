/**
 * RawJPEG
 */

#ifndef RAW_JPEG_HPP
#define RAW_JPEG_HPP

/* Include --------------------------------------------- */
#include <string>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
class RawJPEG {
    public:
        RawJPEG();
        RawJPEG(const std::string &pStr);
        virtual ~RawJPEG();

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

std::ostream &operator<<(std::ostream &pOs, const RawJPEG &pRawJPEG);

#endif /* RAW_JPEG_HPP */
