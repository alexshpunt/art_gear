#ifndef AG_INPUTMANAGER_H
#define AG_INPUTMANAGER_H

#include <map>
#include <deque>
#include <string>
#include "Patterns/Singleton.h"
#include "Math/AGPoint2.h"

#define AGInput() AGInputManager::getInstance()

using namespace std;


typedef map< int, bool > KeysMap; 
typedef map< string, bool > ButtonsMap; 

enum AGMouseButton { LMB, RMB, MMB };

class AGInputManager
{
	DECLARE_SINGLETON_INIT( AGInputManager )
	public:
		void update(); 

		void setKeyPressed( int key, bool flag );
		bool isKeyPressed( int key ); 
		bool isKeyDown( int key );
		bool isKeyUp( int key );

		bool isKeyPressed( string key );
		bool isKeyDown( string key );
		bool isKeyUp( string key );

		void setButtonPressed( const string& button, bool flag );
		bool isButtonPressed( const string& button );
		bool isButtonDown( const string& button );
		bool isButtonUp( const string& button );

		void setMousePos( AGPoint2 pos, bool lockDelta = false );
		void setMouseDeltaPos( AGPoint2 deltaPos );
		const AGPoint2& getMousePos() const;

		AGPoint2 getMouseDeltaPos();
		AGPoint2 getMouseDelta(); 

		void setWheelDelta( float wheelDelta );
		float getWheelDelta();

		void setCharInput( wchar_t charInput ); 
		bool isCharInput() const; 
		char getCharInput(); 
		wchar_t getWCharInput(); 
	private:
		void init(); 
		int fromNameToCode( string name );

		bool m_lockDelta; 
		AGPoint2 m_mousePos;
		AGPoint2 m_mouseDeltaPos; 

		float m_wheelDelta; 

		KeysMap m_keyPressed; 
		KeysMap m_keyUp; 
		KeysMap m_keyDown; 

		ButtonsMap m_buttonsMapPressed; 
		ButtonsMap m_buttonsMapUp;
		ButtonsMap m_buttonsMapDown;  

		deque< AGPoint2 > m_mouseStack; 

		bool m_isCharInput; 
		wchar_t m_charInput; 
};

#endif 