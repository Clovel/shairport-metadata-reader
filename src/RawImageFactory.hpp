/**
 * RawImageFactory
 */

#ifndef RAW_IMAGE_FACTORY_HPP
#define RAW_IMAGE_FACTORY_HPP

/* Include --------------------------------------------- */
#include <string>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
class RawImageFactory {
    public:
        virtual void clear(void);
        virtual std::string append(const std::string pStr) = 0;

    protected:
        std::string mRawData;
        bool mIsComplete;
};

#endif /* RAW_IMAGE_FACTORY_HPP */
