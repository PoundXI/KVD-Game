#ifndef TYPECONVERTOR_HPP_INCLUDED
#define TYPECONVERTOR_HPP_INCLUDED

#include <string>

class Conversion {
public:
    template <typename T>
    static std::string ToString(T value);
    static std::string IntToString(int value);
    static std::string FloatToString(float value);

    template <typename T>
    static T ToType(std::string value);
    static int StringToInt(std::string value);
    static float StringToFloat(std::string value);
};

#endif // TYPECONVERTOR_HPP_INCLUDED
