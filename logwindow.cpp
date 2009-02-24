#include "logwindow.h"
#include "server.h"
#include "client.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>

LogWindow::LogWindow(QWidget * parent)
: QMainWindow(parent), server(NULL), client(NULL)
{
    QLabel * central = new QLabel(this);
    QVBoxLayout * layout = new QVBoxLayout(central);

    input = new QTextEdit(central);
    input->setMaximumHeight(50);
    log = new QTextEdit(central);
    log->setReadOnly(true);
    sendButton = new QPushButton("Send", central);
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

    layout->addWidget(log, 10);
    layout->addWidget(sendButton, 0);
    layout->addWidget(input, 0);
    central->setLayout(layout);

    this->setCentralWidget(central);
    this->resize(500, 350);

    QMenuBar * bar = this->menuBar();
    QMenu * connMenu = bar->addMenu("Connection");
    connMenu->addAction("Connect to Sever", this, SLOT(startClient()));
    connMenu->addAction("Disconnect from Server");
    connMenu->addSeparator();
    connMenu->addAction("Start Server", this, SLOT(startServer()));
    connMenu->addAction("Stop Server");
}

LogWindow::~LogWindow() {}

void LogWindow::writeOnConsole(const QString & message) {
    log->append(message);
}

void LogWindow::sendMessage() {
    if(client) client->sendMesssage(input->toPlainText());
}

void LogWindow::startServer() {
    if(! server) {
        server = new Server(this);
        connect(server, SIGNAL(error(QString)), this, SLOT(writeOnConsole(QString)));
    }
}

void LogWindow::stopServer() {}

void LogWindow::startClient() {
    if(! client) {
        client = new Client(this);
        connect(client, SIGNAL(gotMessage(QString)), this, SLOT(writeOnConsole(QString)));
    }
}

void LogWindow::stopClient() {}
