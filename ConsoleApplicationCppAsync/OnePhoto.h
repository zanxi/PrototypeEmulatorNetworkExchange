#pragma once

#include "libh.h"
#include "DataStore.h"

#include "initparameters.h"
#define maxId 1300

extern IniParam Setup;


class OneCadrMaster :public thread
{    
public:
    //    OneCadrMaster();
    OneCadrMaster(DataStore* dts, string nameSubsystem, int ip);
    void makeStep();
    string readVariable(string name);
    void run();
    //QDateTime getLastTime();
    string toString();
private:
    int lastId;
    map<int, string> values;
    map<string, int> vars;
    DataStore* dts;
    string nameSubsystem;
    string ipPhoto;
    //QTimer* tmr;
    int ip;
    mutex mutex;
    //QDateTime lastOperation = QDateTime::currentDateTime();
};


