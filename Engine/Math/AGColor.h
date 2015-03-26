#ifndef AG_COLOR_H
#define AG_COLOR_H

class AGColorPrivate; 

class AGColor 
{
	public:
		AGColor(); 
		AGColor( const AGColor& color );

		AGColor( int color ); 
		AGColor( int r, int b, int g ); 
		AGColor( int r, int b, int g, int a ); 

		AGColor( float color ); 
		AGColor( float r, float g, float b );
		AGColor( float r, float g, float b, float a ); 
		~AGColor();

		void setRed( int r );
		void setRed( float r );
		
		void setGreen( int g );
		void setGreen( float g ); 

		void setBlue( int b );
		void setBlue( float b );

		void setAlpha( int a );
		void setAlpha( float a ); 

		void setColor( int r, int g, int b ); 
		void setColor( int r, int g, int b, int a );

		void setColor( float r, float g, float b ); 
		void setColor( float r, float g, float b, float a ); 

		float getRedF() const;
		float getGreenF() const;
		float getBlueF() const;
		float getAlphaF() const;

		int getRed() const;
		int getGreen() const;
		int getBlue() const;
		int getAlpha() const; 

		AGColor& operator=( AGColor color );

		operator float*() const; 

	private:	
		AGColorPrivate* p; 
};

#endif 