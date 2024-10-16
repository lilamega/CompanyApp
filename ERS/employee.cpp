/**
 * @brief Employee class
 * @param parent
 * @param ST
 * @class Employee
 * @file employe.cpp
 */
#include "employee.h"

//Employee::Employee(QObject *parent):QObject(parent)//constructeur, 4eme instruction
Employee::Employee(QObject *parent, EnumST ST):
    QObject(parent),
    m_ST(ST) //save
{    
    // building the list
    nodeList = new QList<node>();
    init_node_list(QDir::toNativeSeparators("C:/Qt/Projects/ERS/records.txt")); //go into w/ the path

    if (m_ST == ST_Agrate)
    {
        qDebug()<<("You are in Agrate ! \n");
    }
    else if (m_ST == ST_Rousset)
    {
        qDebug()<<("You are in Rousset ! \n");
    }
    else if (m_ST == ST_Crolles)
    {
        qDebug()<<("You are in Crolles ! \n");
    }
    else
    {
        qDebug()<<("You are lost !!!! \n");
    }
}

Employee::~Employee()
{

}

void Employee::add_employee(node d, QList<node> *l)
{
    //update list
    // the node is already with values
    l->append(d);


    // update records file
    update_records_file(QDir::toNativeSeparators("C:/Qt/Projects/ERS/records.txt"));
    emit log("add employee : " + d.name  + "," + QString().number(d.age,10) + "," + d.job);


}

void Employee::remove_employee(node d, QList<node> *l)
{
     QString name = d.name;
     uint age = d.age;

     for (int i=0;i<l->count(); i++)
     {
         // extact node by node and put in tempo node
         node n = nodeList->at(i);
         if ((n.name == name) && (n.age == age))
         {
             l->removeAt(i);
         }

     }

    // update records file
    update_records_file(QDir::toNativeSeparators("C:/Qt/Projects/ERS/records.txt"));

}

void Employee::remove_employee(int index, QList<node> *l)
{
    l->removeAt(index);

    // update records file
    update_records_file(QDir::toNativeSeparators("C:/Qt/Projects/ERS/records.txt"));
    emit log("remove employee : index" + QString().number(index,10));


}

void Employee::print_employee_info(QString name, QList<node> *l)
{

    for (int i=0;i<l->count(); i++)
    {
        // extact node by node and put in tempo node
        node n = nodeList->at(i);
        if ((n.name == name))
        {

            emit log("[" + QString().number(i,10) + "]" + n.name  + "," + QString().number(n.age,10) + "," + n.job);

        }
    }
}

void Employee::print_all_employee_name(QList<node> *l)
{

    for (int i=0;i<l->count(); i++)
    {
        // extact node by node and put in tempo node
        node n = nodeList->at(i);


        emit log("[" + QString().number(i,10) + "]" + n.name);
    }

}

void Employee::print_all_employee_info(QList<node> *l)
{

    for (int i=0;i<l->count(); i++)
    {
        // extact node by node and put in tempo node
        node n = nodeList->at(i);
        emit log("[" + QString().number(i,10) + "]" + n.name  + "," + QString().number(n.age,10) + "," + n.job);

    }

}

bool Employee::init_node_list(QString fullFileName)
{
     QFile file(QDir::toNativeSeparators(fullFileName));

     //check if file exist
    if(!file.exists())
    {
        emit log ("record file doesn't exist");
        return false;
    }

    //open file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit log("open file error");
        return false;
    }

    QTextStream in(&file);
    // line by line
    while (!in.atEnd())
    {
        node n;
        bool ok;

        //read file
        QString line = in.readLine();

        //parse file
        QStringList list = line.split(',');

        //fill node
        n.name =list[0];
        n.age = list[1].toInt(&ok,10);
        n.job =list[2];

        // add node to list
        nodeList->append(n);
    }

    //close file
    file.close();
    emit log("node created successufully");

    return true;
}

bool Employee::update_records_file(QString fullFileName)
{
    QFile file(QDir::toNativeSeparators(fullFileName));

    //check if file exist
   if(!file.exists())
   {
       emit log("record file doesn't exist");
       return false;
   }

   //open file
   if (!file.open(QFile::WriteOnly))
   {
       emit log("open file error");
       return false;
   }

   QTextStream in(&file);
   //extact node by node
   for (int i=0;i<nodeList->count(); i++)
   {
       //put in tempo node
       node n = nodeList->at(i);
       //print
       in <<n.name<<","<<QString().number(n.age,10)<<","<<n.job<<"\n";       
   }

   //close file
   file.close();
   emit log("records file updated successfully");
   return true;
}

