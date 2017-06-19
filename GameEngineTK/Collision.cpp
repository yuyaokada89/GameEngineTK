//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Collision.cpp
//!
//! @brief  ‚ ‚½‚è”»’è—pcpp
//!
//! @date   2017/06/15
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//----------------------------------------------------------------------
//! @brief ‹…‚Æ‹…‚Ì‚ ‚½‚è”»’è
//!
//! @param[in] ‹…AA‹…B
//!
//! @return true:@ƒqƒbƒg false:@ƒqƒbƒg‚¹‚¸
//----------------------------------------------------------------------
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	/*‹…A‚ÆB‚Ì’†SÀ•W‚Ì·‚ğŒvZ‚·‚é*/
	Vector3 sub = sphereB.Center - sphereA.Center;

	/*‹——£‚Ì“ñæ*/
	float distanceSquare;

	/*O•½•û‚Ì’è—‚Å‹——£‚ğZo*/
	distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	/*”¼Œa‚Ì“ñæ*/
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	/*‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚Î“–‚½‚Á‚Ä‚¢‚È‚¢*/
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}