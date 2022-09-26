#include "onephoto.h"

OneCadrMaster::OneCadrMaster(DataStore* dts, string nameSubsystem, int ip)
{
    this->dts = dts;
    this->nameSubsystem = nameSubsystem;
    this->ip = ip;
}

//void OneCadrMaster::makeStep()
//{
//    int idStep = (lastId > maxId) ? maxId : lastId;
//    for (int id = 1; id < lastId; id += idStep) {
//        QTcpSocket* socket = new QTcpSocket;
//        socket->connectToHost(ipPhoto, static_cast<uint>(Setup.OneCadrPort));
//        if (!socket->waitForConnected(Setup.OneCadrTimeOut)) {
//            delete socket;
//            return;
//        }
//        string req;
//        req.sprintf("R%d %d", id, (id + idStep) > lastId ? lastId : id + idStep);
//        socket->write(req.toLatin1());
//        string result = "";
//        if (!socket->waitForReadyRead(Setup.OneCadrTimeOut)) {
//            socket->close();
//            delete socket;
//            return;
//        };
//        while (1) {
//            QByteArray in = socket->read(128000);
//            if (in.size() == 0) break;
//            result.append(string::fromLatin1(in));
//            if (result.contains("</vals>")) break;
//            if (!socket->waitForReadyRead(Setup.OneCadrTimeOut)) break;
//        };
//        if (!result.contains("</vals>"))
//        {
//            qInfo() << toString() << " bad responce " << req;
//            socket->close();
//            delete socket;
//            return;
//        }
//        QXmlStreamReader reader(result);
//        while (!reader.atEnd()) {
//            if (reader.name().toString() == "val" && reader.isStartElement()) {
//                string value;
//                int id;
//                foreach(const QXmlStreamAttribute & attr, reader.attributes()) {
//                    if (attr.name().toString() == "value") {
//                        value = attr.value().toString();
//                    }
//                    if (attr.name().toString() == "id") {
//                        id = attr.value().toInt();
//                    }
//                }
//                mutex.lock();
//                values.insert(id, value);
//                mutex.unlock();
//            }
//            reader.readNext();
//        }
//        mutex.lock();
//        lastOperation = QDateTime::currentDateTime();
//        mutex.unlock();
//        socket->close();
//        delete socket;
//        QThread::msleep(1000);
//    }
//}

//string OneCadrMaster::readVariable(string name)
//{
//    if (!vars.(name)) return "not found";
//    int id = vars.value(name);
//    mutex.lock();
//    string value = "is array";
//    if (values.contains(id)) value = values.value(id);
//    mutex.unlock();
//    return  value;
//}

//void OneCadrMaster::run()
//{
//    Subsystem sub = dts->pr.subs.value(nameSubsystem);
//    ipPhoto = ip == 0 ? sub.main : sub.second;
//    if (ipPhoto == "") {
//        qWarning() << "in subsystem " << nameSubsystem << " invalid ip";
//        return;
//    }
//    lastId = -1;
//    foreach(Variable var, sub.vars) {
//        lastId = lastId < var.id ? var.id : lastId;
//        values.insert(var.id, "not read");
//        vars.insert(var.name, var.id);
//    }
//    while (1) {
//        QThread::msleep(Setup.OneCadrStep);
//        makeStep();
//    }
//}

//QDateTime OneCadrMaster::getLastTime()
//{
//    QDateTime result;
//    mutex.lock();
//    result = lastOperation;
//    mutex.unlock();
//    return  result;
//}

string OneCadrMaster::toString()
{
    return nameSubsystem + " " + ipPhoto;
}


