#pragma once

#include "libH.h"
#include "logger.h"
#include "xmlStreamReader.h"


class  Variable
{
public:
    Variable();
    Variable(const XmlStreamReader* xmlReader);
    string toString();
    string valueToString();
    void defaultValue();

    void readValue(void* buffer, int address);
    void writeValue(void* buffer, int address);
public:
    string name;
    string description;
    int format;
    int size = 1;
    int id = 0;

    string value = "";
private:
    bool isZero(void* buffer, int len);

};


