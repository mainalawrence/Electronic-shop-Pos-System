#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H

#include <QAbstractListModel>
#include<QList>
#include<Lib_global.h>
#include<Data/employee.h>

namespace Model {


class LIB_EXPORT EmployeeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum{
        id,fname ,lname ,phone ,gender ,username,password,roles,email
    };
    explicit EmployeeModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool removeRow_(int id);
    bool populate(const QList<Data::Employee_D*>data);


    // Remove data:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Data::Employee_D*>mdata;
};
}
#endif // EMPLOYEEMODEL_H
