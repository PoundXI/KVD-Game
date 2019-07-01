#ifndef FILEMANAGER_HPP_INCLUDED
#define FILEMANAGER_HPP_INCLUDED

#include <vector>
#include <string>
#include <sys/stat.h> //mode_t

class FileManager {
public:
    static std::vector<std::string> GetFileNames(std::string path);
    static std::vector<std::string> GetDirectoryNames(std::string path);

    static bool IsFileExists(std::string path);
    static bool IsDirectoryExists(std::string path);

    static std::string ReadFromFile(std::string filename);
    static void WriteToFile(std::string filename, char* memblock, int size);

    static void CreateDirectoryPath(std::string path, mode_t mode);

    static void RemoveFile(std::string path);
};

#endif // FILEMANAGER_HPP_INCLUDED
