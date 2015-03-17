#include "AGVec4.h"

AGVec4::AGVec4()
{
	x = y = z = w = 0.0f;
}

AGVec4::AGVec4(float value)
{
	x = y = z = w = value; 
}

AGVec4::AGVec4( float inX, float inY, float inZ, float inW )
{
	x = inX;
	y = inY;
	z = inZ;
	w = inW; 
}

AGVec4::~AGVec4()
{

}

