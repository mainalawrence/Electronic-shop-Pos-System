#include "returnsmodel.h"
#include<QtDebug>

namespace Model {
ReturnsModel::ReturnsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mProfit=0;
}

int ReturnsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mData.count();
}

bool ReturnsModel::empty_data()
{
    int index=mData.size();
    for(int i=0;i<=index;i++){
        beginRemoveRows(QModelIndex(),index-i,index-i);
        mData.removeAt(i);
        endRemoveRows();
    }
}

QVariant ReturnsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto  col=role;
    auto row=mData.at(index.row());
    switch (col) {
    case id:{
        return QVariant(row->id()).toString();
        break;
    }
    case empname:{
        return QVariant(row->emp()).toString();
        break;
    }
    case date:{
        return QVariant(row->date()).toString();
        break;
    }
    case paytype:{
        return QVariant(row->paytype()).toString();
        break;
    }
    case total:{
        return QVariant(row->totalCost()).toInt();
        break;
    }
    case profit_:{
        return QVariant(row->profit()).toInt();
        break;
    }
    }
    return QVariant();
}

QHash<int, QByteArray> ReturnsModel::roleNames() const
{

    QHash<int, QByteArray>roles;
    roles.insert(id,"id");
    roles.insert(empname,"empname");
    roles.insert(paytype,"paytype");
    roles.insert(date,"date");
    roles.insert(total,"total");
    roles.insert(profit_,"profit");
    return roles;
}

long ReturnsModel::totalItem() const
{
    return mData.count();
}

void ReturnsModel::setTotalItem(long totalItem)
{
    if(mTotalItem !=totalItem){
        mTotalItem=totalItem;
        emit mTotalItemChanged();
    }
}

long ReturnsModel::grandTotal() const
{
    long total=0;
    for(auto &d:mData){
        total+=d->totalCost();
    }
    return total;
}

void ReturnsModel::setGrandTotal(long grandTotal)
{
    if(mGrandTotal !=grandTotal){
        mGrandTotal=grandTotal;
        emit mGrandTotalChanged();
    }
}

long ReturnsModel::profit()
{
    long profit_=0;
    for(auto &d:mData){
        profit_+=d->profit();
    }
     emit mProfitChanged();
    return profit_;
}

void ReturnsModel::setProfit(long profit)
{
    if(mProfit !=profit){
        mProfit=profit;
        emit mProfitChanged();

    }
}

void ReturnsModel::populate(QList<Data::Return *> &data)
{
    mData.clear();
    emit beginResetModel();
    mData=data;
    endResetModel();
}
}
