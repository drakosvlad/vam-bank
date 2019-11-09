#pragma once

#include <array>
#include <string>
#include <QString>

template<size_t size>
const std::array<unsigned char, size> qStringToStdArray(const QString &s)
{
    std::array<unsigned char, size> buf;
    std::string stdString(s.toStdString());
    for (size_t i = 0; i < size; ++i)
        buf[i] = static_cast<unsigned char>(stdString[i] - '0');
    return buf;
}

template<size_t size>
const std::array<unsigned char, size> hexQStringToStdArray(const QString &s)
{
    QByteArray arr(QByteArray::fromHex(s.toLatin1()));
    std::array<unsigned char, size> buf;
    for (size_t i = 0; i < 16; ++i)
        buf[i] = static_cast<unsigned char>(arr.at(i));
    return buf;
}
