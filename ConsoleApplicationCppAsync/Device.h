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
    list<string> getSrcVariables();       //���������� ����� ���������� ������� ��������� �� ������ ����������
    list<string> getDstVariables();       //���������� ����� ���������� ������� ��������� �� ������ ����������

    void setDriver(map<string, Variable>* allvars, Driver* drv);
    //    void setAllVariables(map<string,Variable> *allvars);
    void readAll();                         // ��������� ����� �� ��������� ����������
    void writeAll();                        // �������� � ����� �������� ���������� ����������

    void writeBufferDriver(void* extbuff);  // ������� �� �������� ������ �� ���������
    void readBufferDriver(void* extbuff);  // ������� �� ����������� ������ �� �������
    bool compareBufferDriver(void* extbuff); // true if equal

    string toString();
    list<string> srcVars;       //����� ���������� ������� ��������� �� ������ ����������
    list<string> dstVars;       //����� ���������� ������� ��������� �� ������ ����������

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
    map <string, int> nameAddress;       //������� �� ����� � ����� ������

};
