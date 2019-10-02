#ifndef WAYINFO_H
#define WAYINFO_H

#include <QObject>
#include "coordinateorder.h"
#include <QGeoCoordinate>
#include <QtDebug>
#include <QString>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace  std;

class WayInfo : public QObject
{
    Q_OBJECT

public:
    explicit WayInfo(QObject *parent = nullptr);


    QString coorBase()
    {
        return "DDD";
    }
    void setCoorBase( QString &coor)
    {

        qDebug()<<coor;
        pointBase.setLatitude(coor.split(",")[0].toDouble());
        pointBase.setLatitude(coor.split(",")[1].toDouble());
    }
signals:
    void offStart();
    void offEnd();
    void Base();
private:
    QList<QGeoCoordinate> _wayFly;
    QString _coor;
    //point.first X longtitude
    //point.second Y latitude
    CoordinateOrder *order;
    QGeoCoordinate pointBase,pointStart,pointEnd;
    pair<int,int> choseStart(vector<vector<pair<int,pair<double, double>> > > &a,QGeoCoordinate &start, QGeoCoordinate &end, QGeoCoordinate &base,double &distanceStart);
    //differentX, differentY
    double lengthDegreeX=0,lengthDegreeY=0,height=0;

    double countSquareWDouble,countSquareWTrunc,difference,countSquareLDouble,countSquareLTrunc;
    double longtitude=0,latitude=0;//довгота //широта
    double vutr=0; //Витрати на політ
    double vusot=0; //Висота польоту
    double vutrnafoto=0;//витрати на політ
    double focusDistance,horizontalAngel, verticalAngel;
    int countSquareWMain, countSquareLMain;
    int positionPoints;//в Ростіка на телефоні або ТЮІ 2019
    double length=0,width=0;
public slots:
    QList<QGeoCoordinate> wayFly()
    {
        return _wayFly;
    }
    QGeoCoordinate basePosition()
    {
        return pointBase;
    }

    void setCoordinates(QString coordinates,int combin)
    {

        switch(combin)
        {
            case 1:

                pointBase.setLatitude(coordinates.split(",")[0].toDouble());
                pointBase.setLongitude(coordinates.split(",")[1].toDouble());
            break;
            case  2:

                pointEnd.setLatitude(coordinates.split(",")[0].toDouble());
                pointEnd.setLongitude(coordinates.split(",")[1].toDouble());
            break;
            case 3:

                pointStart.setLatitude(coordinates.split(",")[0].toDouble());
                pointStart.setLongitude(coordinates.split(",")[1].toDouble());
            break;
        }
    }
    void setAllParametrs(QString focus,QString horizA,QString verticalA,QString costPhoto,QString costFly,QString he)
    {
        focusDistance=focus.toDouble();
        horizontalAngel=horizA.toDouble();
        verticalAngel=verticalA.toDouble();
        vutrnafoto=costPhoto.toDouble();
        vutr=costFly.toDouble();
        height=he.toDouble();
    }

   void handleDate();
};

#endif // WAYINFO_H
