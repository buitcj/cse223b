#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <sstream>

using namespace std;

class GeoPoint {
	public:
		float xCoord;
		float yCoord;

		GeoPoint(void);
		GeoPoint(float x, float y);
		bool operator < (const GeoPoint& other) const;

		~GeoPoint(void);
};
