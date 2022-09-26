#pragma once

#include "logger.h"
#include "signal.h"
#include "xmlStreamReader.h"

class Driver
{
public:
    Driver();
    Driver(XmlStreamReader* xmlReader);
    string toString();


public:
    string name;
    string description;
    string code;
    size_t lenData;
    size_t lenInit;
    string header;
    string type;
    map <string, Signal> datas;
    map <string, Signal> inits;

};
