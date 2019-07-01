#include "Conversion.hpp"

#include <sstream>

template <typename T>
std::string Conversion::ToString(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string Conversion::IntToString(int value) {
    return ToString<int>(value);
}

std::string Conversion::FloatToString(float value) {
    return ToString<float>(value);
}

template <typename T>
T Conversion::ToType(std::string value) {
    T result;
    std::stringstream ss;
    ss << value;
    ss >> result;
    return result;
}

int Conversion::StringToInt(std::string value) {
    return ToType<int>(value);
}

float Conversion::StringToFloat(std::string value) {
    return ToType<float>(value);
}
