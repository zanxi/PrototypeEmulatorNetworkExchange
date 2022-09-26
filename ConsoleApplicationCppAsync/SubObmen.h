
#pragma once

#include "datastore.h"
#include "variablefinder.h"
#include "initparameters.h"
#include "onephoto.h"

#include "Widget.h"

extern IniParam Setup;

class SubObmen : public Widget
{
    
public:
    explicit SubObmen(DataStore* dts, Widget* parent = nullptr);
    void updateTimer();
    //void showFinded(StringList seek);

    void setSize(int w, int h);
    void connectSlotFind(VariableFinder* varFind);
    void connectCollapsFind(VariableFinder* varFind);

    //TreeWidget* tree;

private:
    map<string, OneCadrMaster*> masters;
    //QTimer* tmr = nullptr;
    DataStore* dts;
    Widget* parent;
    //bool isFinded(StringList seek, string one, string duo);
    void collaps();
//signals:

//public slots:
};
