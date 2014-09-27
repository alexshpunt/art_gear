#ifndef AG_POINT_H
#define AG_POINT_H

class AGPoint 
{
	public:
		AGPoint();
		AGPoint( float x, float y );
		AGPoint( const AGPoint& copy );
		~AGPoint();

		void setX( float x );
		float getX() const; 

		void setY( float y );
		float getY() const; 

		bool operator==( const AGPoint& var );
		AGPoint& operator=( const AGPoint& var );

		AGPoint operator+( const AGPoint& var );
		AGPoint& operator+=( const AGPoint& var );

		AGPoint operator-( const AGPoint& var );
		AGPoint& operator-=( const AGPoint& var );

		AGPoint operator*( float var );
		AGPoint& operator*=( float var );
		
		AGPoint operator/( float var );
		AGPoint& operator/=( float var );

	private:
		float m_x;
		float m_y;
};

#endif 