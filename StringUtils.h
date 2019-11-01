#pragma once

#include <array>
#include <string>
#include <QString>

template<size_t size>
const std::array<unsigned char, size> qStringToStdArray(const QString &s)
{
    std::array<unsigned char, size> buf;
    std::string stdString(s.toStdString());
    for (size_t i = 0; i < 16; ++i)
        buf[i] = static_cast<unsigned char>(stdString[i] - '0');
    return buf;
}
