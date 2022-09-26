#pragma once
#include "libh.h"

class Logger
{
public:
    Logger(string path);
    //static _Tree_head_scoped_ptr<File> m_logFile;
    //static void messageHandler(QtMsgType type, const QMessageLogContext& context, const string& msg);
    static void messageHandler();
    //static QTextStream out;
    static mutex mutex_;
    static string path;
    //static QDateTime nowDate;
};


