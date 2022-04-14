#include "timer.h"
namespace Data {
Timer::Timer(QObject *parent) : QObject(parent)
{

}

QTime Timer::Start() const
{
    return _Start;
}

void Timer::setStart(const QTime &Start)
{
   if( _Start != Start){
        _Start = Start;
        emit StartChanged();
   }
}

QTime Timer::End() const
{
    return _End;
}

void Timer::setEnd(const QTime &End)
{
   if( _End != End){
        _End = End;
        emit EndChanged();
   }
}

QTime Timer::Hours() const
{
    return _Hours;
}

void Timer::setHours(const QTime &Hours)
{
    if(_Hours != Hours){
        _Hours = Hours;
        emit HoursChanged();
    }
}

QString Timer::Id() const
{
    return _Id;
}

void Timer::setId(const QString &Id)
{
   if( _Id != Id){
        _Id = Id;
        emit IdChanged();
   }
}
}
