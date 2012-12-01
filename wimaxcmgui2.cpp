#include <QtGui/QApplication>
#include "window.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.show();
    a.setQuitOnLastWindowClosed(false);
    return a.exec();
}
