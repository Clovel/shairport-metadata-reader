/**
 * MetaData
 */

/* Include --------------------------------------------- */
#include "MetaData.hpp"

#include <iostream>

/* Defines --------------------------------------------- */

/* Class implentation ---------------------------------- */

std::ostream &operator<<(std::ostream &pOs, const metadata::MetaData &pMetaData) {
    pOs << "Code : " << (unsigned int)pMetaData.code() << ", "
        << "Type : " << (unsigned int)pMetaData.type() << ", "
        << "Length : " << (unsigned int)pMetaData.length() << ", "
        << "Title : " << pMetaData.title() << ", "
        << "Album Name : " << pMetaData.albumName() << ", "
        << "Artist : " << pMetaData.artist() << ", "
        << "Genre : " << pMetaData.genre() << ", "
        << "Composer : " << pMetaData.composer() << ", "
        << "Comment : " << pMetaData.comment() << ", "
        << "Sort As : " << pMetaData.sortAs() << ", "
        << "URL : " << pMetaData.URL() << ", "
        << "Client IP : " << pMetaData.clientIP() << ", "
        << "Persistent ID : " << (unsigned int)pMetaData.persistentID() << ", "
        << "File Type : " << pMetaData.fileType();
    
    return pOs;
}

namespace metadata {
    MetaData::MetaData() {
        /* Empty */
    }

    MetaData::~MetaData() {
        /* Empty */
    }

    void MetaData::print(void) const {
        std::cout << "[INFO ] MetaData value is : " << *this << std::endl;
    }

    /* Getters */
    uint32_t MetaData::type(void) const {
        return mType;
    }

    uint32_t MetaData::code(void) const {
        return mCode;
    }

    uint32_t MetaData::length(void) const {
        return mLength;
    }

    uint32_t MetaData::persistentID(void) const {
        return mPersistentID;
    }

    std::string MetaData::URL(void) const {
        return mURL;
    }

    std::string MetaData::clientIP(void) const {
        return mClientIP;
    }

    std::string MetaData::albumName(void) const {
        return mAlbumName;
    }

    std::string MetaData::artist(void) const {
        return mArtist;
    }

    std::string MetaData::comment(void) const {
        return mComment;
    }

    std::string MetaData::genre(void) const {
        return mGenre;
    }

    std::string MetaData::title(void) const {
        return mTitle;
    }

    std::string MetaData::composer(void) const {
        return mComposer;
    }

    std::string MetaData::fileType(void) const {
        return mFileType;
    }

    std::string MetaData::sortAs(void) const {
        return mSortAs;
    }

    /* Setters */
    void MetaData::setType(const uint32_t &pType) {
        mType = pType;
    }
    void MetaData::setCode(const uint32_t &pCode) {
        mCode = pCode;
    }
    void MetaData::setLength(const uint32_t &pLength) {
        mLength = pLength;
    }

    void MetaData::setPersistentID(const uint32_t &pPersistentID) {
        mPersistentID = pPersistentID;
    }

    void MetaData::setURL(const std::string &pURL) {
        mURL = pURL;
    }

    void MetaData::setClientIP(const std::string &pClientIP) {
        mClientIP = pClientIP;
    }

    void MetaData::setAlbumName(const std::string &pAlbumName) {
        mAlbumName = pAlbumName;
    }

    void MetaData::setArtist(const std::string &pArtist) {
        mArtist = pArtist;
    }

    void MetaData::setComment(const std::string &pComment) {
        mComment = pComment;
    }

    void MetaData::setGenre(const std::string &pGenre) {
        mGenre = pGenre;
    }

    void MetaData::setTitle(const std::string &pTitle) {
        mTitle = pTitle;
    }

    void MetaData::setComposer(const std::string &pComposer) {
        mComposer = pComposer;
    }

    void MetaData::setFileType(const std::string &pFileType) {
        mFileType = pFileType;
    }

    void MetaData::setSortAs(const std::string &pSortAs) {
        mSortAs = pSortAs;
    }
}