#pragma once

#include "logger.h"
#include "tablemodbus.h"
#include "xmlStreamReader.h"

class MModbus
{
public:
    MModbus();
    MModbus(const XmlStreamReader* xmlReader);
    string toString();

    string name;
    string description;
    string type;
    string ip1 = "";
    string ip2 = "";
    int port;
    int step;
    string xml;
    TableModbus tableModbus;

};
