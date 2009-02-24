#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QTcpSocket
{
    Q_OBJECT
public:
    Client(QObject * parent = 0);
    ~Client();

public slots:
    // bedzie zwracalo prosta informacje o nawiazaniu polaczenia
    void onConnected();

    // okno bedzie to wywolywalo, zeby wyslac wiadomosc
    void sendMesssage(const QString & message);

    // przeczyta wiadomosc, wysle na okno
    void processRead();

signals:
    void gotMessage(const QString & message);
};

#endif // CLIENT_H
