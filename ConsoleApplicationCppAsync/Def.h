#pragma once

#include "libh.h"
#include "logger.h"
#include "xmlStreamReader.h"

class Def
{
public:
    Def(XmlStreamReader* xmlReader);
    string toString();

    string name;
    string dname;
};
