#ifndef DATABASE_CONTROLLER_H
#define DATABASE_CONTROLLER_H
#include <QObject>
#include<QSql>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QDateTime>
#include<QVariant>
#include<QJsonArray>
#include<QFile>
#include<Controller/Main_Databasecontroller.h>
#include<QCryptographicHash>

#include <Data/sales.h>
#include<Data/item.h>
#include<Data/employee.h>
#include<Data/return.h>
#include<Data/expenses.h>


class Sale;
class item;
class Employee;
class Expensis;
#include<Lib_global.h>

namespace Controller{

class  LIB_EXPORT Database_controller: public Main_DatabaseController
{
    Q_OBJECT
public:
    explicit Database_controller(QObject *parent = nullptr);
    bool CreatetableRow(QString data)const;
    //read from data
    QStringList logincheck(QString ,QString);
    QList<Data::Sale*> Read_Sales(QString dbname);
    QList<Data::item*> Read_Stock(QString dbname);
    QList<Data::item*> Read_Inventory(int id);
    QList<Data::Sale*>Read_Returns(QString dbname);
    QList<Data::Sale*>Read_MostSold(QString dbname);

    //read data with arguemnt
    QList<Data::Sale*> Read_Sales_month(QString dbname);
    QList<Data::Sale*> Read_Sales_items(int id,int index);

    QList<Data::Return*>read_Sales_report(int id,int);

    QList<Data::Return*> read_mostsold_report(int id,int index);
    QList<Data::Return*> read_returns_report(int id,int index);
//get the expensis
    QList<Data::Expenses*>read_expensis(int date,int i);
    bool write_expensis(QString _Date,QString _Description, QString _Amount,int _Employee);

    //read profit and expenisi
    QJsonArray readProfitLoss(int id,int index);
    bool PushDiscount(int saleid,int userid,int amount,QString date);


    //users employee
    QList<Data::Employee_D*> readEmployee();
    bool remove_employee(int id);
    bool update_employee(int id,QString fname,QString gender,QString lname,QString role,QString email,QString username, QString password,QString phone);
    bool push_employee(QString fname,QString gender,QString lname,QString role,QString email,QString username, QString password,QString phone);
    QList<Data::Employee_D *> search_employee(QString text);
    QList<Data::Sale*>Read_Cart(QString dbname);

    //search the database
    QList<Data::Sale*> Read_Search(QString dbname,QString search);

    //category section
    bool update_category(QString old,QString text);
    QJsonArray read_Category();
    bool drop_category(const QString text);
    bool add_Category(const QString text);

    //append in the database
    bool push_Items(QString name,QString category,int quantity,int price,int wholesale,int discount);
    QList<Data::item*> Read_Stock_Search(QString text);
    bool import(QString ,QString location);


    //backing up the database
    bool Csvread_mostsold_report();
    bool Csvread_returns_report();
    bool Csvread_Sales_report();
    bool Export_toCsv_SalesDetails();
    bool Export_toCsv();

    bool Backupdata(QString dwd);
    bool RestoreDatabase(QString dwd);
    bool createTable();

    // save the sales
    bool push_sales_payment(int sale_id,QString type,int Amount,int employee_id,int refund,QString date,int profit);
    bool push_return_payment(int sale_id,QString type,int Amount,int employee_id,int refund,QString date,int profit);



    int push_sale(int employee_id,QString sales_time);
    bool push_sales_items(int sale_id,int item_id,int qnt,int cost ,int unitprice,int profit);
    bool updatestock(int id,int qnt);
    bool update_items(int id, const QString name, const QString category, const int quantity, const int price,const int wholesale,int discount);

    bool droprow(int id);

    //themes and the company information

    bool pushthemes(QString font,QString login,QString background,QString sales);
    QJsonArray readthemes();

    bool saveCompanyinfor( QString CompanyName,QString CompanyAddress,QString CompanyNumber,QString CompanyEmail,QString Policy);
    QJsonArray ReadCompnayinfor();

signals:
    void Databaseconnected();
    void dbconnected(bool);

private:

    QSqlDatabase db;
    bool databaseinitialization();
    bool m_databaseconnected=false;

};
}
#endif // DATABASE_CONTROLLER_H
