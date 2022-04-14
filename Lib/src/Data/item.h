#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include<QString>
#include<Lib_global.h>


namespace Data {
class LIB_EXPORT item : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_Name READ Name WRITE setName NOTIFY NameChanged)
    Q_PROPERTY(QString ui_Category READ Category WRITE setCategory NOTIFY CategoryChanged)
    Q_PROPERTY(int ui_Quantity READ Quantity WRITE setQuantity NOTIFY QuantityChanged)
    Q_PROPERTY(int ui_Price READ Price WRITE setPrice NOTIFY PriceChanged)
    Q_PROPERTY(int ui_id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int ui_Wholesaleprice READ Wholesaleprice WRITE setWholesaleprice NOTIFY WholesalepriceChanged)
    Q_PROPERTY(int ui_Profit READ Profit WRITE setProfit NOTIFY ProfitChanged)
    Q_PROPERTY(int ui_Maxdiscount READ Maxdiscount WRITE setMaxdiscount NOTIFY MaxdiscountChanged)
public:
    explicit item(QObject *parent = nullptr);
    item(int id,QString name,QString category,int quantity,int price, int _Wholesaleprice,int _Profit,int _Maxdiscount);

    QString Name() const;
    void setName(const QString &Name);

    QString Category() const;
    void setCategory(const QString &Category);

    int Quantity() const;
    void setQuantity(int Quantity);

    int Price() const;
    void setPrice(int Price);

    int id() const;
    void setId(int id);

    int Wholesaleprice() const;
    void setWholesaleprice(int Wholesaleprice);

    int Profit() const;
    void setProfit(int Profit);

    int Maxdiscount() const;
    void setMaxdiscount(int Maxdiscount);

signals:
    void NameChanged();
    void CategoryChanged();
    void QuantityChanged();
    void MaxdiscountChanged();
    void PriceChanged();
    void idChanged();
    void WholesalepriceChanged();
    void ProfitChanged();
private:
    int _id;
    QString _Name;
    QString _Category;
    int _Quantity;
    int _Price;
    int _Wholesaleprice;
    int _Profit;
    int _Maxdiscount;

};
}
#endif // ITEM_H
