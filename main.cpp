#include <QApplication>
#include "login.h"
#include"subwindow.h"
#include"mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login login;

    login.show();

    return a.exec();
}

