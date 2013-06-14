#include "GeoPoint.h"

GeoPoint::GeoPoint(void) {
    xCoord = 0.0;
    yCoord = 0.0;
}

GeoPoint::GeoPoint(float x, float y) {
    xCoord = x;
    yCoord = y;
}

// Note the nuance here. Less than ONLY compares the y coordinate
bool GeoPoint::operator < (const GeoPoint& other) const
{
    if(xCoord < other.xCoord)
        return true;
    else if(xCoord == other.xCoord)
    {
        if(yCoord < other.yCoord)
        {
            return true;
        }
    }
    return false;
}

GeoPoint::~GeoPoint(void) {
}
