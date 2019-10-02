#ifndef PLANECONTROLLER_H
#define PLANECONTROLLER_H
#include <QObject>
#include <QTime>
#include <QBasicTimer>
#include <QDebug>
#include <QEasingCurve>
#include <QGeoCoordinate>
#include <QtPositioning/private/qwebmercator_p.h>
#include <QDebug>
#include <QTimerEvent>


#define ANIMATION_DURATION 4000


class PlaneController: public QObject
{
    Q_OBJECT
   // Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
  //  Q_PROPERTY(QGeoCoordinate from READ from WRITE setFrom NOTIFY fromChanged)
    //Q_PROPERTY(QGeoCoordinate to READ to WRITE setTo NOTIFY toChanged)

public:
    PlaneController();

    Q_INVOKABLE bool isFlying() const ;



public slots:
    void setFrom( QGeoCoordinate frm);
   // QGeoCoordinate from() ;
    void setTo( QGeoCoordinate to);
    QGeoCoordinate to() ;
    void setPosition( QGeoCoordinate c) ;
    QGeoCoordinate position() ;
    void startFlight();


signals:
    void positionChanged();
    void arrived();
    void departed();
    void toChanged();
    void fromChanged();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    //! [C++Pilot3]
    void updatePosition();
    //! [C++Pilot3]

private:
    QGeoCoordinate currentPosition;
    QGeoCoordinate fromCoordinate, toCoordinate;
    QBasicTimer timer;
    QTime startTime, finishTime;
    QEasingCurve easingCurve;
//! [PlaneController2]
    // ...
};

#endif // PLANECONTROLLER_H
