#pragma once

#include "libh.h"
#include "project.h"
#include "subsystem.h"
#include "variable.h"
#include "device.h"


class DataStore
{
public:
    DataStore(Project* prj);
    string toString();

    void readAllDevices();
    void writeAllDevices();

    map<string, Variable> allvars;
    map<string, Device> alldevs;
    Project pr;
};
