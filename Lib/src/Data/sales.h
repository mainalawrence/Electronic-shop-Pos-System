#ifndef SALES_H
#define SALES_H

#include <QObject>
#include<QString>
#include<Lib_global.h>

namespace Data {
class LIB_EXPORT Sale : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_Name READ Name WRITE setName NOTIFY NameChanged)
    Q_PROPERTY(QString ui_Category READ Category WRITE setCategory NOTIFY CategoryChanged)
    Q_PROPERTY(int ui_Quantity READ Quantity WRITE setQuantity NOTIFY QuantityChanged)
    Q_PROPERTY(int ui_Cost READ Cost WRITE setCost NOTIFY CostChanged)
    Q_PROPERTY(int ui_Total_cost READ Total_cost WRITE setTotal_cost NOTIFY Total_costChanged)
    Q_PROPERTY(QString ui_Id READ Id WRITE setId NOTIFY IdChanged)
    Q_PROPERTY(QString ui_date READ getDate WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(QString  ui_payment READ getPayment WRITE setPayment NOTIFY PaymentChanged)
    Q_PROPERTY(QString  ui_user READ getUser WRITE setUser NOTIFY UserChanged)
    Q_PROPERTY(int ui_profit READ getProfit WRITE setProfit NOTIFY profitChanged)
    Q_PROPERTY(int ui_Discount READ getDiscount WRITE setDiscount NOTIFY DiscountChanged)
    Q_PROPERTY(int ui_total_discount READ getTotalDiscount WRITE setTotalDiscount NOTIFY TDiscountChanged)
public:
    explicit Sale(QObject *parent = nullptr);
      Sale(QString id,QString name,QString category,int quantity,int cost, int totalcost,QString Date,QString user,QString payment,int mProfit);

    QString Name() const;
    void setName(const QString &Name);

    QString Category() const;
    void setCategory(const QString &Category);

    int Quantity() const;
    void setQuantity(int Quantity);

    int Cost() const;
    void setCost(int Cost);

    int Total_cost() const;
    void setTotal_cost(int Total_cost);

    QString Id() const;
    void setId(const QString &Id);

    QString getDate() const;
    void setDate(const QString &value);

    QString getUser() const;
    void setUser(const QString &user);

    QString getPayment() const;
    void setPayment(const QString &payment);

    int getProfit() const;
    void setProfit(int profit);

    int getDiscount() const;
    void setDiscount(int discount);

    int getTotalDiscount() const;
    void setTotalDiscount(int totalDiscount);

signals:
    void NameChanged();
    void CategoryChanged();
    void QuantityChanged();
    void CostChanged();
    void  Total_costChanged();
    void dateChanged();
    void IdChanged();
    void PaymentChanged();
    void UserChanged();
    void profitChanged();
    void DiscountChanged();
    void TDiscountChanged();
private:
    QString _Id;
    QString _Name;
    QString _Category;
    int _Quantity=0;
    int _Cost=0;
    int _Total_cost=0;
    QString date;
    QString mPayment;
    QString mUser;
    int mProfit=0;
    int mDiscount=0;
    int mTotalDiscount=0;

};
}
#endif // SALES_H
