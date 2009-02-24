#include "server.h"
#include "serverthread.h"

#include <QMutexLocker>
#include <QVectorIterator>
#include <QDebug>

Server::Server(QObject * parent)
: QTcpServer(parent)
{
    if(! listen(QHostAddress::Any, 7890) )
        emit error("Failed opening port 7890 for server");
    else
        emit error("Started server on port 7890.");
}

Server::~Server() {}

void Server::incomingConnection(int socketDesc) {
    ServerThread * newthread = new ServerThread(socketDesc, this);

    mutex.lock();
    threads.append(newthread);
    mutex.unlock();

    // odebranie wiadomosci w watku spowoduje przekazanie go do servera
    connect(newthread, SIGNAL(receivedMessage(QString)), this, SLOT(receiveMessage(QString)));
    connect(newthread, SIGNAL(error(QString)), parent(), SLOT(writeOnConsole(QString)));
    newthread->start();
}

void Server::receiveMessage(const QString & message) {
    mutex.lock();
    QVectorIterator<ServerThread*> threadsIter(threads);
    mutex.unlock(); // chyba mozna zdjac tu blokade, bo QVectorIterator nie zmieania obiektu

    while(threadsIter.hasNext()) {
        threadsIter.next()->sendMessage(message);
    }
}
