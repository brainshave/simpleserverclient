#include "client.h"

Client::Client(QObject * parent)
: QTcpSocket(parent)
{
    connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(this, SIGNAL(readyRead()), this, SLOT(processRead()));

    connectToHost("localhost", 7890);
}

Client::~Client() {}

void Client::onConnected() {
    emit gotMessage(QString("Connected to Host."));
}

void Client::sendMesssage(const QString & message) {
    if(write(message.toUtf8()) == -1) {
        emit gotMessage("Failed sending message to client.");
    }
}

void Client::processRead() {
    emit gotMessage(QString(readAll()));
}
