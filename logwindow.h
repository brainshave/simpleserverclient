#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>

class Server;
class Client;

class LogWindow : public QMainWindow {
    Q_OBJECT
public:
    LogWindow(QWidget * parent = 0);
    ~LogWindow();

public slots:
    void writeOnConsole(const QString & message);
    void sendMessage();

    void startServer();
    void stopServer();
    void startClient();
    void stopClient();

private:
    QTextEdit *log, *input;
    QPushButton *sendButton;
    Server * server;
    Client * client;
};

#endif // LOGWINDOW_H
