//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Collision.h
//!
//! @brief  �����蔻��p�w�b�_�[�t�@�C��
//!
//! @date   2017/06/15
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include <d3d11.h>
#include <SimpleMath.h>



/*��*/
class Sphere
{
public:
	/*���S���W*/
	DirectX::SimpleMath::Vector3 Center;
	/*���a*/
	float Radius;

	/*�R���X�g���N�^*/
	Sphere()
	{
		Radius = 1.0f;
	}
};


/*����*/
class Segment
{
public:
	/*�n�_*/
	DirectX::SimpleMath::Vector3 Start;
	/*�I�_*/
	DirectX::SimpleMath::Vector3 End;
};

/*�J�v�Z��(�����X�E�B�[�g�����`��)*/
class Capsule
{
	/*�c��*/
	Segment Segment;
	/*���a*/
	float Radius;
	/*�R���X�g���N�^*/
	Capsule()
	{
		Segment.Start = DirectX::SimpleMath::Vector3(0, 0, 0);
		Segment.End = DirectX::SimpleMath::Vector3(0, 1, 0);
		Radius = 1.0f;
	}
};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
