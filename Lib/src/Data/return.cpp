#include "return.h"

namespace Data {
Return::Return(QObject *parent) : QObject(parent)
{

}

Return::Return(int mId, QString mEmp, QString mDate, int mTotalCost, QString mPaytype, int mProfit)
    :mId(mId), mEmp(mEmp),mDate(mDate),mTotalCost(mTotalCost), mPaytype(mPaytype) , mProfit(mProfit)
{

}

int Return::id() const
{
    return mId;
}

void Return::setId(int id)
{
    if( mId != id){
        mId = id;
        emit idChanged();
    }
}

QString Return::emp() const
{
    return mEmp;
}

void Return::setEmp(const QString &emp)
{
    if(mEmp != emp){
        mEmp = emp;
        emit empChanged();
    }
}

QString Return::date() const
{
    return mDate;
}

void Return::setDate(const QString &date)
{
    if(  mDate != date)
    {
        mDate = date;
        emit dateChanged();
    }
}

int Return::totalCost() const
{
    return mTotalCost;
}

void Return::setTotalCost(int totalCost)
{
    if( mTotalCost != totalCost){
        mTotalCost = totalCost;
        emit totalCostChanged();
    }
}

QString Return::paytype() const
{
    return mPaytype;
}

void Return::setPaytype(const QString &paytype)
{
    if(mPaytype != paytype){
        mPaytype = paytype;
        emit paytypeChanged();
    }
}

int Return::profit() const
{
    return mProfit;
}

void Return::setProfit(int profit)
{
    if( mProfit != profit){
        mProfit = profit;
        profitChanged();
    }
}

}
