/**
 * NamePipe
 */

#ifndef NAMEDPIPE_HPP
#define NAMEDPIPE_HPP

/* Include --------------------------------------------- */
#include <string>

/* Defines --------------------------------------------- */

/* Class ----------------------------------------------- */
class NamedPipe {
    public:
        NamedPipe(const std::string &pFilePath);
        virtual ~NamedPipe();

        /* Pipe related functions */
        int openPipe(void);
        bool closePipe(void);
        int readPipe(char *pOut, const size_t &pSize);

        /* Getters */
        std::string filePath(void) const;
        int fd(void) const;
        FILE *file(void) const;
        int isFdValid(void);

        /* Setters */

    private:
        std::string mFilePath;

        int mFd;
        FILE *mFile;
};

#endif /* NAMEDPIPE_HPP */
