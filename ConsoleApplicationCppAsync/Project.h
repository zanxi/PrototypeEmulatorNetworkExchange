#pragma once

#include "libh.h"

#include "subsystem.h"
#include "driver.h"
#include "logger.h"


class  Project
{

public:
    Project();
    Project(string filepath, string filename);

    string toString();
    string getError();

public:
    string name;
    string description;
    string path;
    string defdrv;
    string simul;
    string ip;
    int     port;

    map<string, Subsystem> subs;
    map<string, Driver> drivers;
private:
    string error = "no error";
    void loadDrivers(string path);

};

