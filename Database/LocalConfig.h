#pragma once

#include <QString>

class LocalConfig
{
public:
    virtual ~LocalConfig() = 0;
    static const QString DB_NAME;
    static const QString DB_USER;
    static const QString DB_PASS;
    static const QString DB_HOST;
};
