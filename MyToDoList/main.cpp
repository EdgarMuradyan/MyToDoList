#include "mainwindow.h"

#include <QApplication>
#include <QCalendarWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *mainWindow = new MainWindow();
    mainWindow->setMinimumSize(600,500);
    mainWindow->setMaximumWidth(600);
    QIcon winIcon("C:/Users/home_/Desktop/Edgar/To Do List/MyToDoList/Icons/WINICON");
    mainWindow->setWindowIcon(winIcon);

    mainWindow->show();
    return a.exec();
}
