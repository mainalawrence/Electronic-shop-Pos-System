#include "sales_model.h"
#include<QVariant>
#include<QDebug>

using namespace Model;
using namespace Data;


Sales_model::Sales_model(QObject *parent)
    : QAbstractListModel(parent)
{
}




int Sales_model::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid())
        return 0;

    return mData.size();
}

QVariant Sales_model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    auto column=role;
    switch (column) {
    case itemname:{
        return QVariant(mData.at(index.row())->Name()).toString();
        break;
    }
    case quantity:{
        return QVariant(mData.at(index.row())->Quantity()).toInt();
        break;
    }
    case cost:{
        return QVariant(mData.at(index.row())->Cost()).toInt();
        break;
    }
    case category:{
        return QVariant(mData.at(index.row())->Category()).toString();
        break;
    }
    case id:{
        return QVariant(mData.at(index.row())->Id()).toString();
        break;
    }
    case date:{
        return QVariant(mData.at(index.row())->getDate()).toString();
        break;
    }
    case total:{
        return QVariant(mData.at(index.row())->Total_cost()).toInt();
        break;
    }
    case profit:{
        return QVariant(mData.at(index.row())->getProfit()).toInt();
        break;
    }
    case discount:{
        return QVariant(mData.at(index.row())->getDiscount()).toInt();
        break;
    }

    }

    return QVariant();
}

bool Sales_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;

    auto column=role;
    switch (column) {
    case itemname:{
        QVariant(value).toString()=mData.at(index.row())->Name();
        break;
    }
    case quantity:{
        QVariant(value).toString()=mData.at(index.row())->Category();
        break;
    }
    case cost:{
        QVariant(value).toString()=mData.at(index.row())->Cost();
        break;
    }
    case category:{
        QVariant(value).toString()=mData.at(index.row())->Category();
        break;
    }
    case id:{
        QVariant(value).toString()=mData.at(index.row())->Id();
        break;
    }
    case date:{
        QVariant(value).toString()=mData.at(index.row())->getDate();
        break;
    }
    case total:{
        QVariant(value).toString()=mData.at(index.row())->Total_cost();
        break;
    }
    case profit:{
        QVariant(value).toString()=mData.at(index.row())->getProfit();
        break;
    }
    case discount:{
        QVariant(value).toString()=mData.at(index.row())->getDiscount();
        break;
    }
    }

    return true;
}

Qt::ItemFlags Sales_model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> Sales_model::roleNames() const
{
    QHash<int, QByteArray>Names;
    Names.insert(itemname,"name");
    Names.insert(quantity,"quantity");
    Names.insert(cost,"cost");
    Names.insert(category,"category");
    Names.insert(id,"id");
    Names.insert(total,"total");
    Names.insert(date,"date");
    Names.insert(profit,"profit");
    Names.insert(discount,"discount");
    return Names;
}

void Sales_model::populate(QList<Sale*> &data)
{
    mData.empty();
    emit beginResetModel();
    mData=data;
    emit endResetModel();

}

bool Sales_model::populate_item(QString id, QString name, QString category, int quantity, int cost, int totalcost, QString Date, QString user, QString payment, int profit)
{
    int index=mData.size();
    if(mData.isEmpty()){
        emit beginInsertRows(QModelIndex(),index,index);
        mData.append(new Sale(id,name,category,quantity,cost,totalcost,Date,user,payment,profit));
        emit endInsertRows();
        return true;

    }
    else {
        for(auto &d:mData){
            if(id!=d->Id()){
                emit beginInsertRows(QModelIndex(),index,index);
                mData.append(new Sale(id,name,category,quantity,cost,totalcost,Date,user,payment,profit));
                emit endInsertRows();
                return true;

            }
            else {

                return false;
            }
        }
    }


    return true;

}

bool Sales_model::populate_item_single(QString id, QString name, QString category, int quantity, int cost, int totalcost, QString Date,QString user,QString payment,int profit)
{
    mData.clear();
    int index=mData.size();
    emit beginInsertRows(QModelIndex(),index,index);
    mData.append(new Sale(id,name,category,quantity,cost,totalcost,Date,user,payment,profit));
    emit endInsertRows();
    return false;
}

bool Sales_model::update(QString id, int quantity)
{
    for(auto &d:mData)
    {
        if(d->Id()==id){
            emit beginResetModel();
            d->setQuantity(0);
            d->setQuantity(quantity);
            d->setTotal_cost(d->Cost()*quantity);
            d->setTotalDiscount(0);
            emit endResetModel();
        }
    }
    return true;
}

bool Sales_model::Discount(QString id, int discount)
{
    for(auto &d:mData)
    {
        if(d->Id()==id){
            if(d->Quantity()==1){
                emit beginResetModel();

                d->setDiscount(discount);
                emit endResetModel();
            }
            else{
                emit beginResetModel();

                d->setDiscount(discount);
                emit endResetModel();
            }
        }
    }

    return true;
}
bool Sales_model::Remove(QString id)
{
    int index=mData.size()-1;
    emit beginRemoveRows(QModelIndex(),index,index);
    for(int i=0;i<mData.size();i++){
        if(mData[i]->Id()==id){
            mData.removeAt(i);
        }
    }
    emit endRemoveRows();
    return true;
}
bool Sales_model::clear_data()
{
    if(mData.size()<0)return false;
    int index=mData.size()-1;
    for(int i=0;i<=index;i++){
        beginRemoveRows(QModelIndex(),index-i,index-i);
        mData.removeAt(i);
        endRemoveRows();
    }
    return true;
}

QList<Sale *> Sales_model::getData()
{
    return  mData;
}

int Sales_model::Grandtotal()
{
    int tt=0;
    int discount=0;
    for(auto &d:mData){
        tt+=d->Total_cost();
    }
    for(auto &d:mData){
        discount+=d->getDiscount();
    }
    qDebug()<<tt;
    int balance=tt-discount;
    emit GrandtotalChanged();
    return balance;
}

void Sales_model::setGrandtotal(unsigned int Grandtotal)
{
    if(m_Grandtotal != Grandtotal){
        m_Grandtotal = Grandtotal;
        emit GrandtotalChanged();
    }
}

int Sales_model::Amount() const
{
    return mData.count();
}

void Sales_model::setAmount(int Amount)
{
    m_Amount = Amount;
}

int Sales_model::getTendered()
{
    int discount=0,tt=0;
    for(auto &d:mData){
        tt+=d->Total_cost();
    }
    for(auto &d:mData){
        discount+=d->getDiscount();
    }
    qDebug()<<tt;
    int balance=tt-discount;
    emit GrandtotalChanged();
    return balance;
    emit tenderedChanged();
    return balance;
}

int Sales_model::Profit()
{
    int tt=0;
    for(auto &d:mData){
        tt+=d->getProfit();
    }
    emit tenderedChanged();
    return tt;
}

int Sales_model::getChange()
{
    return m_Grandtotal-tendered;
    emit ChangeChanged();
}

unsigned int Sales_model::getDiscount()
{
    int tt=0;
    for(auto &d:mData){
        tt+=d->getDiscount();
    }
    emit DiscountChanged();
    emit GrandtotalChanged();
    return tt;
}

void Sales_model::setDiscount(unsigned int Discount)
{
    if(_Discount != Discount)
    {
        _Discount = Discount;
        emit DiscountChanged();
    }
}


