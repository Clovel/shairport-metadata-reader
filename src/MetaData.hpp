/**
 * MetaDataReader
 */

#ifndef METADATA_HPP
#define METADATA_HPP

/* Include --------------------------------------------- */
#include <string>

#include <cstdint>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
namespace metadata {
    /** Model class for media MetaData received by Shairport-sync */
    class MetaData {
        public:
            MetaData();
            virtual ~MetaData();

            /* Getters */
            uint32_t type(void) const;
            uint32_t code(void) const;
            uint32_t length(void) const;

            uint32_t persistentID(void) const;
            std::string URL(void) const;
            std::string clientIP(void) const;
            std::string albumName(void) const;
            std::string artist(void) const;
            std::string comment(void) const;
            std::string genre(void) const;
            std::string title(void) const;
            std::string composer(void) const;
            std::string fileType(void) const;
            std::string sortAs(void) const;

            /* Setters */
            void setType(const uint32_t &pType);
            void setCode(const uint32_t &pCode);
            void setLength(const uint32_t &pLength);

            void setPersistentID(const uint32_t &pPersistentID);
            void setURL(const std::string &pURL);
            void setClientIP(const std::string &pClientIP);
            void setAlbumName(const std::string &pAlbumName);
            void setArtist(const std::string &pArtist);
            void setComment(const std::string &pComment);
            void setGenre(const std::string &pGenre);
            void setTitle(const std::string &pTitle);
            void setComposer(const std::string &pComposer);
            void setFileType(const std::string &pFileType);
            void setSortAs(const std::string &pSortAs);

        private:
            /* Basic MetaData information */
            uint32_t mType;
            uint32_t mCode;
            uint32_t mLength;

            /* Specific MetaData information */
            uint32_t mPersistentID;
            std::string mURL;
            std::string mClientIP;
            std::string mAlbumName;
            std::string mArtist;
            std::string mComment;
            std::string mGenre;
            std::string mTitle;
            std::string mComposer;
            std::string mFileType;
            std::string mSortAs;
    };
}

#endif /* METADATA_HPP */
