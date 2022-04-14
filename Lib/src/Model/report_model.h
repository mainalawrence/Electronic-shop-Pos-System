#ifndef REPORT_MODEL_H
#define REPORT_MODEL_H

#include <QAbstractListModel>
#include<QObject>
#include<Lib_global.h>
#include<Data/item.h>
#include<QList>

namespace Model {
class LIB_EXPORT Report_Model : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(long ui_itemsamount READ items )
    Q_PROPERTY(long ui_grandtotal READ grandtotal)
    Q_PROPERTY(long ui_profit READ profit)
public:
    enum{
        id=0,itemname,quantity ,cost ,category,Wholesaleprice,total,maxdiscount
    };
    explicit Report_Model(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool removeRow_(int id);


    // Remove data:
    QHash<int, QByteArray> roleNames() const override;

     void populate(QList<Data::item*> &data);

     long items() const;

     long grandtotal() const;

     long profit() const;

private:
     QList<Data::item*> _mData;

    long mItems;
    long mGrandtotal;
    long mProfit;

};

}

#endif // REPORT_MODEL_H
