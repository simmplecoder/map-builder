#include "mainwindow.h"
#include <QApplication>
#include <GL/gl.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    glEnable(GL_MULTISAMPLE);
    w.show();

    return a.exec();
}
