#include "FileManager.hpp"

//http://stackoverflow.com/questions/2197918/cross-platform-way-of-testing-whether-a-file-is-a-directory
//http://www.kernel.org/doc/man-pages/online/pages/man2/stat.2.html

#include <cstdio> // FILE, remove
#include <dirent.h> //DIR
#include <sys/stat.h> // stat, mode_t

#include <fstream>
#include <cstring>

std::vector<std::string> FileManager::GetFileNames(std::string path) {
    std::vector<std::string> result;
    std::string fullpath;

    DIR* dir = opendir(path.c_str());
    struct dirent* ent;

    if(dir != NULL) {
        while(ent = readdir(dir)) {
            if((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0)) {
                fullpath = path + "/" + ent->d_name; //unix path seperator
                if(IsFileExists(fullpath)) {
                    result.push_back(ent->d_name);
                }
            }
        }
    }
    closedir(dir);
    return result;
}

std::vector<std::string> FileManager::GetDirectoryNames(std::string path) {
    std::vector<std::string> result;
    std::string fullpath;

    DIR* dir = opendir(path.c_str());
    struct dirent* ent;

    if(dir != NULL) {
        while(ent = readdir(dir)) {
            if((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0)) {
                fullpath = path + "/" + ent->d_name; //unix path seperator
                if(IsDirectoryExists(fullpath)) {
                    result.push_back(ent->d_name);
                }
            }
        }
    }
    closedir(dir);
    return result;
}

bool FileManager::IsFileExists(std::string path) {
    struct stat s;
    if(stat(path.c_str(), &s) == 0) {
        if((s.st_mode & S_IFMT) ==  S_IFREG)
            return true;
    }
    return false;
}

bool FileManager::IsDirectoryExists(std::string path) {
    struct stat s;
    if(stat(path.c_str(), &s) == 0) {
        if((s.st_mode & S_IFMT) ==  S_IFDIR)
            return true;
    }
    return false;
}

std::string FileManager::ReadFromFile(std::string filename) {
    std::string result;
    std::string line;
    std::ifstream myfile(filename.c_str());

    if(myfile.is_open()) {
        while(myfile.good()) {
            getline(myfile, line);
            result += line + "\n";
        }
        myfile.close();
    }
    return result;
}

void FileManager::WriteToFile(std::string filename, char* memblock, int size) {
    std::ofstream ofs;
    ofs.open(filename.c_str(), std::ofstream::out | std::ofstream::app);
    ofs.write(memblock, size);
    ofs.close();
}

void FileManager::CreateDirectoryPath(std::string path, mode_t mode) {
    int pos = 0;
    int next = 0;

    std::string node = "";
    std::string currentPath = "";
    if(path.substr(0, 1) == "/") {
        currentPath = "/"; //unix root directory
    }

    while(pos < path.length() && next != -1) {
        pos = path.find_first_of("/", pos);
        next = path.find_first_of("/", pos + 1);
        node = path.substr(pos + 1, next - pos - 1);
#ifdef WIN32
        mkdir((currentPath + node).c_str());
#else
        mkdir((currentPath + node).c_str(), mode);
#endif
        currentPath += node + "/";
        pos++;
    }
}

void FileManager::RemoveFile(std::string path) {
    remove(path.c_str());
}
