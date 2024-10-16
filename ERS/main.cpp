/**
 * \file main.c
 * @brief Programm Employees.
 * \author Lila.M
 * \version 1.0.0
 * \date mai 2024
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
