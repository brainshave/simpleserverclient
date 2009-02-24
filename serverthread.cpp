#include "serverthread.h"

#include <QDebug>
#include <QMutexLocker>

ServerThread::ServerThread(int sockDesc, QObject * parent)
: QThread(), sockDesc(sockDesc)
{
    // kasuje watek jesli sie skonczy jego wykonywanie
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

    // wywoluje processRead() jesli sa jakies dane
    //connect(&socket, SIGNAL(readyRead()), this, SLOT(processRead()));

    connect(&socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
}

ServerThread::~ServerThread() {
    qDebug() << this << "is dying";
}

void ServerThread::run() {
    if(! socket.setSocketDescriptor(sockDesc)) {
        emit error("Failed opening socket.");
        return;
    }
    emit error("Got Client.");
    while(socket.isValid()) {
        socket.waitForReadyRead();
        emit receivedMessage(QString(socket.readAll()));
    }
    // uruchamia event loop
    //exec();
}

//void ServerThread::processRead() {
//    // wysyla signal z wiadomoscia do Servera
//    // bardzo podatne na DoS-owanie...
////    char data[5];
////    qint64 bytesRead = 0;
////    do { bytesRead = socket.read(data, 4); }
////    while(bytesRead);
////    data[4] = 0;
////    emit receivedMessage(QString(data));
//    emit receivedMessage(QString(socket.readAll()));
//    qDebug() << socket.state();
//    qDebug() << "redeable?" << socket.isReadable();
//    qDebug() << "valid?" << socket.isValid();
//    qDebug() << "readLine?" << socket.canReadLine();
//}

void ServerThread::sendMessage(const QString & message) {
    //QMutexLocker lock(&mutex);
    if(socket.isValid() && socket.isWritable()) {
        if(socket.write(message.toUtf8()) == -1) {
            emit error("Failed sending message to client.");
        }
    }
}

void ServerThread::onDisconnect() {
    emit error("Client disconnected.");
    exit();
}
