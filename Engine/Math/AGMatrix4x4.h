#ifndef AG_MATRIX4X4_H
#define AG_MATRIX4X4_H

class AGMatrix4x4 
{
	public:
		AGMatrix4x4();
		AGMatrix4x4( float e );
		AGMatrix4x4( 
			float e00, float e01, float e02, float e03,
			float e10, float e11, float e12, float e13, 
			float e20, float e21, float e22, float e23,
			float e30, float e31, float e32, float e33 );
		AGMatrix4x4( const AGMatrix4x4& copy );

		bool isIdentity(); 
		void setIdentity();

		void fill( float e );
		void invert(); 
		AGMatrix4x4 getInverted(); 

		void transpose(); 
		AGMatrix4x4 getTransposed(); 

		static AGMatrix4x4 getIdentity();
};

#endif 