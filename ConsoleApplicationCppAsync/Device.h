#pragma once

#include "libh.h"
#include "def.h"
#include "variable.h"
#include "driver.h"
#include "logger.h"
#include "xmlStreamReader.h"
#include "IODevice.h"

class  Device
{
public:
    Device();
    Device(const XmlStreamReader* xmlReader, IODevice* file);
    list<string> getSrcVariables();       //Возвращает имена переменных которые источники на данном устройстве
    list<string> getDstVariables();       //Возвращает имена переменных которые приемники на данном устройстве

    void setDriver(map<string, Variable>* allvars, Driver* drv);
    //    void setAllVariables(map<string,Variable> *allvars);
    void readAll();                         // прочитать буфер во временные переменные
    void writeAll();                        // записать в буфер значения внутренних переменных

    void writeBufferDriver(void* extbuff);  // перенос из внешнего буфера во внутрений
    void readBufferDriver(void* extbuff);  // перенос из внутреннего буфера во внешний
    bool compareBufferDriver(void* extbuff); // true if equal

    string toString();
    list<string> srcVars;       //имена переменных которые источники на данном устройстве
    list<string> dstVars;       //имена переменных которые приемники на данном устройстве

    map<string, Def> defs;
    map<string, Variable>* allvars;
    map<string, bool> myvars;
    string name;
    string description;
    string driver;
    string slot;
    //QDateTime lastOperation = QDateTime::currentDateTime();

    mutex* mutex_ = new mutex();
    Driver drv;
private:
    void* dataBuffer = nullptr;
    map <string, int> nameAddress;       //Переход из имени в адрес буфера

};
