#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include<Lib_global.h>
#include<QTime>
#include<QDate>

namespace Data {
class LIB_EXPORT Timer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_Id READ Id WRITE setId NOTIFY IdChanged)
    Q_PROPERTY(QTime ui_End READ End WRITE setEnd NOTIFY EndChanged)
    Q_PROPERTY(QTime ui_Start READ Start WRITE setStart NOTIFY StartChanged)
    Q_PROPERTY(QTime ui_Hours READ Hours WRITE setHours NOTIFY HoursChanged)
public:
    explicit Timer(QObject *parent = nullptr);

    QTime Start() const;
    void setStart(const QTime &Start);

    QTime End() const;
    void setEnd(const QTime &End);

    QTime Hours() const;
    void setHours(const QTime &Hours);

    QString Id() const;
    void setId(const QString &Id);

signals:
    void IdChanged();
    void EndChanged();
    void StartChanged();
    void HoursChanged();
private:
    QTime _Start;
    QTime _End;
    QTime _Hours;
    QString _Id;


};
}
#endif // TIMER_H
