#ifndef EXPENISISMODEL_H
#define EXPENISISMODEL_H

#include <QAbstractListModel>
#include<Lib_global.h>
#include<QList>
#include<Data/expenses.h>
namespace Model {

class LIB_EXPORT ExpenisisModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int ui_size READ getSize WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int ui_total READ getTotal WRITE setTotal NOTIFY totalChanged)

public:
    explicit ExpenisisModel(QObject *parent = nullptr);

    enum{
      id,description,amount,date,employee
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void populate(const QList<Data::Expenses*>data) ;

    QHash<int, QByteArray> roleNames() const override;

    unsigned int getSize();
    unsigned int getTotal() ;
    void setTotal(unsigned int value);
    void setSize(unsigned int value);

signals:
    void totalChanged();
    void sizeChanged();
private:
    QList<Data::Expenses*>_data;
    unsigned int size;
    unsigned int Total;
};
}
#endif // EXPENISISMODEL_H
