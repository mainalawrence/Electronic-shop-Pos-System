#ifndef Employee_D_H
#define Employee_D_H

#include <QObject>
#include<Lib_global.h>
#include<QString>

namespace Data {

class LIB_EXPORT Employee_D : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString Fname READ FName WRITE setFName NOTIFY FnameChanged)
    Q_PROPERTY(QString LName READ LName WRITE setLName NOTIFY LNameChanged)
    Q_PROPERTY(QString Email READ Email WRITE setEmail NOTIFY EmailChanged)
    Q_PROPERTY(QString Phone READ Phone WRITE setPhone NOTIFY PhoneChanged)
    Q_PROPERTY(QString Gender READ Gender WRITE setGender NOTIFY GenderChanged)
    Q_PROPERTY(QString Username READ Username WRITE setUsername NOTIFY UsernameChanged)
    Q_PROPERTY(QString PAssword READ PAssword WRITE setPAssword NOTIFY PAsswordChanged)
    Q_PROPERTY(QString Role READ Role WRITE setRole NOTIFY RoleChanged)
public:
    explicit Employee_D(QObject *parent = nullptr);
    Employee_D( int  id,QString _FName,QString _LName,QString _Email,QString _Phone,QString _Gender,QString _Username,QString _PAssword,QString _Role);

    QString FName() const;
    void setFName(const QString &FName);

    QString LName() const;
    void setLName(const QString &LName);

    QString Email() const;
    void setEmail(const QString &Email);

    QString Phone() const;
    void setPhone(const QString &Phone);

    QString Gender() const;
    void setGender(const QString &Gender);

    QString Username() const;
    void setUsername(const QString &Username);

    QString PAssword() const;
    void setPAssword(const QString &PAssword);

    QString Role() const;
    void setRole(const QString &Role);

    int getId() const;
    void setId(int value);

signals:
    void idChanged();
    void FnameChanged();
    void LNameChanged();
    void EmailChanged();
    void PhoneChanged();
    void GenderChanged();
    void UsernameChanged();
    void PAsswordChanged();
    void RoleChanged();


private:
    int  id;
    QString _FName;
    QString _LName;
    QString _Email;
    QString _Phone;
    QString _Gender;
    QString _Username;
    QString _PAssword;
    QString _Role;

};
}
#endif
