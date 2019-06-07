/**
 * RawJPEG
 */

#ifndef RAW_JPEG_FACTORY_HPP
#define RAW_JPEG_FACTORY_HPP

/* Include --------------------------------------------- */
#include "RawImageFactory.hpp"

#include <string>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
class RawJPEGFactory : public RawImageFactory {
    public:
        RawJPEGFactory();
        virtual ~RawJPEGFactory();

        std::string append(const std::string pStr);
};

#endif /* RAW_JPEG_FACTORY_HPP */
