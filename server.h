#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QVector>
#include <QMutex>

class ServerThread;
class LogWindow;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject * parent = 0);
    ~Server();

protected:
    void incomingConnection(int socketDesc);

public slots:
    // powinno odebrac wiadomosc z jednego polaczenia i rozeslac go do wszystkich
    void receiveMessage(const QString & message);

signals:
    void error(const QString & message);

private:
    QVector<ServerThread*> threads;
    QMutex mutex;
};

#endif // SERVER_H
