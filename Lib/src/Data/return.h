#ifndef RETURN_H
#define RETURN_H

#include <QObject>
#include<Lib_global.h>

namespace Data {

class LIB_EXPORT Return : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString emp READ emp WRITE setEmp NOTIFY empChanged)
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(int totalCost READ totalCost WRITE setTotalCost NOTIFY totalCostChanged)
    Q_PROPERTY(QString paytype READ paytype WRITE setPaytype NOTIFY paytypeChanged)
    Q_PROPERTY(int profit READ profit WRITE setProfit NOTIFY profitChanged)
public:
    explicit Return(QObject *parent = nullptr);
Return(int mId,QString mEmp,QString mDate,int mTotalCost,QString mPaytype,int mProfit);
    int id() const;
    void setId(int id);

    QString emp() const;
    void setEmp(const QString &emp);

    QString date() const;
    void setDate(const QString &date);

    int totalCost() const;
    void setTotalCost(int totalCost);

    QString paytype() const;
    void setPaytype(const QString &paytype);

    int profit() const;
    void setProfit(int profit);

signals:
    void idChanged();
    void empChanged();
     void dateChanged();
     void totalCostChanged();
     void paytypeChanged();
     void profitChanged();

private:
    int mId;
    QString mEmp;
    QString mDate;
    int mTotalCost;
    QString mPaytype;
    int mProfit;





};
}
#endif // RETURN_H
