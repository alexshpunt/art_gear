#ifndef AG_INPUTMANAGER_H
#define AG_INPUTMANAGER_H

#include <map>
#include <string>
#include "Patterns/Singleton.h"
#include "Math/AGPoint2.h"

#define AGInput() AGInputManager::getInstance()

using namespace std;

typedef map< int, bool > KeysMap; 
typedef map< string, bool > ButtonsMap; 

class AGInputManager
{
	DECLARE_SINGLETON_INIT( AGInputManager )
	public:
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

		void setMousePos( AGPoint2 pos );
		const AGPoint2& getMousePos() const;
		AGPoint2 getMouseDeltaPos();

		void setWheelDelta( float wheelDelta );
		float getWheelDelta();
	private:
		void init(); 
		int fromNameToCode( string name );

		AGPoint2 m_mousePos;
		AGPoint2 m_mouseDeltaPos; 

		float m_wheelDelta; 

		KeysMap m_keyPressed; 
		KeysMap m_keyUp; 
		KeysMap m_keyDown; 

		ButtonsMap m_buttonsMapPressed; 
		ButtonsMap m_buttonsMapUp;
		ButtonsMap m_buttonsMapDown;  
};

#endif 