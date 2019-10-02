#include "wayinfo.h"

#include "coordinateorder.h"

WayInfo::WayInfo(QObject *parent) : QObject(parent)
{

}
#define pi 3.14159265359

double toRad(double degree)
{
  return degree*pi/180;

}

// length in meters of a degree in latitude, longtitude
pair<double, double> getLengthDegree(double latDegree)
{
  double lat =  toRad(latDegree); //latitude in radians
  pair<double, double> lengthDegree;
  /*
  a degree of latitude =
  110574m (equator)
  111694m (pole)
  */
  lengthDegree.first = 111132.92 - 559.82*cos(2*lat) + 1.175*cos(4*lat) - 0.0023*cos(6*lat);
  /*
  a degree of longtitude =
  111319m (equator)
  0m (pole)
  */
  lengthDegree.second = 111412.84*cos(lat) - 93.5*cos(3*lat) + 0.118 * cos(5*lat);
  return lengthDegree;
}



void WayInfo::handleDate()// todo rename
{
    //height=ui->Height->text().toDouble();
   // horizontalAngel=ui->GeometrySensorH->text().toDouble();
   // verticalAngel=ui->GeometrySensor->text().toDouble();
    //focusDistance=ui->FocusDistance->text().toDouble();

// set degree of latitude, longtitude in degrees to pair
   // pointEnd.longitude()=ui->pointXEnd->text().toDouble();//Довгота
    //pointEnd.latitude()=ui->pointYEnd_2->text().toDouble();//Широта

    //pointStart.longitude()=ui->pointXStart->text().toDouble();
    //pointStart.latitude()=ui->pointYStart->text().toDouble();

   // pointbase.longitude()=ui->pointXBase->text().toDouble();
   // pointbase.latitude()=ui->pointYBase->text().toDouble();

    // angle of view
    double aH=2*(atan(horizontalAngel/(2*focusDistance))*180/pi);
    double aV=2*(atan(verticalAngel/(2*focusDistance))*180/ pi);

    length=2*tan(0.5*aH*pi/180)*height;
    width= 2*tan(0.5*aV*pi/180)*height;

    qDebug()<<"length width meters"<<length<<" "<<width<<pointStart.longitude();

    if(pointStart.longitude()<pointEnd.longitude() && pointStart.latitude()>pointEnd.latitude())
    {
        positionPoints=1;//Стартова позиція в лівому верхньому куті
        lengthDegreeX=pointEnd.longitude()-pointStart.longitude();//Довгота в градусах
        lengthDegreeY=pointStart.latitude()-pointEnd.latitude();//Широта в градусах
    }else if (pointStart.longitude()>pointEnd.longitude() && pointStart.latitude()>pointEnd.latitude())
    {
        positionPoints=2;//Стартова точка знаходится в правому верхньому куті
        lengthDegreeX=pointStart.longitude()-pointEnd.longitude();//Довгота в градусах
        lengthDegreeY=pointStart.latitude()-pointEnd.latitude();//Широта в градусах
    }else if (pointStart.longitude()>pointEnd.longitude() && pointStart.latitude()<pointEnd.latitude())
    {
        positionPoints=3;//Стартова точка знаходится в правому нижньому куті
        lengthDegreeX=pointStart.longitude()-pointEnd.longitude();//Довгота в градусах
        lengthDegreeY=pointEnd.latitude()-pointStart.latitude();//Широта в градусах

    }else if (pointStart.longitude()<pointEnd.longitude() && pointStart.latitude()<pointEnd.latitude())
    {
        positionPoints=4;//Стартова точка знаходится в лівому нижньому куті
        lengthDegreeX=pointEnd.longitude()-pointStart.longitude();//Довгота в градусах
        lengthDegreeY=pointEnd.latitude()-pointStart.latitude();//Широта в градусах
    }

    qDebug()<<"PositionPoints: "<<positionPoints;
    //degree to meters
    pair<double, double> metersDegree = getLengthDegree(pointStart.latitude());  // length depend on latitude
    latitude=lengthDegreeY*metersDegree.first;//Широта в метрах
    longtitude=lengthDegreeX*metersDegree.second;//Довгота в метрах

    qDebug()<<"Latitude v metrax, longtitude: "<<latitude<<" "<<longtitude;

    countSquareWDouble = abs(latitude/width);
    countSquareLDouble = abs(longtitude/length);

    countSquareWTrunc = trunc(countSquareWDouble);
    countSquareLTrunc = trunc(countSquareLDouble);

    difference = countSquareWDouble - countSquareWTrunc;

    if (difference>0)
    {
        countSquareWMain = countSquareWTrunc+1;
    }
    else {
        countSquareWMain = countSquareWTrunc;
    }
    difference = countSquareLDouble - countSquareLTrunc;
    if (difference>0)
    {
        countSquareLMain = countSquareLTrunc+1;
    }
    else {
        countSquareLMain = countSquareLTrunc;
    }

    qDebug()<<latitude/width<<" "<<longtitude/length;
    double pointX1;  // Координата центра першого прямокутника
    double pointY1;
    if(positionPoints==1 || positionPoints==2)
    {
        pointY1=pointStart.latitude()-abs((width/2)/(111.32*1000));
    }else
    {
       pointY1=pointStart.latitude()+abs((width/2)/(111.32*1000));
    }
    if(positionPoints==1 || positionPoints==4)
    {
          pointX1=pointStart.longitude()+((length/2)/(cos(lengthDegreeY*3.14/180)*(40075/360)*1000));
    }else
    {
          pointX1=pointStart.longitude()-((length/2)/(cos(lengthDegreeY*3.14/180)*(40075/360)*1000));
    }
    pair<int,pair<double,double>> *defpair=new pair<int,pair<double,double>>();
    defpair->first=0;
    vector<pair<int,pair<double, double>>> def(countSquareLMain,*defpair) ;  // {ми там були, (Latitude1, Longtitude1)}, {чи ми там були, (Latitude2, Longtitude2)}
    vector<vector<pair<int, pair<double, double>>>> a(countSquareWMain,def);


    a[0][0].second.first=pointY1;
    a[0][0].second.second=pointX1;
    qDebug()<<"countW double: "<<countSquareWDouble<<"countL"<<countSquareLDouble;
    qDebug()<<"countW main: "<<countSquareWMain<<"countL"<<countSquareLMain;

//    qDebug()<<"1:"<<QString::number(pointY1,'f',6)+","+QString::number(pointX1,'f',6);
    for(unsigned int i=0;i<countSquareWMain;++i)
    {
        if(i!=0)
        {
          if(positionPoints==1 || positionPoints==2)
          {

               a[i][0].second.first=a[i-1][0].second.first-abs((width)/(111.32*1000));//down
          }else
          {
                a[i][0].second.first=a[i-1][0].second.first+abs((width)/(111.32*1000));;
          }
        }
        a[i][0].second.second=pointX1;
        for (unsigned int j=0;j<countSquareLMain;++j)
        {
            if(j!=0)
            {
                if(positionPoints==1 || positionPoints==4)
                {
                     a[i][j].second.second=a[i][j-1].second.second+(length)/(cos(lengthDegreeY*3.14/180)*(40075/360)*1000);
                }else
                {
                     a[i][j].second.second=a[i][j-1].second.second-(length)/(cos(lengthDegreeY*3.14/180)*(40075/360)*1000);
                }
            }
            a[i][j].second.first=a[i][0].second.first;
            //qDebug()<<QString::number(a[i][j].second.first,'f',6)+", "+QString::number(a[i][j].second.second,'f',6);
        }
    }


    int countSquare=countSquareLMain*countSquareWMain;
    double distanceStart=0;
    pair<int,int> pos=choseStart(a,pointStart,pointEnd,pointBase,distanceStart);
    a[pos.first][pos.second].first=1;  // ми були в початковій координаті
    order=new CoordinateOrder(countSquareLMain,countSquareWMain,length,width);
    order->coordinateOrder(a,pos.first,pos.second,countSquare);
    vector<pair<int,int>> way=order->getWay();
    double differentXEnd=a[way[countSquare-1].first][way[countSquare-1].second].second.second-pointBase.longitude();
    double differentYEnd=a[way[countSquare-1].first][way[countSquare-1].second].second.first-pointBase.latitude();
    qDebug()<<"Way points:";
    for(int i=0;i<countSquare;++i)
    {

        qDebug()<<QString::number(a[way[i].first][way[i].second].second.first,'f',6)<<QString::number(a[way[i].first][way[i].second].second.second,'f',6);
        QGeoCoordinate tmp(a[way[i].first][way[i].second].second.first,a[way[i].first][way[i].second].second.second);
        _wayFly.push_back(tmp);
    }

    double latitudeEnd=differentYEnd*111.32*1000;//Широта в метрах
    double longtitudeEnd=cos(differentYEnd*3.14/180)*40075/360*1000*differentXEnd;
    double distanceEnd=sqrt(pow(latitudeEnd,2)+pow(longtitudeEnd,2)+pow(height,2));//?????????????????

    qDebug()<<order->getLength()<<" "<<distanceEnd<<" "<<distanceStart;
    double d=order->getLength()+distanceEnd+distanceStart;

    qDebug()<<QString::number(d,'f',6);
    qDebug()<<countSquare;
   // vutr = ui->vutr->text().toDouble();
  //  vutrnafoto= ui->vutrnafoto->text().toDouble();
    double pal=d*vutr + vutrnafoto*countSquare;qDebug()<<QString::number(pal,'f',6);



}


pair<int,int> WayInfo::choseStart(vector<vector<pair<int,pair<double, double>> > > &a,QGeoCoordinate &start, QGeoCoordinate &end, QGeoCoordinate &base,double &distanceStart)
{
    pair<int,int> position;
    double min=INT_MAX;

    double diffX=0;
    double diffY=0;
    double latitudeS,longtitudeS;
    switch(positionPoints)
    {
        case 1:
            if(base.latitude() > end.latitude() && base.latitude() < end.latitude() && base.longitude() < start.longitude())//1
            {
                for(int i=0;i<countSquareWMain;++i)
                {
                   diffX=abs(base.longitude()-a[i][0].second.second);
                   diffY=abs(base.latitude()-a[i][0].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.first=i;
                   }
                }
                position.second=0;
                return position;
            }else
            if (base.latitude() > start.latitude() && base.longitude() > start.longitude() && base.longitude() < end.longitude()) //2
            {
                for(int i=0;i<countSquareLMain;++i)
                {
                   diffX=abs(base.longitude()-a[0][i].second.second);
                   diffY=abs(base.latitude()-a[0][i].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.second=i;
                   }
                }
                position.first=0;
                return position;
            }else
            if (base.latitude() > end.latitude() && base.latitude() <= start.latitude() && base.longitude() >= end.longitude()) //3
            {
                for(int i=0;i<countSquareWMain;++i)
                {
                   diffX=abs(base.longitude()-a[i][countSquareLMain-1].second.second);
                   diffY=abs(base.latitude()-a[i][countSquareLMain-1].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.first=i;
                   }
                }
                position.second=countSquareLMain-1;
                return position;
            }else
            if (base.latitude() < start.latitude() && base.longitude() > start.longitude() && base.longitude() < end.longitude()) //4
            {
                for(int i=0;i<countSquareLMain;++i)
                {
                   diffX=abs(base.longitude()-a[countSquareWMain-1][i].second.second);
                   diffY=abs(base.latitude()-a[countSquareWMain-1][i].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.second=i;
                   }
                }
                position.first=countSquareWMain-1;
                return position;
            }else if (base.longitude()<=start.longitude() && base.latitude()>=start.latitude()) //5
            {
                position.first=0;
                position.second=0;

                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()>=end.longitude() && base.latitude()>=start.latitude())//6
            {
                position.first=0;
                position.second=countSquareLMain-1;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()>=end.longitude() && base.latitude()<=end.latitude()) //7
            {
                position.first=countSquareWMain-1;
                position.second=countSquareLMain-1;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()<=start.longitude() && base.latitude()<=start.latitude())//8
            {
                position.first=countSquareWMain-1;
                position.second=0;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }
        break;
        case 2:
            if(base.longitude()<end.longitude() && base.latitude()>end.latitude() && base.latitude()<start.latitude())//1
            {
                for(int i=0;i<countSquareWMain;++i)
                {
                   diffX=abs(base.longitude()-a[i][0].second.second);
                   diffY=abs(base.latitude()-a[i][0].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.first=i;
                   }
                }
                position.second=0;
                return position;
            }else
            if (base.latitude()>start.latitude() && base.longitude()>end.longitude() && base.longitude()<start.longitude()) //2
            {
                for(int i=0;i<countSquareLMain;++i)
                {
                   diffX=abs(base.longitude()-a[0][i].second.second);
                   diffY=abs(base.latitude()-a[0][i].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.second=i;
                   }
                }
                position.first=0;
                return position;
            }else
            if (base.longitude()>end.longitude() && base.latitude()>end.latitude() && base.latitude()<start.latitude()) //3
            {
                for(int i=0;i<countSquareWMain;++i)
                {
                   diffX=abs(base.longitude()-a[i][countSquareLMain-1].second.second);
                   diffY=abs(base.latitude()-a[i][countSquareLMain-1].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.first=i;
                   }
                }
                position.second=countSquareLMain-1;
                return position;
            }else
            if (base.latitude()<start.latitude() && base.longitude()>end.longitude() && base.longitude()<start.longitude()) //4
            {
                for(int i=0;i<countSquareLMain;++i)
                {
                   diffX=abs(base.longitude()-a[countSquareWMain-1][i].second.second);
                   diffY=abs(base.latitude()-a[countSquareWMain-1][i].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.second=i;
                   }
                }
                position.first=countSquareWMain-1;
                return position;
            }else if (base.longitude()<=end.longitude() && base.latitude()>=start.latitude()) //5
            {
                position.first=0;
                position.second=0;
                diffX=abs(base.longitude()-a[position.first][position.second].second.second);
                diffY=abs(base.latitude()-a[position.first][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()>=start.longitude() && base.latitude()>=start.latitude())//6
            {
                position.first=0;
                position.second=countSquareLMain-1;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()>=start.longitude() && base.latitude()<=end.latitude()) //7
            {
                position.first=countSquareWMain-1;
                position.second=countSquareLMain-1;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()<=end.longitude() && base.latitude()<=end.latitude())//8
            {
                position.first=countSquareWMain-1;
                position.second=0;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }
        break;
        case 3:
            if(base.latitude() > start.latitude() && base.latitude() < start.latitude() && base.longitude() < end.longitude())//1
            {
                for(int i=0;i<countSquareWMain;++i)
                {
                   diffX=abs(base.longitude()-a[i][0].second.second);
                   diffY=abs(base.latitude()-a[i][0].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.first=i;
                   }
                }
                position.second=0;
                return position;
            }else
            if (base.latitude() > end.latitude() && base.longitude() > end.longitude() && base.longitude() < start.longitude()) //2
            {
                for(int i=0;i<countSquareLMain;++i)
                {
                   diffX=abs(base.longitude()-a[0][i].second.second);
                   diffY=abs(base.latitude()-a[0][i].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.second=i;
                   }
                }
                position.first=0;
                return position;
            }else
            if (base.latitude() > start.latitude() && base.latitude() <= end.latitude() && base.longitude() >= start.longitude()) //3
            {
                for(int i=0;i<countSquareWMain;++i)
                {
                   diffX=abs(base.longitude()-a[i][countSquareLMain-1].second.second);
                   diffY=abs(base.latitude()-a[i][countSquareLMain-1].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.first=i;
                   }
                }
                position.second=countSquareLMain-1;
                return position;
            }else
            if (base.latitude() < end.latitude() && base.longitude() > end.longitude() && base.longitude() < start.longitude()) //4
            {
                for(int i=0;i<countSquareLMain;++i)
                {
                   diffX=abs(base.longitude()-a[countSquareWMain-1][i].second.second);
                   diffY=abs(base.latitude()-a[countSquareWMain-1][i].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.second=i;
                   }
                }
                position.first=countSquareWMain-1;
                return position;
            }else if (base.longitude()<=end.longitude() && base.latitude()>=end.latitude()) //5
            {
                position.first=0;
                position.second=0;
                diffX=abs(base.longitude()-a[position.first][position.second].second.second);
                diffY=abs(base.latitude()-a[position.first][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()>=start.longitude() && base.latitude()>=end.latitude())//6
            {
                position.first=0;
                position.second=countSquareLMain-1;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()>=start.longitude() && base.latitude()<=start.latitude()) //7
            {
                position.first=countSquareWMain-1;
                position.second=countSquareLMain-1;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()<=end.longitude() && base.latitude()<=end.latitude())//8
            {
                position.first=countSquareWMain-1;
                position.second=0;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }
        break;
        case 4:
            if(base.longitude()<start.longitude() && base.latitude()>start.latitude() && base.latitude()<end.latitude())//1
            {
                for(int i=0;i<countSquareWMain;++i)
                {
                   diffX=abs(base.longitude()-a[i][0].second.second);
                   diffY=abs(base.latitude()-a[i][0].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.first=i;
                   }
                }
                position.second=0;

            }else
            if (base.latitude()>end.latitude() && base.longitude()>start.longitude() && base.longitude()<end.longitude()) //2
            {
                for(int i=0;i<countSquareLMain;++i)
                {
                   diffX=abs(base.longitude()-a[0][i].second.second);
                   diffY=abs(base.latitude()-a[0][i].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.second=i;
                   }
                }
                position.first=0;
            }else
            if (base.longitude()>start.longitude() && base.latitude()>start.latitude() && base.latitude()<end.latitude()) //3
            {
                for(int i=0;i<countSquareWMain;++i)
                {
                   diffX=abs(base.longitude()-a[i][countSquareLMain-1].second.second);
                   diffY=abs(base.latitude()-a[i][countSquareLMain-1].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.first=i;
                   }
                }
                position.second=countSquareLMain-1;
            }else
            if (base.latitude()<end.latitude() && base.longitude()>start.longitude() && base.longitude()<end.longitude()) //4
            {
                for(int i=0;i<countSquareLMain;++i)
                {
                   diffX=abs(base.longitude()-a[countSquareWMain-1][i].second.second);
                   diffY=abs(base.latitude()-a[countSquareWMain-1][i].second.first);
                   latitudeS=diffY*111.32*1000;
                   longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                   distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                   if (distanceStart<min)
                   {
                       min = distanceStart;
                       position.second=i;
                   }
                }
                position.first=countSquareWMain-1;

            }else if (base.longitude()<=start.longitude() && base.latitude()>=end.latitude()) //5
            {
                position.first=0;
                position.second=0;
                diffX=abs(base.longitude()-a[position.first][position.second].second.second);
                diffY=abs(base.latitude()-a[position.first][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()>=end.longitude() && base.latitude()>=end.latitude())//6
            {
                position.first=0;
                position.second=countSquareLMain-1;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()>=end.longitude() && base.latitude()<=start.latitude()) //7
            {
                position.first=countSquareWMain-1;
                position.second=countSquareLMain-1;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }else if (base.longitude()<=start.longitude() && base.latitude()<=start.latitude())//8
            {
                position.first=countSquareWMain-1;
                position.second=0;
                diffX=abs(base.longitude()-a[position.second][position.first].second.second);
                diffY=abs(base.latitude()-a[position.second][position.second].second.first);
                latitudeS=diffY*111.32*1000;
                longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
                distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2)+pow(height,2));
                return position;
            }
        break;
        }
}
