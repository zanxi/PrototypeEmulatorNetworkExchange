#pragma once

#include "libH.h"
#include "logger.h"
#include "xmlStreamReader.h"


class Save
{
public:
    Save(XmlStreamReader* xmlReader);
    string toString();

    string value;
    string name;

};
