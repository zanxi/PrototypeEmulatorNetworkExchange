#pragma once

#include "libh.h"
#include "logger.h"
#include "xmlStreamReader.h"

class Signal
{
public:
    Signal();
    Signal(const XmlStreamReader* xmlReader);
    string toString();
    string name;
    int format;
    bool mode;
    int address;
    string value;
};

