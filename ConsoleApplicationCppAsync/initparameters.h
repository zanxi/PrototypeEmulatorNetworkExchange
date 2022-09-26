#pragma once

#include "libh.h"

typedef struct Ini {
    int TimeReady = 10;
    int Screen_Update = 1000;
    int SimulStep = 100;
    int Modbus_Step = 500;
    int Modbus_Reconnect = 5000;
    int SimulBasePort = 5555;
    int OneCadrPort = 1080;
    unsigned long OneCadrStep = 5000;
    int OneCadrTimeOut = 2000;
    string logPath = "log";
    string dataPath = "dataSimul/pr";
    string dataName = "main.xml";

} IniParam;

