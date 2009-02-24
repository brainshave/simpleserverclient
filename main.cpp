#include "logwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogWindow window;
    window.show();

    return a.exec();
}
