#ifndef COORDINATEORDER_H
#define COORDINATEORDER_H

#include <bits/stdc++.h>

using namespace  std;

class CoordinateOrder
{
public:
    CoordinateOrder( long L, long W,double Length,double Width);
       ~CoordinateOrder();
    void coordinateOrder(vector<vector<pair<int,pair<double, double>> > > &a, int w,int l, int ec);
        double getLength();
        vector<pair<int,int>> getWay();
    private:

        vector<pair<int,int>> way;
        long L, W;
        pair<int,int> coordinatsWay;
        double lengthToBase=0;
        int wayLenght=0;

        double length=0,width=0;
        int fg=0;
};

#endif // COORDINATEORDER_H
