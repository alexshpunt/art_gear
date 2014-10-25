#ifndef AGDX10_CAMERA_H
#define AGDX10_CAMERA_H

#include <d3dx10.h>
#include <d3d10.h>

class AGDX10Camera
{
	public:
		enum Manipulator{ Editor3D, FPS };

		AGDX10Camera();
		~AGDX10Camera();

		void setManipulator( Manipulator mode );
		int getManipulator() const; 

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

		void setEye( D3DXVECTOR3 forward );
		D3DXVECTOR3 getEye() const; 

		D3DXMATRIX getViewMatrix() const; 
		D3DXMATRIX getProjMatrix() const; 

		float getAngleX() const;
		float getAngleY() const; 

		void update(); 

	private:
		void moveAs3DEditor();
		void moveAsFPS(); 

		Manipulator m_mode; 
		float m_fov;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;
		float m_speed;
		float m_sprintSpeed; 
		float m_sensX;
		float m_sensY;
		int m_layer;

		float m_angleX;
		float m_angleY; 

		D3DXVECTOR3 m_at;
		D3DXVECTOR3 m_up;
		D3DXVECTOR3 m_eye;

		D3DXMATRIX m_rotMatrix; 

		D3DXMATRIX m_viewMatrix;
		D3DXMATRIX m_projMatrix; 
};

#endif 