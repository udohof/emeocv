/*
 * Directory.cpp
 *
 */

#include <string>
#include <list>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#include <iostream>
#else
#include <dirent.h>
#endif

#include "Directory.h"

Directory::Directory(const char* path, const char* extension) :
        _path(path), _extension(extension) {
}

std::list<std::string> Directory::list() {
    std::list<std::string> files;

#ifdef _WIN32
    WIN32_FIND_DATAA findFileData;
    std::string searchPath = _path + "\\*.*";
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findFileData);
    
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                hasExtension(findFileData.cFileName, _extension.c_str())) {
                files.push_back(std::string(findFileData.cFileName));
            }
        } while (FindNextFileA(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
#else
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(_path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if ((ent->d_type == DT_REG || ent->d_type == DT_LNK)
                    && hasExtension(ent->d_name, _extension.c_str())) {
                files.push_back(std::string(ent->d_name));
            }
        }
        closedir(dir);
    }
#endif
    return files;
}

std::string Directory::fullpath(const std::string filename) {
    std::string path(_path);
#ifdef _WIN32
    path += "\\";
#else
    path += "/";
#endif
    path += filename;
    return path;
}

bool Directory::hasExtension(const char* name, const char* ext) {
    if (NULL == name || NULL == ext) {
        return false;
    }
    size_t blen = strlen(name);
    size_t slen = strlen(ext);
    return (blen >= slen) && (0 == strcmp(name + blen - slen, ext));
}
