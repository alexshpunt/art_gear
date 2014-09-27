#ifndef AG_SIZE_H
#define AG_SIZE_H

class AGSize
{
	public:
		AGSize();
		AGSize( float w, float h );
		AGSize( const AGSize& copy );
		~AGSize();

		void setSize( float w, float h );
		void setSize( const AGSize& size );

		void setWidth( float w );
		float getWidth() const;

		void setHeight( float h );
		float getHeight() const; 

		bool operator==( const AGSize& var );
		AGSize& operator=( const AGSize& var );

		AGSize operator+( const AGSize& var );
		AGSize& operator+=( const AGSize& var );

		AGSize operator-( const AGSize& var );
		AGSize& operator-=( const AGSize& var );

		AGSize operator*( float var );
		AGSize operator*=( float var );
		
		AGSize operator/( float var );
		AGSize operator/=( float var );
	private:
		float m_width;
		float m_height;
};

#endif 