/**
 * NamedPipe
 */

/* Include --------------------------------------------- */
#include "NamedPipe.hpp"

// #include <filesystem> // TODO : Link -lstdc++fs
#include <cstdio>

#include <fcntl.h> 
#include <unistd.h>
#include <errno.h>

/* Class implementation -------------------------------- */
NamedPipe::NamedPipe(const std::string &pFilePath) : 
    mFilePath(pFilePath)
{
    /* Empty */
}

NamedPipe::~NamedPipe() {
    closePipe();
}

int NamedPipe::openPipe(void) {
    // if(std::filesystem::is_fifo(std::filesystem::path(mFilePath))) {
    //     mFd = open(mFilePath.c_str(), O_RDONLY | O_NONBLOCK);
    //     return mFd;
    // } else {
    //     return -1;
    // }

    mFd = open(mFilePath.c_str(), O_RDONLY | O_NONBLOCK);
    mFile = fdopen(mFd, "r");

    return mFd;
}

bool NamedPipe::closePipe(void) {
    close(mFd);

    return true;
}

int NamedPipe::readPipe(char *pOut, const size_t &pSize) {
    return read(mFd, (void *)pOut, pSize);
}

/* Getters */
std::string NamedPipe::filePath(void) const {
    return mFilePath;
}

int NamedPipe::fd(void) const {
    return mFd;
}

FILE *NamedPipe::file(void) const {
    return mFile;
}

int NamedPipe::isFdValid(void) {
    return fcntl(mFd, F_GETFD) != -1 || errno != EBADF;
}
