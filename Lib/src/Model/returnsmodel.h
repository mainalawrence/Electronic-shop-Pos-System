#ifndef RETURNSMODEL_H
#define RETURNSMODEL_H

#include <QAbstractListModel>
#include<Data/return.h>
#include<Lib_global.h>


namespace Model {

class LIB_EXPORT ReturnsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(long ui_mTotalItem READ totalItem WRITE setTotalItem NOTIFY mTotalItemChanged)
    Q_PROPERTY(long ui_mGrandTotal READ grandTotal WRITE setGrandTotal NOTIFY mGrandTotalChanged)
    Q_PROPERTY(long ui_mProfit READ profit WRITE setProfit NOTIFY mProfitChanged)

public:
    explicit ReturnsModel(QObject *parent = nullptr);

    enum{
        id,empname,paytype,date,total,profit_
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool empty_data();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
     QHash<int,QByteArray> roleNames() const override;

     long totalItem() const;
     void setTotalItem(long totalItem);

     long grandTotal() const;
     void setGrandTotal(long grandTotal);

     long profit();
     void setProfit(long profit);
     void populate(QList<Data::Return*> &data);


signals:
     void mTotalItemChanged();
     void mGrandTotalChanged();
     void mProfitChanged();

private:
    QList<Data::Return*> mData;

    long mTotalItem;
    long mGrandTotal;
    long mProfit;
};
}
#endif // RETURNSMODEL_H
