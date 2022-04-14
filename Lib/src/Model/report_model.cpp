#include "report_model.h"
#include<QDebug>
#include<QDate>

using namespace Model;
using namespace Data;

Report_Model::Report_Model(QObject *parent)
    : QAbstractListModel(parent)
{

}

int Report_Model::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid())
        return 0;

    return _mData.count();
}

QVariant Report_Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    //itemname quantity cost category
    auto column=role;
    switch (column) {
    case id:{
        return QVariant(_mData.at(index.row())->id()).toInt();
        break;
    }
    case itemname:{
        return QVariant(_mData.at(index.row())->Name()).toString();
        break;
    }

    case quantity:{
        return QVariant(_mData.at(index.row())->Quantity()).toInt();
        break;
    }
    case cost:{
        return QVariant(_mData.at(index.row())->Price()).toInt();
        break;
    }
    case category:{
        return QVariant(_mData.at(index.row())->Category()).toString();
        break;
    }case Wholesaleprice:{
        return QVariant(_mData.at(index.row())->Wholesaleprice()).toInt();
        break;
    }
    case total:{
            return QVariant(_mData.at(index.row())->Profit()).toInt();
            break;
        }
    case maxdiscount:{
        return QVariant(_mData.at(index.row())->Maxdiscount()).toInt();
        break;
    }
    }

    return QVariant();
}

bool Report_Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;
    auto column=role;
    switch (column) {
    case id:{
        QVariant(value).toString()=_mData.at((index.row()))->id();
        break;
    }
    case itemname:{
        QVariant(value).toString()= _mData.at(index.row())->Name();
        break;
    }
        //itemname quantity cost category
    case quantity:{
        QVariant(value).toString()= _mData.at(index.row())->Quantity();

        break;
    }
    case cost:{
        QVariant(value).toString()=_mData.at(index.row())->Price();
        break;
    }
    case category:{

        QVariant(value).toString()=_mData.at(index.row())->Category();
        break;
    }
    case maxdiscount:{
        QVariant(value).toString()=_mData.at(index.row())->Maxdiscount();
        break;
    }

    case Wholesaleprice:{

        QVariant(value).toString()=_mData.at(index.row())->Wholesaleprice();
        break;
    }
    case total:{

        QVariant(value).toString()=_mData.at(index.row())->Profit();
        break;
    }
    }
    return  true;

}

Qt::ItemFlags Report_Model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

bool Report_Model::removeRow_(int id)
{
    for(int i=0;i<_mData.size();i++){
        if(_mData[i]->id()==id){
            emit beginRemoveRows(QModelIndex(),i,i);
            emit endRemoveRows();
            break;
        }
    }

    return true;
}


QHash<int, QByteArray> Report_Model::roleNames() const
{
    QHash<int, QByteArray>Names;
    Names.insert(itemname,"name");
    Names.insert(quantity,"amount");
    Names.insert(cost,"price");
    Names.insert(category,"category");
    Names.insert(id,"id");
    Names.insert(total,"profit");
    Names.insert(Wholesaleprice,"wholesale");
    Names.insert(maxdiscount,"maxdiscount");
    return Names;
}

void Report_Model::populate( QList<item*> &data)
{
    _mData.clear();
    if(!_mData.isEmpty()) qDebug()<<"not emti";
    for(int i=0;i<data.size();i++){
        emit  beginResetModel();
        _mData=data;
        emit endResetModel();

    }
}

long Report_Model::items() const
{
    return _mData.count();
}

long Report_Model::grandtotal() const
{
    long tt=0;
    for(auto &d:_mData){
        tt+=d->Price()*d->Quantity();
    }
    return tt;
}

long Report_Model::profit() const
{
    long prof=0;

    for(auto &d:_mData){
        prof+=d->Price()-d->Wholesaleprice();
    }
    return prof;
}







