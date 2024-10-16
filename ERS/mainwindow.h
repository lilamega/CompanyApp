#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "employee.h"
#include <QFile>
#include <QDir>
#include <QDate>
#include <QTime>
#define _QDEBUG_

/**
 * @headerfile mainwindow.h
 */


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    //premiere instruction
    MainWindow(QWidget *parent = nullptr); // constructeur
    ~MainWindow(); //destructeur

public:
    bool folderExist(const QString folderPath); //prototype

private:
    void set_system_paths(const QString rootPath);
    bool create_file();



signals:
    void log(QString);

private slots:
    // auto creation w/ qt
    void on_pushButton_add_record_clicked();

    void on_pushButton_view_all_clicked();

    void on_pushButton_view_names_clicked();

    void on_pushButton_remove_clicked();

    void on_textEdit_textChanged();

    void on_pushButton_clean_clicked();

public slots:
    void writeLog(QString s);

private:
    Ui::MainWindow *ui;

    //create a list pointer
    QList<node> *local_nodeList = nullptr;
    Employee *emp = nullptr;

    //variables for path
    QString m_rootPath;
    QString m_logPath;
    QString m_imageFolderPath;
    QString m_logFolderPath;



};
#endif // MAINWINDOW_H
