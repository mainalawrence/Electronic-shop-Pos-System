#include "expenisismodel.h"


namespace Model {

ExpenisisModel::ExpenisisModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ExpenisisModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return _data.size();
}

QVariant ExpenisisModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto col=_data.at(index.row());
    switch (role) {
    case id:{
        return QVariant(col->UID()).toString();
    }
    case description:{
        return QVariant(col->Description()).toString();
    }
    case amount:{
        return QVariant(col->Amount()).toString();
    }
    case date:{
        return QVariant(col->Date()).toString();
    }
    case employee:{
        return QVariant(col->Employee()).toString();
    }

    }
    return QVariant();
}

void Model::ExpenisisModel::populate(const QList<Data::Expenses *> data)
{
    _data.empty();
    _data.clear();
    emit beginResetModel();
    _data=data;
    emit endResetModel();
}

QHash<int, QByteArray> ExpenisisModel::roleNames() const
{
    QHash<int, QByteArray>roles;
    roles.insert(id,"id");
    roles.insert(description,"description");
    roles.insert(employee,"employee");
    roles.insert(amount,"amount");
    roles.insert(date,"date");
    return roles;
}
unsigned int ExpenisisModel::getSize()
{
    emit sizeChanged();
    return _data.size();
}

unsigned int ExpenisisModel::getTotal()
{
    int tt=0;
    for(auto &d:_data){
        tt+=d->Amount();
    }
    emit totalChanged();
    return tt;
}

void ExpenisisModel::setTotal(unsigned int value)
{
    if(Total != value){
        Total = value;
        emit totalChanged();
    }
}
void ExpenisisModel::setSize(unsigned int value)
{
    if( size != value){
        size = value;
        emit sizeChanged();
    }
}
}
