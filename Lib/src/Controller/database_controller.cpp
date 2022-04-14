#include <Controller/database_controller.h>
#include<QtDebug>
#include<QJsonArray>
#include<QJsonObject>
#include<QSqlError>
#include<iostream>
namespace Controller {

Database_controller::Database_controller(QObject *parent):Main_DatabaseController(parent)
{
    m_databaseconnected=false;
    if(databaseinitialization()){
        if(createTable()){
            qDebug() << "Database tables created";
            emit dbconnected(true);
        }
        else{
            qDebug() << "ERROR: Unable to create database tables";
        }
    }
    else {
        qDebug() << "ERROR: Unable to open database";
    }
}

bool Database_controller::CreatetableRow(QString data) const
{
    QSqlQuery query(db);

    QString sqlstatement="INSERT INTO tables (Noid) VALUES(:data)";
    if(!query.prepare(sqlstatement)) return  false;
    query.bindValue(":data",QVariant(data));
    if(!query.exec()) return  false;
    return  query.numRowsAffected()>0;
}

QStringList Database_controller::logincheck(QString username, QString password)
{
    QCryptographicHash hash(QCryptographicHash::Md4);
    QByteArray pass=password.toLocal8Bit();
    hash.addData(QByteArray(pass));
    auto dbpass=hash.result();

    QStringList data;
    data.clear();
    QSqlQuery query(db);
    QString sql="SELECT * FROM employee WHERE username=:username AND password=:password;";
    if(!query.prepare(sql)) return {};
    query.bindValue(":username",QVariant(username).toString());
    query.bindValue(":password",QVariant(dbpass).toString());
    if(!query.exec()) return {};
    while (query.next()) {
        data.append(QVariant(query.value(0)).toString());
        data.append(query.value(1).toString());
        data.append(query.value(7).toString());
    }

    return data;
}

QList<Data::Sale *> Database_controller::Read_Sales(QString dbname)
{
    //QString id,QString name,QString category,int quantity,int cost, int totalcost,QString Date
    QList<Data::Sale*> data;
    data.empty();
    QSqlQuery query(db);
    QString sql="Select * from :dbname;";
    if(!query.prepare(sql)) return {};
    query.bindValue(":dbname",QVariant(dbname).toString());
    if(!query.exec()) return {};
    while (query.next()) {
        data.append (new Data::Sale(
                         query.value(0).toString(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toInt(),
                         query.value(5).toInt(),
                         query.value(6).toString(),
                         query.value(7).toString(),
                         query.value(8).toString(),
                         query.value(9).toInt()

                         ));
    }
    return data;
}

QList<Data::item *> Database_controller::Read_Stock(QString dbname)
{
    Q_UNUSED(dbname);
    QList<Data::item*> data;
    data.empty();
    QSqlQuery query(db);
    QString sql="Select * from stock";
    if(!query.prepare(sql)) return {};
    if(!query.exec()) return {};
    //id name categ qnt price
    while (query.next()) {
        data.append (new Data::item(
                         QVariant( query.value(0)).toInt(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toInt(),
                         query.value(5).toInt(),
                         query.value(4).toInt()-query.value(5).toInt(),
                           query.value(6).toInt()
                         ));
    }
    return data;
}

QList<Data::item *> Database_controller::Read_Inventory(int id)
{
    QList<Data::item*> data;
    data.empty();
    QSqlQuery query(db);
    if(id!=0){
        QString sql="Select * from stock where id=:id";
        if(!query.prepare(sql)) return {};
        query.bindValue(":id",id);
    }
    else {
        QString sql="Select * from stock";
        if(!query.prepare(sql)) return {};
    }

    if(!query.exec()) return {};
    //id name categ qnt price
    while (query.next()) {
        data.append (new Data::item(
                         QVariant( query.value(0)).toInt(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toInt(),
                         query.value(5).toInt(),
                         query.value(3).toInt()*query.value(4).toInt(),
                         query.value(6).toInt()
                         ));
    }
    return data;
}

QList<Data::Sale *> Database_controller::Read_Returns(QString dbname)
{
    QList<Data::Sale*> data;
    data.empty();
    QSqlQuery query(db);
    QString sql="Select * from :dbname;";
    if(!query.prepare(sql)) return {};
    query.bindValue(":dbname",QVariant(dbname).toString());
    if(!query.exec()) return {};
    while (query.next()) {
        data.append (new Data::Sale(
                         query.value(0).toString(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toInt(),
                         query.value(5).toInt(),
                         query.value(6).toString(),
                         query.value(7).toString(),
                         query.value(8).toString(),
                         query.value(9).toInt()
                         ));
    }
    return data;
}

QList<Data::Sale *> Database_controller::Read_MostSold(QString dbname)
{
    QList<Data::Sale*> data;
    data.empty();
    QSqlQuery query(db);
    QString sql="Select * from :dbname;";
    if(!query.prepare(sql)) return {};
    query.bindValue(":dbname",QVariant(dbname).toString());
    if(!query.exec()) return {};
    while (query.next()) {
        data.append (new Data::Sale(
                         query.value(0).toString(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toInt(),
                         query.value(5).toInt(),
                         query.value(6).toString(),
                         query.value(7).toString(),
                         query.value(8).toString()
                         ,   query.value(9).toInt()
                         ));
    }
    return data;
}

QList<Data::Sale *> Database_controller::Read_Sales_month(QString dbname)
{

    QString datem=QDate::currentDate().toString("M/yyyy");
    QList<Data::Sale*> data;
    data.empty();
    QSqlQuery query(db);
    QString sql="Select * from :dbname where date=:date;";
    if(!query.prepare(sql)) return {};
    query.bindValue(":dbname",QVariant(dbname).toString());
    query.bindValue(":date",QVariant("% "+datem.toLower()+"%"));
    if(!query.exec()) return {};
    while (query.next()) {
        data.append (new Data::Sale(
                         query.value(0).toString(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toInt(),
                         query.value(5).toInt(),
                         query.value(6).toString(),
                         query.value(7).toString(),
                         query.value(8).toString()
                         ,   query.value(9).toInt()
                         ));
    }
    return data;
}

QList<Data::Sale *> Database_controller::Read_Sales_items(int id, int index)
{//QString sql="select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id;";
    QList<Data::Sale*> data;
    data.empty();
    QSqlQuery query(db);
    if(id!=0 && index==0){
        QString stest="select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id where sai.sales_id=:id;";
        if(!query.prepare(stest))return {};
        query.bindValue(":id",id);
    }
    else if(index==0){
        QString stest="select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id where slp.sales_time::date =:date::date";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==1){
        QString stest="select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id where slp.sales_time::date = :date::date -'1 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==2){
        QString stest="select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id where slp.sales_time::date <= :date::date AND slp.sales_time::date >=:date::date -'7 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==3){
        QString stest=" select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id where slp.sales_time::date <= :date::date AND slp.sales_time::date >=:date::date -'30 day'::interval ";

        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==4){
        QString stest="select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE slp.sales_time>=date_trunc('month',current_date) AND slp.sales_time<=date_trunc('month',current_date)+'1 month'::interval; ";

        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==5){
        QString stest="select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE slp.sales_time>=date_trunc('year',current_date) AND slp.sales_time<=date_trunc('year',current_date)-'1 year'::interval ; ";
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==6){
        QString stest="select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE slp.sales_time<=date_trunc('year',current_date) AND slp.sales_time>=date_trunc('year',current_date)-'2 year'::interval;";

        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else{
        QString stest="select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id";
        if(!query.prepare(stest))return {};
    }

    if(!query.exec()) return {};
    while (query.next()) {
        data.append (new Data::Sale(
                         query.value(0).toString(),//id
                         query.value(1).toString(),//name
                         query.value(2).toString(),//category
                         query.value(3).toInt(),//quantity
                         query.value(2).toInt(),//cost
                         query.value(5).toInt(),//totalcost
                         query.value(6).toString(),//date
                         query.value(4).toString(),//user
                         query.value(4).toString(),//payment
                         query.value(4).toInt()//profit
                         ));
    }

    return data;

}




QList<Data::Return *> Database_controller::read_Sales_report(int id, int index)
{
    QList<Data::Return *> data;
    data.clear();
    QSqlQuery query(db);

    //"Today","Yesterday","Last 7 Days","Last 30 Days","Current Month","Current Year","Last Year"]
    if(id!=0 && index==0){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sa.id=:id;";
        if(!query.prepare(stest))return {};
        query.bindValue(":id",id);
    }
    else if(index==0){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date =:date::date";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==1){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date = :date::date -'1 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==2){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date <= :date::date AND sap.sales_time::date >=:date::date -'7 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==3){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date <= :date::date AND sap.sales_time::date >=:date::date -'30 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==4){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id WHERE sap.sales_time>=date_trunc('month',current_date) AND sap.sales_time<=date_trunc('month',current_date)+'1 month'::interval; ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==5){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id WHERE sap.sales_time<=date_trunc('year',current_date)+'1 year'::interval AND sap.sales_time>=date_trunc('year',current_date); ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==6){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id WHERE  sap.sales_time>date_trunc('year',current_date)-'2 year'::interval AND sap.sales_time<date_trunc('year',current_date); ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else{
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id ";
        if(!query.prepare(stest))return {};
    }
    if(!query.exec()) return {};
    while (query.next()) {
        data.append(new Data::Return(
                        query.value(0).toInt(),
                        query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toInt(),
                        query.value(4).toString(),
                        query.value(5).toInt())
                    );
    }
    return data;
}

QList<Data::Return *> Database_controller::read_mostsold_report(int id,int index)
{//order by sap.profit , sap.amount limit 50
    QList<Data::Return *> data;
    data.clear();
    QSqlQuery query(db);

    if(id!=0 && index==0){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sa.id=:id order by sap.profit , sap.amount limit 50;";
        if(!query.prepare(stest))return {};
        query.bindValue(":id",id);
    }
    else if(index==0){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date =:date::date order by sap.profit , sap.amount limit 50";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==1){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date = :date::date -'1 day'::interval order by sap.profit , sap.amount limit 50 ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==2){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date <= :date::date AND sap.sales_time::date >=:date::date -'7 day'::interval order by sap.profit , sap.amount limit 50 ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==3){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date <= :date::date AND sap.sales_time::date >=:date::date -'30 day'::interval order by sap.profit , sap.amount limit 50";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==4){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id WHERE sap.sales_time>=date_trunc('month',current_date) AND sap.sales_time<=date_trunc('month',current_date)+'1 month'::interval order by sap.profit , sap.amount limit 50; ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==5){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id WHERE sap.sales_time<=date_trunc('year',current_date)+'1 year'::interval AND sap.sales_time>=date_trunc('year',current_date) order by sap.profit , sap.amount limit 50;";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==6){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id WHERE sap.sales_time>date_trunc('year',current_date)-'2 year'::interval AND sap.sales_time<date_trunc('year',current_date) order by sap.profit , sap.amount limit 50";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else{
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id ";
        if(!query.prepare(stest))return {};
    }

    if(!query.exec()) return {};
    while (query.next()) {
        data.append(new Data::Return(
                        query.value(0).toInt(),
                        query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toInt(),
                        query.value(4).toString(),
                        query.value(5).toInt())
                    );
    }
    return data;
}

QList<Data::Return *> Database_controller::read_returns_report(int id, int index)
{
    QList<Data::Return *> data;
    data.clear();
    QSqlQuery query(db);


    if(id!=0 && index==0){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sa.id=:id order by sap.profit , sap.amount limit 50;";
        if(!query.prepare(stest))return {};
        query.bindValue(":id",id);
    }
    else if(index==0){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date =:date::date order by sap.profit , sap.amount limit 50";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==1){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date = :date::date -'1 day'::interval  ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==2){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date <= :date::date AND sap.sales_time::date >=:date::date -'7 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==3){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id where sap.sales_time::date <= :date::date AND sap.sales_time::date >=:date::date -'30 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==4){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id WHERE sap.sales_time>=date_trunc('month',current_date) AND sap.sales_time<=date_trunc('month',current_date)+'1 month'::interval ; ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==5){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id WHERE sap.sales_time>date_trunc('year',current_date)-'2 year'::interval AND sap.sales_time<date_trunc('year',current_date);";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==6){
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id WHERE sap.sales_time>date_trunc('year',current_date)-'2 year'::interval AND sap.sales_time<date_trunc('year',current_date);";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else{
        QString stest="SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id ";
        if(!query.prepare(stest))return {};
    }
    if(!query.exec()) return {};
    while (query.next()) {
        data.append(new Data::Return(
                        query.value(0).toInt(),
                        query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toInt(),
                        query.value(4).toString(),
                        query.value(5).toInt())
                    );
    }
    return data;
}
QList<Data::Expenses *> Database_controller::read_expensis(int id, int index)
{QList<Data::Expenses*>data;
    data.empty();
    QSqlQuery query(db);
    if(id!=0 && index==0){
        QString stest="SELECT exp.id,exp.description,exp.date,us.fname,us.lname,exp.amount from expensis exp JOIN employee us on  us.id= exp.employee_id  where exp.id=:uid";
        if(!query.prepare(stest))return {};
        query.bindValue(":uid",id);
    }
    else if(index==0){
        QString stest="SELECT exp.id,exp.description,exp.date,us.fname,us.lname,exp.amount from expensis exp JOIN employee us on  us.id= exp.employee_id WHERE exp.date::date =:date::date ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==1){
        QString stest="SELECT exp.id,exp.description,exp.date,us.fname,us.lname,exp.amount from expensis exp JOIN employee us on  us.id= exp.employee_id WHERE exp.date::date = :date::date -'1 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==2){
        QString stest="SELECT exp.id,exp.description,exp.date,us.fname,us.lname,exp.amount from expensis exp JOIN employee us on  us.id= exp.employee_id WHERE exp.date::date <= :date::date AND exp.date::date >=:date::date -'7 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==3){
        QString stest="SELECT exp.id,exp.description,exp.date,us.fname,us.lname,exp.amount from expensis exp JOIN employee us on  us.id= exp.employee_id WHERE exp.date::date <= :date::date AND exp.date::date >=:date::date -'30 day'::interval ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==4){
        QString stest="SELECT exp.id,exp.description,exp.date,us.fname,us.lname,exp.amount from expensis exp JOIN employee us on  us.id= exp.employee_id WHERE exp.date>=date_trunc('month',current_date) AND exp.date<=date_trunc('month',current_date)+'1 month'::interval; ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==5){
        QString stest="SELECT exp.id,exp.description,exp.date,us.fname,us.lname,exp.amount from expensis exp JOIN employee us on  us.id= exp.employee_id WHERE exp.date<=date_trunc('year',current_date)+'1 year'::interval AND exp.date>=date_trunc('year',current_date); ";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==6){
        QString stest="SELECT exp.id,exp.description,exp.date,us.fname,us.lname,exp.amount from expensis exp JOIN employee us on  us.id= exp.employee_id WHERE exp.date>date_trunc('year',current_date)-'2 year'::interval AND exp.date<date_trunc('year',current_date);";
        if(!query.prepare(stest))return {};
        query.bindValue(":date",QDateTime::currentDateTime());
    }
    else{
        QString stest="SELECT exp.id,exp.description,exp.date,us.fname,us.lname,exp.amount from expensis exp JOIN employee us on  us.id= exp.employee_id";
        if(!query.prepare(stest))return {};
        if(!query.exec()){};
    }

    if(!query.exec()) return {};
    while (query.next()) {
        data.append(new Data::Expenses(
                        query.value(2).toDate(),
                        query.value(1).toString(),
                        query.value(5).toFloat(),
                        query.value(0).toString(),
                        query.value(3).toString()+" "+query.value(4).toString()
                        ));
    }
    return data;


}

bool Database_controller::write_expensis(QString _Date, QString _Description, QString _Amount, int _Employee)
{
    QSqlQuery _query(db);
    _query.prepare("select * from expensis");
    _query.exec();
    int index=_query.numRowsAffected()+1;

    //id BIGSERIAL primary key ,Description text,date timestamp,employee_id bigint REFERENCES employee(id),Amount decimal
    QSqlQuery query(db);
    QString sql="INSERT INTO  expensis VALUES(:id,:des,:date,:emp,:amt);";
    if(!query.prepare(sql))return {};
    query.bindValue(":id",index);
    query.bindValue(":date",_Date);
    query.bindValue(":des",_Description);
    query.bindValue(":amt",_Amount);
    query.bindValue(":emp",QVariant(_Employee).toInt());
    if(!query.exec()) return {};
    return true;

}

QJsonArray Database_controller::readProfitLoss(int id, int index)
{
    Q_UNUSED(id)
    QJsonArray array;
    array.empty();
    QSqlQuery equery(db);
    QSqlQuery iquery(db);
    QSqlQuery squery(db);
    QSqlQuery dquery(db);
    if(index==0){
        QString expensis="SELECT SUM(amount) from expensis WHERE date::date=:date::date ";
        QString inventory="SELECT SUM(price) from stock  ";
        QString sales="SELECT SUM(sai.profit) from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE sales_time::date =:date::date ";
        QString discount="SELECT SUM(amount) from discount  WHERE date::date =:date::date ";
        if(!equery.prepare(expensis))return {};
        if(!squery.prepare(sales))return {};
        if(!iquery.prepare(inventory))return {};
        if(!dquery.prepare(discount))return {};
        equery.bindValue(":date",QDateTime::currentDateTime());
        iquery.bindValue(":date",QDateTime::currentDateTime());
        squery.bindValue(":date",QDateTime::currentDateTime());
        dquery.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==1){
        QString expensis="SELECT SUM(amount) from expensis WHERE date::date = :date::date -'1 day'::interval ";
        QString inventory="SELECT SUM(price) from stock  ";
        QString sales="SELECT SUM(sai.profit) from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE sales_time::date= :date::date -'1 day'::interval ";
        QString discount="SELECT SUM(amount) from discount  WHERE date::date= :date::date -'1 day'::interval ";
        if(!equery.prepare(expensis))return {};
        if(!squery.prepare(sales))return {};
        if(!iquery.prepare(inventory))return {};
        if(!dquery.prepare(discount))return {};
        equery.bindValue(":date",QDateTime::currentDateTime());
        iquery.bindValue(":date",QDateTime::currentDateTime());
        squery.bindValue(":date",QDateTime::currentDateTime());
        dquery.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==2){
        QString expensis="SELECT SUM(amount) from expensis WHERE date::date <= :date::date AND date::date >=:date::date -'7 day'::interval ";
        QString inventory="SELECT SUM(price) from stock ";
        QString sales="SELECT SUM(sai.profit) from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE sales_time::date <= :date::date AND sales_time::date >=:date::date -'7 day'::interval  ";
        QString discount="SELECT SUM(amount) from discount  WHERE date::date <= :date::date AND date::date >=:date::date -'7 day'::interval  ";
        if(!equery.prepare(expensis))return {};
        if(!squery.prepare(sales))return {};
        if(!iquery.prepare(inventory))return {};
        if(!dquery.prepare(discount))return {};
        equery.bindValue(":date",QDateTime::currentDateTime());
        iquery.bindValue(":date",QDateTime::currentDateTime());
        squery.bindValue(":date",QDateTime::currentDateTime());
        dquery.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==3){
        QString expensis="SELECT SUM(amount) from expensis WHERE date::date <= :date::date AND date::date >=:date::date -'30 day'::interval ";
        QString inventory="SELECT SUM(price) from stock";
        QString sales="SELECT SUM(sai.profit) from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE sales_time::date <= :date::date AND sales_time::date >=:date::date -'30 day'::interval  ";
        QString discount="SELECT SUM(amount) from discount  WHERE date::date <= :date::date AND date::date >=:date::date -'30 day'::interval";
        if(!equery.prepare(expensis))return {};
        if(!squery.prepare(sales))return {};
        if(!iquery.prepare(inventory))return {};
        if(!dquery.prepare(discount))return {};
        equery.bindValue(":date",QDateTime::currentDateTime());
        iquery.bindValue(":date",QDateTime::currentDateTime());
        squery.bindValue(":date",QDateTime::currentDateTime());
        dquery.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==4){
        QString expensis="SELECT SUM(amount) from expensis WHERE date>=date_trunc('month',current_date) AND date<=date_trunc('month',current_date)+'1 month'::interval; ";
        QString inventory="SELECT SUM(price) from stock  ";
        QString sales="SELECT SUM(sai.profit) from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE sales_time>=date_trunc('month',current_date) AND sales_time<=date_trunc('month',current_date)+'1 month'::interval; ";
        QString discount="SELECT SUM(amount) from discount  WHERE date>=date_trunc('month',current_date) AND date<=date_trunc('month',current_date)+'1 month'::interval;";
        if(!equery.prepare(expensis))return {};
        if(!squery.prepare(sales))return {};
        if(!iquery.prepare(inventory))return {};
        if(!dquery.prepare(discount))return {};
        equery.bindValue(":date",QDateTime::currentDateTime());
        iquery.bindValue(":date",QDateTime::currentDateTime());
        squery.bindValue(":date",QDateTime::currentDateTime());
        dquery.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==5){
        QString expensis="SELECT SUM(amount) from expensis WHERE date<=date_trunc('year',current_date)+'1 year'::interval AND date>=date_trunc('year',current_date); ";
        QString inventory="SELECT SUM(price) from stock ";
        QString sales="SELECT SUM(sai.profit) from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE sales_time<=date_trunc('year',current_date)+'1 year'::interval AND sales_time>=date_trunc('year',current_date); ";
        QString discount="SELECT SUM(amount) from discount  WHERE date<=date_trunc('year',current_date)+'1 year'::interval AND date>=date_trunc('year',current_date);";
        if(!equery.prepare(expensis))return {};
        if(!squery.prepare(sales))return {};
        if(!iquery.prepare(inventory))return {};
        if(!dquery.prepare(discount))return {};
        equery.bindValue(":date",QDateTime::currentDateTime());
        iquery.bindValue(":date",QDateTime::currentDateTime());
        squery.bindValue(":date",QDateTime::currentDateTime());
        dquery.bindValue(":date",QDateTime::currentDateTime());
    }
    else if(index==6){
        QString expensis="SELECT SUM(amount) from expensis WHERE date>date_trunc('year',current_date)-'2 year'::interval AND date<date_trunc('year',current_date);";
        QString inventory="SELECT SUM(price) from stock  ";
        QString sales="SELECT SUM(sai.profit) from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id WHERE sales_time>date_trunc('year',current_date)-'2 year'::interval AND sales_time<date_trunc('year',current_date);";
        QString discount="SELECT SUM(amount) from discount  WHERE date>date_trunc('year',current_date)-'2 year'::interval AND date<date_trunc('year',current_date);";
        if(!equery.prepare(expensis))return {};
        if(!squery.prepare(sales))return {};
        if(!iquery.prepare(inventory))return {};
        if(!dquery.prepare(discount))return {};
        equery.bindValue(":date",QDateTime::currentDateTime());
        iquery.bindValue(":date",QDateTime::currentDateTime());
        squery.bindValue(":date",QDateTime::currentDateTime());
        dquery.bindValue(":date",QDateTime::currentDateTime());
    }
    else{
        QString expensis="SELECT SUM(amount) from expensis";
        QString inventory="SELECT SUM(price) from stock ";
        QString sales="SELECT SUM(sai.profit) from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id";
        QString discount="SELECT SUM(amount) from discount";
        if(!equery.prepare(expensis))return {};
        if(!squery.prepare(sales))return {};
        if(!iquery.prepare(inventory))return {};
        if(!dquery.prepare(discount))return {};
        equery.bindValue(":date",QDateTime::currentDateTime());
        iquery.bindValue(":date",QDateTime::currentDateTime());
        squery.bindValue(":date",QDateTime::currentDateTime());
        dquery.bindValue(":date",QDateTime::currentDateTime());
    }

    equery.exec();
    iquery.exec();
    squery.exec();
    dquery.exec();
    while (equery.next()) {
        array.append(equery.value(0).toDouble());

    }
    while (iquery.next()) {
       array.append(iquery.value(0).toDouble());

    }
    while (squery.next()) {
        array.append(squery.value(0).toDouble());

    }
    while (dquery.next()) {
        array.append(dquery.value(0).toDouble());

    }
    //expensis stocls sales discount
    return array;
}

bool Database_controller::PushDiscount(int saleid, int userid, int amount, QString date)
{
    QSqlQuery _query(db);
    _query.prepare("select * from discount");
    _query.exec();
    int index=_query.numRowsAffected()+1;

    QSqlQuery query(db);
    QString sql="insert into discount VALUES(:id,:saleid,:emp,:amount,:date)";
    query.prepare(sql);
    query.bindValue(":id",index);
    query.bindValue(":saleid",saleid);
    query.bindValue(":emp",userid);
    query.bindValue(":amount",amount);
    query.bindValue(":date",date);
    if(!query.exec())return false;
    return true;

}

bool Database_controller::Csvread_mostsold_report()
{
    QSqlQuery query(db);
    QString stest="COPY(SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id) TO 'C:\\Users\\Public\\Documents\\Most_Sold.csv' DELIMITER ',' CSV HEADER ";
    if(!query.prepare(stest))return {};
    if(!query.exec()) return {};
    return true;
}

bool Database_controller::Csvread_returns_report()
{
    QSqlQuery query(db);

    QString stest="COPY (SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM returns sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id) TO 'C:\\Users\\Public\\Documents\\Returns.csv' DELIMITER ',' CSV HEADER ";
    if(!query.prepare(stest))return {};

    if(!query.exec()) return {};
    return true;
}

bool Database_controller::Csvread_Sales_report()
{
    QSqlQuery query(db);

    QString stest="COPY (SELECT sa.id ,emp.fname,sap.sales_time,sap.amount,sap.sale_type,sap.profit  FROM sales sa inner JOIN sales_items sai on sa.id=sai.id inner JOIN sales_payment sap on sa.id=sap.id inner JOIN employee emp on sa.employee_id=emp.id) TO 'C:\\Users\\Public\\Documents\\Sales.csv' DELIMITER ',' CSV HEADER ";
    if(!query.prepare(stest))return {};
    if(!query.exec()) return {};
    return true;
}

bool Database_controller::Export_toCsv_SalesDetails()
{
    QSqlQuery query(db);
    QString sql="COPY (select sai.sales_id,st.name,st.price,sai.quantity,sai.profit,sai.cost,slp.sales_time from sales_items sai join stock st on sai.item_id= st.id  join sales_payment slp on slp.sales_id=sai.sales_id ) TO 'C:\\Users\\Public\\Documents\\Sales_Details.csv' DELIMITER ',' CSV HEADER";
    if(!query.prepare(sql))return {};
    if(!query.exec()) return {};
    return true;
}

QList<Data::Employee_D *> Database_controller::readEmployee()
{

    QList<Data::Employee_D *>data;
    data.clear();
    QSqlQuery query(db);
    QString sql="Select * from employee";
    if(!query.prepare(sql)) return {};
    if(!query.exec()) return {};
    while (query.next()) {
        data.append (new Data::Employee_D(
                         query.value(0).toInt(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(5).toString(),
                         query.value(8).toString(),
                         query.value(6).toString(),
                         query.value(3).toString(),
                         query.value(4).toString(),
                         query.value(7).toString()
                         ));
    }

    return data;


}
bool Database_controller::remove_employee(int id)
{
    QString sql=" DELETE FROM employee WHERE id=:text;";
    QSqlQuery query(db);
    if(!query.prepare(sql)) {};
    query.bindValue(":text",id);
    if(!query.exec()){};
    return true;
}

bool Database_controller::update_employee(int id, QString fname, QString gender, QString lname, QString role, QString email, QString username, QString password,QString Phone)
{
    QCryptographicHash hash(QCryptographicHash::Md4);
    QByteArray pass=password.toLocal8Bit();
    hash.addData(QByteArray(pass));
    auto dbpass=hash.result();

    QSqlQuery query(db);
    QString sql="UPDATE employee SET fname=:fname ,lname=:lname, gender=:gender, role=:role, email=:email,username=:username,password=:password,phone=:phone WHERE id=:id";
    if(!query.prepare(sql)) return  false;
    query.bindValue(":id",id);
    query.bindValue(":fname",fname);
    query.bindValue(":lname",lname);
    query.bindValue(":gender",gender);
    query.bindValue(":role",role);
    query.bindValue(":email",email);
    query.bindValue(":username",username);
    query.bindValue(":password",QVariant(dbpass).toString());
    query.bindValue(":phone",Phone);
    if(!query.exec()) return false;
    return  true;
}

bool Database_controller::push_employee(QString fname, QString gender, QString lname, QString role, QString email, QString username, QString password,QString phone)
{
    QSqlQuery _query(db);
    _query.prepare("select * from employee");
    _query.exec();
    int index=_query.numRowsAffected()+2;


    QCryptographicHash hash(QCryptographicHash::Md4);
    QByteArray pass=password.toLocal8Bit();
    hash.addData(QByteArray(pass));
    auto dbpass=hash.result();
    qDebug()<<QVariant(dbpass).toString();


    QSqlQuery query(db);
    QString sql="INSERT INTO employee VALUES(:id,:fname ,:lname,:username,:password,:email,:gender,:role,:phone)";
    if(!query.prepare(sql)) return  false;
    query.bindValue(":id",index);
    query.bindValue(":fname",fname);
    query.bindValue(":lname",lname);
    query.bindValue(":gender",gender);
    query.bindValue(":role",role);
    query.bindValue(":email",email);
    query.bindValue(":username",username);
    query.bindValue(":password",QVariant(dbpass).toString());
    query.bindValue(":phone",phone);
    if(!query.exec()) return false;
    return  true;
}

QList<Data::Employee_D *> Database_controller::search_employee(QString text)
{
    qDebug()<<text;
    QList<Data::Employee_D *>data;
    data.clear();
    QSqlQuery query(db);
    QString sql="Select * from employee WHERE fname like :text OR lname like :text OR username like :text OR email like :text OR gender like :text OR phone like :text ";
    if(!query.prepare(sql)) return {};
    query.bindValue(":text",QVariant("%"+text.toLower()+"%"));
    if(!query.exec()) return {};
    while (query.next()) {
        data.append (new Data::Employee_D(
                         query.value(0).toInt(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(5).toString(),
                         query.value(8).toString(),
                         query.value(6).toString(),
                         query.value(3).toString(),
                         query.value(4).toString(),
                         query.value(7).toString()
                         ));
    }
    qDebug()<<data.count();
    return data;
}

QList<Data::Sale *> Database_controller::Read_Cart(QString dbname)
{
    QList<Data::Sale*> data;
    data.empty();
    QSqlQuery query(db);
    QString sql="Select * from :dbname";
    if(!query.prepare(sql)) return {};
    query.bindValue(":dbname",QVariant(dbname).toString());

    if(!query.exec()) return {};
    while (query.next()) {
        data.append (new Data::Sale(
                         query.value(0).toString(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toInt(),
                         query.value(5).toInt(),
                         query.value(6).toString(),
                         query.value(7).toString(),
                         query.value(8).toString(),
                         query.value(9).toInt()
                         ));
    }
    return data;
}

QList<Data::Sale *> Database_controller::Read_Search(QString dbname, QString searchText)
{

    QList<Data::Sale *>data;
    data.clear();
    QString sql="SELECT * from :dbname Where date=:searchText or id=:searchText or name=:searchText";
    QSqlQuery query(db);
    if(!query.prepare(sql)) return {};
    query.bindValue(":searchText",QVariant("%"+searchText.toLower()+"%"));
    query.bindValue(":dbname",QVariant(dbname).toString());
    if(!query.exec()) return {};
    while (query.next()) {
        data.append (new Data::Sale(
                         query.value(0).toString(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toInt(),
                         query.value(5).toInt(),
                         query.value(6).toString(),
                         query.value(7).toString(),
                         query.value(8).toString(),
                         query.value(9).toInt()
                         ));
    }
    return data;
}

bool Database_controller::update_category(QString old,QString text)
{
    QSqlQuery query(db);
    QString sql="UPDATE stock_category SET category=:text where category=:old;";
    if(!query.prepare(sql)) return {};
    query.bindValue(":text",text);
    query.bindValue(":old",old);
    if(!query.exec()) return {};

    return query.numRowsAffected()>0;
}

QJsonArray Database_controller::read_Category()
{
    QJsonArray data;
    QString sql("SELECT * FROM category");
    QSqlQuery query(db);
    if(!query.prepare(sql)) return {};

    if(!query.exec()) return {};

    while (query.next()) {
        data.append(query.value(0).toString());
    }
    return data;
}

bool Database_controller::drop_category(const QString text)
{
    QString sql=" DELETE FROM  category WHERE category=:text;";
    QSqlQuery query(db);
    if(!query.prepare(sql)) {};
    query.bindValue(":text",text);
    if(!query.exec()){};
    return true;
}
bool Database_controller::add_Category(const QString text)
{
    QString sql="Insert into category VALUES(:text);";
    QSqlQuery query(db);
    if(!query.prepare(sql)) {};
    query.bindValue(":text",text.toLower());
    if(!query.exec()){};
    return true;
}





bool Database_controller::push_Items(QString name, QString category, int quantity, int price, int wholesale, int discount)
{
    QSqlQuery _query(db);
    _query.prepare("select * from stock");
    _query.exec();
    int index=_query.numRowsAffected()+1;

    QString sql="INSERT INTO stock VALUES(:id,:name,:category,:quantity,:price,:wholesale,:discount)";
    QSqlQuery query(db);
    if(!query.prepare(sql)) return {};
    query.bindValue(":id",QVariant(index).toInt());
    query.bindValue(":name",QVariant(name).toString().toLower());
    query.bindValue(":category",QVariant(category).toString().toLower());
    query.bindValue(":quantity",QVariant(quantity).toInt());
    query.bindValue(":price",QVariant(price).toInt());
    query.bindValue(":wholesale",QVariant(wholesale).toInt());
    query.bindValue(":discount",QVariant(discount).toInt());
    if(!query.exec()) return false;

    return true;
}

QList<Data::item *> Database_controller::Read_Stock_Search(QString searchText)
{
    QList<Data::item *>data;
    data.clear();
    QString sql="SELECT * FROM stock WHERE name like :searchText OR category like :searchText ";
    QSqlQuery query(db);
    if(!query.prepare(sql)) return {};
    query.bindValue(":searchText",QVariant("%"+searchText.toLower()+"%"));
    if(!query.exec()) return {};
    while (query.next()){
        data.append (new Data::item(
                         QVariant( query.value(0)).toInt(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toInt(),
                         query.value(5).toInt(),
                         query.value(4).toInt()-query.value(5).toInt(),
                         query.value(6).toInt()

                         ));

    }

    return data;
}

bool Database_controller::import(QString dtable,QString location)
{
    qDebug()<<location;
    QString sql="COPY "+dtable+" FROM '"+location+"' ";
    QSqlQuery query(db);
    if(!query.prepare(sql)) return {};
    query.bindValue(":location",QVariant(location).toString());

    if(!query.exec()) return {};

    return true;
}

bool Database_controller::Export_toCsv()
{
    QSqlQuery query(db);
    QString sql="COPY (Select * from stock ) TO 'C:\\Users\\Public\\Documents\\Inventory.csv' DELIMITER ',' CSV HEADER";
    if(!query.prepare(sql)) return false;

    if(!query.exec()) return 0;
    return true;
}




bool Database_controller::Backupdata(QString dwd)
{
    QSqlQuery query("pg_dump -Fc -f computer.pgsql computer");

    if(!query.exec()) return 0;
    return true;
}

bool Database_controller::RestoreDatabase(QString dwd)
{
    //pg_dump -Fc -f DATABASE.pgsql DATABASE
}

bool Database_controller::createTable()
{
    QSqlQuery query(db);
    QString sql="CREATE TABLE IF NOT EXISTS employee(id BIGINT PRIMARY KEY,fname text,lname text,username text,password bytea,email text,gender text,role int,phone text);";
    QString sql9="CREATE TABLE IF NOT EXISTS sales(id BIGSERIAL not null primary key,employee_id bigint REFERENCES employee(id),customer_id  bigint REFERENCES stock(id),sales_time  timestamp);";
    QString sql3="CREATE TABLE IF NOT EXISTS returns (id BIGSERIAL primary key NOT NULL,name text,category text, quantity smallint, cost smallint,totalcost Bigint,date text,user text, payment text);";
    QString sql2="CREATE TABLE IF NOT EXISTS stock(id BIGSERIAL primary key NOT NULL ,name text, category text, quantity Bigint, price Bigint,wholesaleprice Bigint,discount bigint);";
    QString sql4="CREATE TABLE IF NOT EXISTS users(id SERIAL primary key,firstName text, lastname text,username text,password text,role text);";
    QString sql5="CREATE TABLE category(category text);";
    QString sql6="CREATE TABLE IF NOT EXISTS returns(id  BIGSERIAL   not null,sales_id   bigint References sales(id),sale_type text ,amount   bigint not null, employee_id BIGINT References employee(id),cash_refund   bigint   not null,sales_time text,profit bigint );";
    QString sql7="CREATE TABLE IF NOT EXISTS sales_payment(id BIGSERIAL not null,sales_id   bigint References sales(id),sale_type text,amount bigint,employee_id bigint REFERENCES employee(id),cash_refund bigint,profit bigint,sales_time timestamp);";
    QString sql8="CREATE TABLE IF NOT EXISTS sales_items(id BIGSERIAL not null,sales_id bigint REFERENCES sales(id),item_id bigint REFERENCES stock(id),quantity bigint,cost bigint,unit_price bigint,profit bigint);";
    QString sql10="CREATE TABLE IF NOT EXISTS companyinfo(name text,address text,number text,email text ,policy text);";
    QString sql11="CREATE TABLE  IF NOT EXISTS theme(font text,login text,background text,sale text);";
    QString sql13="CREATE TABLE IF NOT EXISTS Expensis(id BIGSERIAL primary key ,Description text,date timestamp,employee_id bigint REFERENCES employee(id),Amount bigint);";
    QString sql14="CREATE TABLE IF NOT EXISTS Discount(id BIGSERIAL PRIMARY KEY, salesid BIGINT REFERENCES sales(id),employee_id bigint REFERENCES employee(id),amount int,date timestamp)";
    QString sql15="CREATE SELECT 10+20";

    query.exec(sql9);
    query.exec(sql);
    query.exec(sql2);
    query.exec(sql3);
    query.exec(sql4);
    query.exec(sql5);
    query.exec(sql6);
    query.exec(sql7);
    query.exec(sql8);
    query.exec(sql10);
    query.exec(sql11);
    query.exec(sql13);
    query.exec(sql14);
    query.exec(sql15);

    return true;

}

bool Database_controller::push_sales_payment(int sale_id, QString type, int Amount, int employee_id, int refund, QString date,int profit)
{
    QSqlQuery _query(db);
    _query.prepare("select * from sales_payment");
    _query.exec();
    int index=_query.numRowsAffected()+1;

    QSqlQuery query(db);
    QString sql="INSERT INTO sales_payment VALUES(:id,:sales_id,:sale_type,:Amount,:employee_id,:cash_refund,:profit,:sales_time);";
    if(!query.prepare(sql))return false;
    query.bindValue(":id",index);
    query.bindValue(":sales_id",sale_id);
    query.bindValue(":sale_type",type);
    query.bindValue(":Amount",Amount);
    query.bindValue(":employee_id",employee_id);
    query.bindValue(":cash_refund",refund);
    query.bindValue(":sales_time",date);
    query.bindValue(":profit",QVariant(profit));
    if(!query.exec()) return false;
    return  true;
}

bool Database_controller::push_return_payment(int sale_id, QString type, int Amount, int employee_id, int refund, QString date, int profit)
{
    QSqlQuery _query(db);
    _query.prepare("select * from returns");
    _query.exec();
    int index=_query.numRowsAffected()+1;

    QSqlQuery query(db);
    QString sql="INSERT INTO returns VALUES(:id,:sales_id,:sale_type,:Amount,:employee_id,:cash_refund,:sales_time,:profit);";
    if(!query.prepare(sql))return false;
    query.bindValue(":id",index);
    query.bindValue(":sales_id",sale_id);
    query.bindValue(":sale_type",type);
    query.bindValue(":Amount",Amount);
    query.bindValue(":employee_id",employee_id);
    query.bindValue(":cash_refund",refund);
    query.bindValue(":sales_time",date);
    query.bindValue(":profit",QVariant(profit));
    if(!query.exec()) return false;
    return  true;
}

int Database_controller::push_sale(int employee_id, QString sales_time)
{
    QSqlQuery _query(db);
    _query.prepare("select * from sales");
    _query.exec();
    int index=_query.numRowsAffected()+1;

    QSqlQuery query(db);
    QString sql="INSERT INTO sales( id,employee_id,sales_time) VALUES(:id,:employee_id,:sales_time)";
    if(!query.prepare(sql)) return  false;
    query.bindValue(":id",index);
    query.bindValue(":employee_id",employee_id);
    query.bindValue(":sales_time",sales_time);

    if(!query.exec()) return false;
    return  index;
}

bool Database_controller::push_sales_items(int sale_id, int item_id, int qnt, int cost, int unitprice, int profit)
{
    QSqlQuery _query(db);
    _query.prepare("select * from sales_items");
    _query.exec();
    int index=_query.numRowsAffected()+1;

    QSqlQuery query(db);
    QString sql="INSERT INTO sales_items VALUES(:id,:sales_id,:item_id,:quantity,:cost,:unit_price,:profit);";
    if(!query.prepare(sql)) return  false;
    query.bindValue(":id",index);
    query.bindValue(":sales_id",sale_id);
    query.bindValue(":item_id",item_id);
    query.bindValue(":quantity",qnt);
    query.bindValue(":cost",cost);
    query.bindValue(":unit_price",unitprice);
    query.bindValue(":profit",profit);
    if(!query.exec()) return false;
    return  true;

}



bool Database_controller::updatestock(int id, int qnt)
{
    QSqlQuery query(db);
    QString sql="UPDATE stock SET quantity=quantity-:qnt WHERE id=:id";
    if(!query.prepare(sql)) return  false;
    query.bindValue(":id",id);
    query.bindValue(":qnt",qnt);

    if(!query.exec()) return false;
    return  true;

}

bool Database_controller::update_items(int id, const QString name, const QString category, const int quantity, const int price, const int wholesale, int discount)
{
    QSqlQuery query(db);
    QString sql="UPDATE stock SET quantity=:qnt ,name=:name, category=:category, price=:price,wholesaleprice=:wholesale,discount=:discount   WHERE id=:id";
    if(!query.prepare(sql)) return  false;
    query.bindValue(":id",id);
    query.bindValue(":qnt",quantity);
    query.bindValue(":name",name);
    query.bindValue(":category",category);
    query.bindValue(":price",price);
    query.bindValue(":wholesale",wholesale);
    query.bindValue(":discount",discount);

    if(!query.exec()) return false;
    return  true;
}

bool Database_controller::droprow( int id)
{
    QSqlQuery query(db);
    QString sql="DELETE FROM stock WHERE id=:id";
    if(!query.prepare(sql)) return  false;

    query.bindValue(":id",id);

    if(!query.exec()) return false;
    return  true;
}

bool Database_controller::pushthemes(QString font, QString login, QString background, QString sales)
{

    QSqlQuery _query(db);
    _query.prepare("select * from theme");
    _query.exec();
    int index=_query.numRowsAffected();

    QSqlQuery query(db);
    if(index==0){
        QString sql="INSERT INTO theme VALUES(:font,:login,:background,:sale)";
        if(!query.prepare(sql)) return  false;
    }
    else {
        QString sql2="UPDATE theme SET font=:font,login=:login,background=:background,sale=:sale";
        if(!query.prepare(sql2)) return  false;
    }
    query.bindValue(":font",font);
    query.bindValue(":login",login);
    query.bindValue(":background",background);
    query.bindValue(":sale",sales);

    if(!query.exec()) return false;
    return  true;
}

QJsonArray Database_controller::readthemes()
{
    QJsonArray data;
    data.empty();
    QSqlQuery query(db);
    QString sql="SELECT * FROM theme";
    if(!query.prepare(sql)) return  {};
    if(!query.exec()) return {};
    while (query.next()) {
        data.append(query.value(0).toString());
        data.append(query.value(1).toString());
        data.append(query.value(2).toString());
        data.append(query.value(3).toString());
    }
    return data;
}

bool Database_controller::saveCompanyinfor(QString CompanyName, QString CompanyAddress, QString CompanyNumber, QString CompanyEmail, QString Policy)
{
    QSqlQuery _query(db);
    _query.prepare("select * from companyinfo");
    _query.exec();
    int index=_query.numRowsAffected();
    std::cout<<index;
    QSqlQuery query(db);
    if(index==0){
        QString sql="INSERT INTO companyinfo VALUES(:name,:address,:number,:email,:policy)";
        if(!query.prepare(sql)) return  false;
    }
    else {
        QString sql2="UPDATE companyinfo SET name=:name,address=:address,number=:number,email=:email,policy=:policy";
        if(!query.prepare(sql2)) return  false;
    }

    query.bindValue(":name",CompanyName);
    query.bindValue(":address",CompanyAddress);
    query.bindValue(":email",CompanyEmail);
    query.bindValue(":number",CompanyNumber);
    query.bindValue(":policy",Policy);
    if(!query.exec()) return false;
    return  true;
}

QJsonArray Database_controller::ReadCompnayinfor()
{
    QJsonArray data;
    data.empty();
    QSqlQuery query(db);
    QString sql="SELECT * FROM companyinfo";
    if(!query.prepare(sql)) return  {};
    if(!query.exec()) return {};
    while (query.next()) {
        data.append(query.value(0).toString());
        data.append(query.value(1).toString());
        data.append(query.value(2).toString());
        data.append(query.value(3).toString());
        data.append(query.value(4).toString());
    }
    return data;
}

bool Database_controller::databaseinitialization()
{
    db = QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName("DRIVER={PostgreSQL ANSI};SERVER=127.0.0.1;DATABASE=computer");
    db.setUserName("postgres"); // Set Login Username
    db.setPassword("pass");
    db.setPort(5432);
    return db.open();
}


}
