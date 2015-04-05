#ifndef AG_VEC4_H
#define AG_VEC4_H

class AGVec4
{
	public:	
		AGVec4();
		AGVec4( float value );
		AGVec4( float inX, float inY, float inZ, float inW ); 
		~AGVec4();

		float x, y, z, w; 
};

#endif 