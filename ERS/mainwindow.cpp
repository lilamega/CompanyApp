/**
 * @file mainwindow.cpp
 * @author Lila.M
 * @version 1.0.0
 * @date mai 2024
 * @brief Programm to found company's employees
 * @mainclass MainWindow
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) /// \brief MainWindow constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); ///\brief create ui


    //create a class 'Employee'
    emp = new Employee(); //2nd instruction, go into
    if(!connect(this, SIGNAL(log(QString)),
                    this, SLOT(writeLog(QString))))
    {
        //throw(tr("Boot eRRor(s)@[%1:%2]").arg(__FILE__, QString::number(__LINE__ )));
    }

    if(!connect(emp, SIGNAL(log(QString)),
                    this, SLOT(writeLog(QString))))
    {
        //throw(tr("Boot eRRor(s)@[%1:%2]").arg(__FILE__, QString::number(__LINE__ )));
    }


    //emp->print_all_employee_info(emp->get_node_list());
    //emp->print_all_employee_name(emp->get_node_list());

    // change automatically root path/application path  according to the mode (debug or release)
    #ifdef QT_NO_DEBUG
        set_system_paths(QCoreApplication::applicationDirPath());
    #else
        set_system_paths("C:/Qt/Projects/ERS");
    #endif

    create_file();

    emp->print_all_employee_info(emp->get_node_list());
}

MainWindow::~MainWindow() /// \brief MainWindow destructor
{
    delete ui;
}

/**
 * @brief MainWindow::writeLog -- show code’s progress
 * @param log
 */
void MainWindow::writeLog(QString s)
{
    ui->textEdit->append(s);

    //print debug if we are in debug mode
    #ifndef QT_NO_DEBUG
         qDebug()<<s;

         QFile file(m_logPath);
           if (file.open(QFile::Append))
           {
               QTextStream stream(&file);
               stream  << s +"\n";
               file.close();
           }
           else
           {
               emit log("Log eRRor(s)!");
               //return false;
           }

    #endif

}

//function for folders
/**
 * @brief MainWindow::folderExist
 * @param folderPath
 * @return directory exixst (True) or not (False)
 */
bool MainWindow::folderExist(const QString folderPath)
{
    QDir dir(folderPath);
    return dir.exists();
}

//function for folders
/**
 * @brief MainWindow::set_system_paths -- get absolute and relative paths
 * @param rootPath
 */
void MainWindow::set_system_paths(const QString rootPath)
{
   // set paths
   m_rootPath = rootPath;
   m_logFolderPath = rootPath + "/logs";
   m_imageFolderPath = rootPath + "/images";
}

/**
 * @brief MainWindow::create_file -- record file
 * @return state (open or error) and close
 */
bool MainWindow::create_file()
{
    //file name
    QString logName = QDateTime::currentDateTime().toString("yyyy_MM_dd.HH_mm_ss") ;

     m_logPath = m_logFolderPath + "/"  + "trace_"  + logName + ".log";

     QFile file(QDir::toNativeSeparators(m_logPath));

     //open file
     if (!file.open(QIODevice::WriteOnly))
     {
         emit log("open file error");
         return false;
     }

     QTextStream in(&file);
     in <<QString("*** ERS log file - ")<<QDateTime::currentDateTime().toString("yyyy-MM-dd_HH:mm:ss:zzz")<<" ***\n";


     //close file
     file.close();
     emit log("records file updated successfully \n");
     return true;
}


// events/slots functions
void MainWindow::on_pushButton_add_record_clicked()
{
    node n;
    // get value from QT lineEdit
    n.name = ui->lineEdit_name->text();
    n.job = ui->lineEdit_job->text();
    bool ok;
    n.age = ui->lineEdit_age->text().toUInt(&ok,10);

    //call function
    emp->add_employee(n,emp->get_node_list());
    //emit log("add employee");

}


void MainWindow::on_pushButton_view_all_clicked()
{
    emp->print_all_employee_info(emp->get_node_list());
    //emit log("all info");

}


void MainWindow::on_pushButton_view_names_clicked()
{
    emp->print_all_employee_name(emp->get_node_list());

    //emit log("names");


}


void MainWindow::on_pushButton_remove_clicked()
{
    // get value from QT lineEdit
    bool ok;
    int index = ui->lineEdit_index->text().toUInt(&ok,10);
    //get size of list
    int count =emp->get_node_list()->count();

  if ((index <= (count-1)) && (index >= 0))
  {
      //call function
      emp->remove_employee(index,emp->get_node_list());
      //qDebug()<<"Remove data done (index :"<<index<<")";
      //emit log("remove employee");


  }

}


void MainWindow::on_textEdit_textChanged()
{


}


void MainWindow::on_pushButton_clean_clicked()
{
    ui->textEdit->clear();
}

