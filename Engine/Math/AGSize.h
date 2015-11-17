#ifndef AG_SIZE_H
#define AG_SIZE_H

class AGSize
{
	public:
		AGSize();
		AGSize( int w, int h );
		AGSize( const AGSize& copy );
		~AGSize();

		void setSize( int w, int h );
		void setSize( const AGSize& size );

		void setWidth( int w );
		int getWidth() const;

		void setHeight( int h );
		int getHeight() const; 

		bool operator==( const AGSize& var );
		AGSize& operator=( const AGSize& var );

		AGSize operator+( const AGSize& var );
		AGSize& operator+=( const AGSize& var );

		AGSize operator-( const AGSize& var );
		AGSize& operator-=( const AGSize& var );

		AGSize operator*( int var );
		AGSize operator*=( int var );
		
		AGSize operator/( int var );
		AGSize operator/=( int var );

		int m_width;
		int m_height;
	private:
		
};

#endif 