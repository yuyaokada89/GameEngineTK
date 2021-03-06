//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Collision.cpp
//!
//! @brief  あたり判定用cpp
//!
//! @date   2017/06/15
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//----------------------------------------------------------------------
//! @brief 球と球のあたり判定
//!
//! @param[in] 球A、球B
//!
//! @return true:　ヒット false:　ヒットせず
//----------------------------------------------------------------------
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	/*球AとBの中心座標の差を計算する*/
	Vector3 sub = sphereB.Center - sphereA.Center;

	/*距離の二乗*/
	float distanceSquare;

	/*三平方の定理で距離を算出*/
	distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	/*半径の二乗*/
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	/*距離が半径の和より大きければ当たっていない*/
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}