#include "IniFile.hpp"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstring>

/** Constructor & Destructor **/
IniFile::IniFile()
    : _filename("")
    , _loaded(false) {
}

IniFile::IniFile(std::string filename)
    : _filename("")
    , _loaded(false) {
    LoadFromFile(filename);
}

IniFile::~IniFile() {
}

void IniFile::LoadFromFile(std::string filename) {
    _filename = filename;

    std::string line;
    std::ifstream myfile(_filename.c_str());

    _lines.clear();
    if(myfile.is_open()) {
        while(myfile.good()) {
            //read(split) by \n
            getline(myfile, line);

            //remove \r if exists
            if(*line.rbegin() == '\r') line.erase(line.end() - 1);

            Trim(line);
            _lines.push_back(line);
        }
        myfile.close();
        _loaded = true;
    }
}

void IniFile::LoadFromMemory(char* memblock, int size) {
    _filename = "";
    std::string line;

    std::istringstream iss;
    iss.rdbuf()->pubsetbuf(memblock, size);

    _lines.clear();
    while(getline(iss, line)) {
        // chomp the \r as getline understands \n
        if(*line.rbegin() == '\r') line.erase(line.end() - 1);
        Trim(line);
        _lines.push_back(line);
    }
    _loaded = true;
}

std::string IniFile::GetData() {
    std::string result;

    std::vector<std::string>::iterator it = _lines.begin();
    for(; it != _lines.end(); it++) {
        result += (*it) + "\n";
    }
    return result;
}

/** Load & Update **/
bool IniFile::IsLoaded() {
    return _loaded;
}

void IniFile::SaveToFile() {
    if(_filename == "")return;

    std::ofstream myfile(_filename.c_str());

    if(myfile.is_open()) {
        std::vector<std::string>::iterator it = _lines.begin();
        for(; it != _lines.end(); it++) {
            myfile << *it;
            if(it + 1 != _lines.end()) {
                myfile << std::endl;
            }
        }
        myfile.close();
    }
}

std::string IniFile::GetFileName() {
    return _filename;
}

/** Helper **/
std::string& IniFile::TrimRight(std::string& s, const std::string& delimiters) {
    return s.erase(s.find_last_not_of(delimiters) + 1);
}

std::string& IniFile::TrimLeft(std::string& s, const std::string& delimiters) {
    return s.erase(0, s.find_first_not_of(delimiters));
}

std::string& IniFile::Trim(std::string& s, const std::string& delimiters) {
    return TrimLeft(TrimRight(s, delimiters), delimiters);
}

std::vector<std::string> IniFile::Split(const std::string& s, const std::string& delimiters, const bool keep_empty) {
    std::vector<std::string> result;
    if(delimiters.empty()) {
        result.push_back(s);
        return result;
    }
    std::string::const_iterator substart = s.begin(), subend;
    while(true) {
        subend = search(substart, s.end(), delimiters.begin(), delimiters.end());
        std::string temp(substart, subend);
        if(keep_empty || !temp.empty()) {
            result.push_back(temp);
        }
        if(subend == s.end()) {
            break;
        }
        substart = subend + delimiters.size();
    }
    return result;
}

std::vector<std::string>::iterator IniFile::FindSection(std::string section) {
    std::string sectionFormat = "[" + section + "]";
    std::vector<std::string>::iterator itSection = _lines.begin();
    //find section
    for(; itSection != _lines.end(); itSection++) {
        //section found
        if(ToLower(*itSection) == ToLower(sectionFormat)) {
            return itSection;
        }
    }
    //section not found
    return itSection;
}

std::vector<std::string>::iterator IniFile::FindKey(std::string section, std::string key) {
    //find section
    std::vector<std::string>::iterator itSection = FindSection(section);
    //section found
    if(itSection != _lines.end()) {
        std::vector<std::string>::iterator itKey = itSection;
        //find key
        for(; itKey != _lines.end(); itKey++) {
            //key found
            if(ToLower((*itKey).substr(0, key.size())) == ToLower(key)) {
                return itKey;
            }
        }
        //key not found
        return itKey;
    } else {
        //section not found
        return itSection;
    }
}

std::string IniFile::ToLower(std::string s, const std::locale loc) {
    for(std::string::iterator p = s.begin(); p != s.end(); ++p)
        *p = tolower(*p, loc);
    return s;
}

/** Getting & Setting String**/
void IniFile::SetString(std::string section, std::string key, std::string value) {
    //find section
    std::vector<std::string>::iterator itSection = FindSection(section);

    //section found
    if(itSection != _lines.end()) {

        //find key
        std::vector<std::string>::iterator itKey = FindKey(section, key);

        //key found
        if(itKey != _lines.end()) {
            //set value
            *itKey = key + "=" + value ;
        } else {
            //insert new key
            _lines.insert(itSection + 1, key + "=" + value);
        }
    } else {
        //insert new section & key
        _lines.push_back("[" + section + "]");
        _lines.push_back(key + "=" + value);
    }
}

std::string IniFile::GetString(std::string section, std::string key, std::string defaultValue) {
    std::string result = defaultValue;

    //find key
    std::vector<std::string>::iterator itKey = FindKey(section, key);

    //key found
    if(itKey != _lines.end()) {
        //return value
        std::string pureValue = Trim(Split(*itKey, "=")[1], " \f\n\r\t\v\"");
        result = pureValue;
        return result;
    }

    //return default value
    return result;
}

/** Getting & Setting Int **/
void IniFile::SetInt(std::string section, std::string key, int value) {
    std::stringstream ss;
    ss << value;

    //find section
    std::vector<std::string>::iterator itSection = FindSection(section);

    //section found
    if(itSection != _lines.end()) {

        //find key
        std::vector<std::string>::iterator itKey = FindKey(section, key);

        //key found
        if(itKey != _lines.end()) {
            //set value
            *itKey = key + "=" + ss.str();
        } else {
            //insert new key
            _lines.insert(itSection + 1, key + "=" + ss.str());
        }
    } else {
        //insert new section & key
        _lines.push_back("[" + section + "]");
        _lines.push_back(key + "=" + ss.str());
    }
}
int IniFile::GetInt(std::string section, std::string key, int defaultValue) {
    int result = defaultValue;

    //find key
    std::vector<std::string>::iterator itKey = FindKey(section, key);

    //key found
    if(itKey != _lines.end()) {
        //return value
        std::string pureValue = Trim(Split(*itKey, "=")[1]);
        std::stringstream ss;
        ss << pureValue;
        ss >> result;
        return result;
    }

    //return default value
    return result;
}

/** Getting & Setting Bool **/
void IniFile::SetBool(std::string section, std::string key, bool value) {
    std::string strValue = (value) ? "true" : "false";

    //find section
    std::vector<std::string>::iterator itSection = FindSection(section);

    //section found
    if(itSection != _lines.end()) {

        //find key
        std::vector<std::string>::iterator itKey = FindKey(section, key);

        //key found
        if(itKey != _lines.end()) {
            //set value
            *itKey = key + "=" + strValue;
        } else {
            //insert new key
            _lines.insert(itSection + 1, key + "=" + strValue);
        }
    } else {
        //insert new section & key
        _lines.push_back("[" + section + "]");
        _lines.push_back(key + "=" + strValue);
    }
}

bool IniFile::GetBool(std::string section, std::string key, bool defaultValue) {
    //find key
    std::vector<std::string>::iterator itKey = FindKey(section, key);

    //key found
    if(itKey != _lines.end()) {
        //return value
        std::string pureValue = Trim(Split(*itKey, "=")[1]);
        if(ToLower(pureValue) == "true") {
            return true;
        } else {
            *itKey = key + "=false"; //fix word
            return false;
        }
    }

    //return default value
    return defaultValue;
}

/** Getting & Setting Float **/
void IniFile::SetFloat(std::string section, std::string key, float value) {
    std::stringstream ss;
    ss << value;

    //find section
    std::vector<std::string>::iterator itSection = FindSection(section);

    //section found
    if(itSection != _lines.end()) {

        //find key
        std::vector<std::string>::iterator itKey = FindKey(section, key);

        //key found
        if(itKey != _lines.end()) {
            //set value
            *itKey = key + "=" + ss.str();
        } else {
            //insert new key
            _lines.insert(itSection + 1, key + "=" + ss.str());
        }
    } else {
        //insert new section & key
        _lines.push_back("[" + section + "]");
        _lines.push_back(key + "=" + ss.str());
    }
}

float IniFile::GetFloat(std::string section, std::string key, float defaultValue) {
    float result = defaultValue;

    //find key
    std::vector<std::string>::iterator itKey = FindKey(section, key);

    //key found
    if(itKey != _lines.end()) {
        //return value
        std::string pureValue = Trim(Split(*itKey, "=")[1]);
        std::stringstream ss;
        ss << pureValue;
        ss >> result;
        return result;
    }

    //return default value
    return result;
}


