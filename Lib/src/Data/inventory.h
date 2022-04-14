#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include<Lib_global.h>

namespace Data {


class LIB_EXPORT Inventory : public QObject
{
    Q_OBJECT
public:
    explicit Inventory(QObject *parent = nullptr);

signals:
private:
    int mId;
    QString mName;
    QString mCategory;
    int mQuantity;
    int mPrice;
    int mSubtotal;

};
}
#endif // INVENTORY_H
