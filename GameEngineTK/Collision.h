//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Collision.h
//!
//! @brief  あたり判定用ヘッダーファイル
//!
//! @date   2017/06/15
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include <d3d11.h>
#include <SimpleMath.h>



/*球*/
class Sphere
{
public:
	/*中心座標*/
	DirectX::SimpleMath::Vector3 Center;
	/*半径*/
	float Radius;

	/*コンストラクタ*/
	Sphere()
	{
		Radius = 1.0f;
	}
};


/*線分*/
class Segment
{
public:
	/*始点*/
	DirectX::SimpleMath::Vector3 Start;
	/*終点*/
	DirectX::SimpleMath::Vector3 End;
};

/*カプセル(球をスウィートした形状)*/
class Capsule
{
	/*芯線*/
	Segment Segment;
	/*半径*/
	float Radius;
	/*コンストラクタ*/
	Capsule()
	{
		Segment.Start = DirectX::SimpleMath::Vector3(0, 0, 0);
		Segment.End = DirectX::SimpleMath::Vector3(0, 1, 0);
		Radius = 1.0f;
	}
};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
