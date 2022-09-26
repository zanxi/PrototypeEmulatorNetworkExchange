#pragma once
#include "libH.h"
#include "xmlStreamReader.h"
#include "MModbus.h"
#include "Save.h"
#include "Variable.h"
#include "Device.h"


class Subsystem
{
public:
    Subsystem();
    Subsystem(const XmlStreamReader* xmlReader);
    void loadSubsystem(string path, string namefile);
    string getError();
    string toString();

    string name;
    string description;
    string scheme;
    int id;
    string file;
    string main;
    string second;
    string path;
    string result;
    int step;
    string saveFile;
    map <string, MModbus> modbuses;
    map <string, Variable> vars;
    map <string, Device> devices;
    map <string, Save>   saves;
    //time lastOperation = QDateTime::currentDateTime();
    list <string> orderDevices;
    int maxIdVariable = 0;
private:
    string error = "";
    bool loadVariables(string filexml);
    bool loadDevices(string path, string filexml);
    bool loadSaves(string filexml);

};
