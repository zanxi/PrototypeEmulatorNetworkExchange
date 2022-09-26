#pragma once

#include "Widget.h"

class VariableFinder :public Widget
{
    
public:
    explicit VariableFinder(Widget* parent = nullptr);
    //stringList seek();

    //QFrame* frame;

//signals:
//    void on_find_clicked(stringList text);
//    void collapsAll();

private:
    //PushButton* findButton;
    //PushButton* collapsButton;
    //LineEdit* lineEdit;
    //String seek_str = "";
    Widget* parent;
    void clicked();
    void collaps();
};
