#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QList>
#include <QFile>
#include <QDir>
#include <QDebug>

#include <QObject>

/**
 *  @enum EnumST
 *  @brief enum ST sites
 */
//enum creation
typedef enum{
    ST_Rousset, /*! ST Rousset */
    ST_Agrate, /*! ST Agrate */
    ST_Crolles /*! ST Crolles */
}EnumST;

/**
 *  @struct node
 *  @brief 3 parameters to characterize employees
 */typedef struct {

    QString name;
    uint age;
    QString job;
}node;


class Employee : public QObject
{
    Q_OBJECT


public:
    explicit Employee(QObject *parent = nullptr, EnumST ST = ST_Agrate);//construteur, 3nd instruction (go into) //add EnumST parameter
    ~Employee(); //destructeur

    //prototype
    /**
     * @brief add_employee
     * @param caracteristics
     * @param list
     */
    void add_employee(node d, QList<node> *l);
    /**
     * @brief remove_employee
     * @param caracteristics
     * @param list
     */
    void remove_employee(node d, QList<node> *l);
    /**
     * @brief remove_employee
     * @param index
     * @param list
     */
    void remove_employee(int index, QList<node> *l);
    /**
     * @brief print_employee_info
     * @param name
     * @param list
     */
    void print_employee_info(QString name, QList<node> *l);
    /**
     * @brief print_all_employee_name
     * @param list
     */
    void print_all_employee_name(QList<node> *l);
    /**
     * @brief print_all_employee_info
     * @param list
     */
    void print_all_employee_info(QList<node> *l);
    QList<node> *get_node_list(){return nodeList;}

signals:
    void log(QString); //prototype of signal (only)


private:
    bool init_node_list(QString fullFileName);
    bool update_records_file(QString fullFileName);

private:
    QList<node> *nodeList = nullptr;
    // create
    EnumST m_ST;

};


#endif // EMPLOYEE_H
