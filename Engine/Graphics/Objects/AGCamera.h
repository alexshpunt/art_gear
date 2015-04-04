#ifndef AG_CAMERA_H
#define AG_CAMERA_H

#include <d3dx10.h>
#include <d3d10.h>

#include "Graphics/AGGraphics.h"

class AGCamera
{
	public:
		enum AGCameraType{ Ortho, Perspective };
		AGCamera( AGCameraType type = Perspective );
		~AGCamera();

		void setType( AGCameraType type );
		AGCameraType getType() const; 

		void setFov( float fov );
		float getFov() const; 

		void setAspectRatio( float aspectRatio );
		float getAspectRatio() const; 

		void setNearPlane( float nearPlane );
		float getNearPlane() const; 

		void setFarPlane( float farPlane );
		float getFarPlane() const; 

		void setSpeed( float speed );
		float getSpeed() const; 

		void setSprintSpeed( float sprintSpeed );
		float getSprintSpeed() const; 

		void setSensX( float sensX );
		float getSensX() const;

		void setSensY( float sensY );
		float getSensY() const; 

		void setLayer( int layer );
		int getLayer() const; 

		void setAt( D3DXVECTOR3 at );
		D3DXVECTOR3 getAt() const;

		void setUp( D3DXVECTOR3 up );
		D3DXVECTOR3 getUp() const;

		D3DXVECTOR3 getDir(); 

		void setEye( D3DXVECTOR3 forward );
		D3DXVECTOR3 getEye() const; 

		D3DXMATRIX getViewMatrix() const; 
		D3DXMATRIX getProjMatrix() const; 

		float getAngleX() const;
		float getAngleY() const; 

		void setTargetDistance( float dist );
		void update(); 
		void updateProj();
		void updateOrtho();  

		void rotateY( float angle );
		void rotateX( float angle ); 
		void rotate( float angleX, float angleY ); 

		void translateInDirection( float z );

	protected:
		float m_nearPlane;
		float m_farPlane;
		float m_aspectRatio;
		float m_speed;
		float m_sprintSpeed; 
		float m_sensX;
		float m_sensY;
		int m_layer;

		float m_targetDistance; 
		float m_angleX;
		float m_angleY; 

		D3DXVECTOR3 m_at;
		D3DXVECTOR3 m_up;
		D3DXVECTOR3 m_eye;

		D3DXMATRIX m_rotMatrix; 

		D3DXMATRIX m_viewMatrix;
		D3DXMATRIX m_projMatrix; 

		float m_vertSpeed;
		float m_horSpeed; 

		float m_fov;

		float m_zoom; 

		AGCameraType m_type;

		POINT m_mpos; 
};
#endif 