#include "coordinateorder.h"
#include <QtDebug>


CoordinateOrder::CoordinateOrder(long L, long W, double Length, double Width):L(L),W(W), length(Length),width(Width)
{

}


void CoordinateOrder::coordinateOrder(vector<vector<pair<int,pair<double, double>> > > &a,  int w, int l, int ec)
{
    coordinatsWay.first=w;
    coordinatsWay.second=l;
    qDebug()<<w<<l;
    way.push_back(coordinatsWay);
    if(l+1<L)//Right
    {
        if (a[w][l+1].first == 0)//we have not been there
        {
            // check that we were there
            wayLenght+=length;
            a[w][l+1].first = 1;
            coordinateOrder(a, w, l+1, ec-1); // we go there
        }
    }

    // Down
    if(w+1<W)
    {
        if (a[w+1][l].first == 0)//we have not been there
        {
             wayLenght+=width;
            a[w+1][l].first = 1;
            coordinateOrder(a, w+1, l, ec-1);
        }
    }


    //Left
    if(l-1>=0)
    {
        if (a[w][l-1].first == 0) //we have not been there
        {
            wayLenght+=length;
            a[w][l-1].first = 1;
            coordinateOrder(a, w, l-1, ec-1);
        }

    }
    //Up
    if(w-1>=0)
    {
        if (a[w-1][l].first == 0)//we have not been there
        {
            wayLenght+=width;
            a[w-1][l].first = 1;
            coordinateOrder(a, w-1, l, ec-1);
        }
    }
}

double CoordinateOrder::getLength()
{
    return wayLenght;
}

vector<pair<int,int>> CoordinateOrder::getWay()
{
    return way;
}
