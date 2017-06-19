//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Collision.cpp
//!
//! @brief  �����蔻��pcpp
//!
//! @date   2017/06/15
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//----------------------------------------------------------------------
//! @brief ���Ƌ��̂����蔻��
//!
//! @param[in] ��A�A��B
//!
//! @return true:�@�q�b�g false:�@�q�b�g����
//----------------------------------------------------------------------
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	/*��A��B�̒��S���W�̍����v�Z����*/
	Vector3 sub = sphereB.Center - sphereA.Center;

	/*�����̓��*/
	float distanceSquare;

	/*�O�����̒藝�ŋ������Z�o*/
	distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	/*���a�̓��*/
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	/*���������a�̘a���傫����Γ������Ă��Ȃ�*/
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}