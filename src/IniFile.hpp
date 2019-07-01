#ifndef INIFILE_HPP_INCLUDED
#define INIFILE_HPP_INCLUDED

#include <string>
#include <vector>
#include <locale>


class IniFile {
private:
    std::vector<std::string> _lines;
    std::string _filename;
    bool _loaded;

    //Trim
    std::string& TrimRight(std::string& s, const std::string& delimiters = " \f\n\r\t\v");
    std::string& TrimLeft(std::string& s, const std::string& delimiters = " \f\n\r\t\v");
    std::string& Trim(std::string& s, const std::string& delimiters = " \f\n\r\t\v");

    //Split
    std::vector<std::string> Split(const std::string& s, const std::string& delimiters, const bool keep_empty = true);

    //Find
    std::vector<std::string>::iterator FindSection(std::string section);
    std::vector<std::string>::iterator FindKey(std::string section, std::string key);

    //Format
    std::string ToLower(std::string s, const std::locale loc = std::locale());
public:
    IniFile();
    IniFile(std::string filename);
    ~IniFile();

    void LoadFromFile(std::string filename);
    void LoadFromMemory(char* memblock, int size);
    std::string GetData();
    void SaveToFile();
    bool IsLoaded();
    std::string GetFileName();

    //string
    void SetString(std::string section, std::string key, std::string value);
    std::string GetString(std::string section, std::string key, std::string defaultValue = "");

    //int
    void SetInt(std::string section, std::string key, int value);
    int GetInt(std::string section, std::string key, int defaultValue = 0);

    //bool
    void SetBool(std::string section, std::string key, bool value);
    bool GetBool(std::string section, std::string key, bool defaultValue = false);

    //float
    void SetFloat(std::string section, std::string key, float value);
    float GetFloat(std::string section, std::string key, float defaultValue = 0.0);
};

#endif // INIFILE_HPP_INCLUDED

