#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QTcpSocket>

class ServerThread : public QThread
{
    Q_OBJECT
public:
    ServerThread(int sockDesc, QObject * parent);
    ~ServerThread();

    void run();

public slots:
//    void processRead();
    void sendMessage(const QString & message);
    void onDisconnect();

signals:
    void receivedMessage(const QString & message);
    void error(const QString & message);

private:
    int sockDesc;
    QMutex mutex;
    QTcpSocket socket;
};

#endif // SERVERTHREAD_H
