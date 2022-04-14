#ifndef EXPENSES_H
#define EXPENSES_H

#include<Lib_global.h>

#include <QObject>
#include<QDate>

namespace Data {
class LIB_EXPORT Expenses : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate ui_Date READ Date WRITE setDate NOTIFY DateChanged)
    Q_PROPERTY(QString ui_Description READ Description WRITE setDescription NOTIFY DescriptionChanged)
    Q_PROPERTY(float ui_Amount READ Amount WRITE setAmount NOTIFY AmountChanged)
    Q_PROPERTY(QString ui_UID READ UID WRITE setUID NOTIFY UIDChanged)
    Q_PROPERTY(QString ui_Employee READ Employee WRITE setEmployee NOTIFY EmployeeChanged)
public:
    explicit Expenses(QObject *parent = nullptr);
     Expenses( QDate _Date,QString _Description, float _Amount,QString _UID,   QString _Employee);

    QDate Date() const;
    void setDate(const QDate &Date);

    QString Description() const;
    void setDescription(const QString &Description);

    float Amount() const;
    void setAmount(float Amount);

    QString UID() const;
    void setUID(const QString &UID);

    QString Employee() const;
    void setEmployee(const QString &Employee);

signals:
    void DateChanged();
    void DescriptionChanged();
    void AmountChanged();
    void UIDChanged();
    void EmployeeChanged();

private:
    QDate _Date;
    QString _Description;
    float _Amount;
    QString _UID;
    QString _Employee;


};
}
#endif // EXPENSES_H
