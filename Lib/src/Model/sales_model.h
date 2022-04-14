#ifndef SALES_MODEL_H
#define SALES_MODEL_H

#include <QAbstractListModel>
#include<Lib_global.h>
#include<Data/sales.h>



namespace Model {

class LIB_EXPORT Sales_model : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int ui_Grandtotal READ Grandtotal WRITE setGrandtotal NOTIFY GrandtotalChanged)
    Q_PROPERTY(int ui_Amount READ Amount WRITE setAmount NOTIFY AmountChanged)
    Q_PROPERTY(int ui_Tendered READ getTendered  NOTIFY tenderedChanged)
    Q_PROPERTY(int ui_Profit READ Profit  NOTIFY ProfitChanged)
    Q_PROPERTY(int ui_Change READ getTendered  NOTIFY ChangeChanged)
    Q_PROPERTY(int ui_Discount READ getDiscount WRITE setDiscount NOTIFY DiscountChanged)
public:
    explicit Sales_model(QObject *parent = nullptr);
    enum{
        id,itemname,quantity ,cost ,category,date,total,profit,discount
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;
    void populate(QList<Data::Sale*> &ata);
    bool populate_item(QString id,QString name,QString category,int quantity,int cost, int totalcost,QString Date,QString,QString,int);
    bool populate_item_single(QString id,QString name,QString category,int quantity,int cost, int totalcost,QString Date,QString,QString,int);
    bool update(QString id,int quantity);
    bool Discount(QString id,int q);
    bool Remove(QString id);
    bool clear_data();
    QList<Data::Sale*>getData();
    int Grandtotal();
    void setGrandtotal(unsigned int Grandtotal);

    int Amount() const;
    void setAmount(int Amount);
    int getTendered();
    int Profit();

    int getChange() ;


    unsigned int getDiscount();
    void setDiscount(unsigned int Discount);

signals:
    void GrandtotalChanged();
    void AmountChanged();
    void tenderedChanged();
    void ChangeChanged();
    void ProfitChanged();
    void DiscountChanged();

private:
    QList<Data::Sale*> mData;
    unsigned   int m_Grandtotal;
    unsigned int m_Amount;
    unsigned int tendered;
    unsigned int Change;
    unsigned int mProfit;
    unsigned int _Discount;
};
}
#endif // SALES_MODEL_H
