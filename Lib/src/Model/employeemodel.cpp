#include "employeemodel.h"

namespace Model {
using namespace Data;
EmployeeModel::EmployeeModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int EmployeeModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return  mdata.count();
}

QVariant EmployeeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto column=role;
    auto row=mdata.at(index.row());

    switch (column) {
    case id:{
        return QVariant(row->getId()).toInt();
         break;
    }
    case fname:{
        return QVariant(row->FName()).toString();
         break;
    }
    case lname:{
        return QVariant(row->LName()).toString();
         break;
    }
    case phone:{
        return QVariant(row->Phone()).toString();
         break;
    }
    case gender:{
        return QVariant(row->Gender()).toString();
         break;
    }
    case username:{
        return QVariant(row->Username()).toString();
         break;
    }
    case email:{
        return QVariant(row->Email()).toString();
         break;
    }
    case password:{
        return QVariant(row->PAssword()).toString();
         break;
    }
    case roles:{
        return QVariant(row->Role()).toString();
         break;
    }
    }
    return QVariant();
}

bool EmployeeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        auto column=role;
        auto row=mdata.at(index.row());

        switch (column) {
        case id:{
            QVariant(value).toString()=row->getId();
             break;
        }
        case fname:{
            QVariant(value).toString()=row->FName();
             break;
        }
        case lname:{
            QVariant(value).toString()=row->LName();
             break;
        }
        case phone:{
            QVariant(value).toString()=row->Phone();
            break;
        }
        case gender:{
            QVariant(value).toString()=row->Gender();
             break;
        }
        case username:{
            QVariant(value).toString()=row->Username();
             break;
        }
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags EmployeeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

bool EmployeeModel::removeRow_(int id)
{
    for(int i=0;i<mdata.size();i++){
        if(mdata[i]->getId()==id){
            emit beginRemoveRows(QModelIndex(),i,i);
            emit endRemoveRows();

            break;
        }
    }
    return true;
}

bool EmployeeModel::populate(const QList<Employee_D *> data)
{

    mdata.clear();
    if(!mdata.isEmpty()) return false;
    for(int i=0;i<data.size();i++){
    emit  beginResetModel();
    mdata=data;
    emit endResetModel();
}
    return true;
}
QHash<int, QByteArray> EmployeeModel::roleNames() const
{
    QHash<int, QByteArray>Names;
    Names.insert(fname,"fname");
    Names.insert(lname,"lname");
    Names.insert(id,"id");
    Names.insert(gender,"gender");
    Names.insert(phone,"phone");
    Names.insert(username,"username");
    Names.insert(email,"email");
    Names.insert(password,"password");
    Names.insert(roles,"role");
    return Names;
}
}
