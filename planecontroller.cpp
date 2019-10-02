#include "planecontroller.h"


PlaneController::PlaneController()
{
    easingCurve.setType(QEasingCurve::InOutQuad);
    easingCurve.setPeriod(ANIMATION_DURATION);
}

void PlaneController::setFrom( QGeoCoordinate frm)
{
    fromCoordinate = frm;
}

void PlaneController::setTo( QGeoCoordinate to)
{
    toCoordinate = to;
}

QGeoCoordinate PlaneController::to()
{
    return toCoordinate;
}

void PlaneController::setPosition( QGeoCoordinate c)
{
    if (currentPosition == c)
        return;

    currentPosition = c;
    emit positionChanged();
}

QGeoCoordinate PlaneController::position()
{
    return currentPosition;
}

bool PlaneController::isFlying() const
{
    return timer.isActive();
}

//! [C++Pilot2]

void PlaneController::startFlight()
{
    if (timer.isActive())
        return;

    startTime = QTime::currentTime();
    finishTime = startTime.addMSecs(ANIMATION_DURATION);

    timer.start(15, this);
    emit departed(); // відправлення
}
//! [C++Pilot2]


void PlaneController::timerEvent(QTimerEvent *event)
{
    if (!event)
        return;

    if (event->timerId() == timer.timerId())
        updatePosition();
    else
        QObject::timerEvent(event);
}


void PlaneController::updatePosition()
{
    // simple progress animation
    qreal progress;
    QTime current = QTime::currentTime();
    if (current >= finishTime) {
        progress = 1.0;
        timer.stop();
    } else {
        progress = ((qreal)startTime.msecsTo(current) / ANIMATION_DURATION);
    }

    setPosition(QWebMercator::coordinateInterpolation(
                      fromCoordinate, toCoordinate, easingCurve.valueForProgress(progress)));

    if (!timer.isActive())
        emit arrived();
}
