//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   CollisionNode.h
//!
//! @brief  あたり判定ノードヘッダーファイル
//!
//! @date   2017/06/19
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include "Collision.h"
#include "Obj3d.h"

/*当たり判定ノード*/
class CollisionNode
{
public:
	/*初期化*/
	virtual void Initialize() = 0;
	/*毎フレーム更新*/
	virtual void Update() = 0;
	/*描画*/
	virtual void Draw() = 0;
	/*親をセット*/
	void SetParent(Obj3d* parent);
	/*親からのオフセットをセット*/
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }
protected:
	/*デバッグ表示用オブジェクト*/
	Obj3d m_Obj;
	/*親からのオフセット*/
	DirectX::SimpleMath::Vector3 m_Trans;
};

/*球当たり判定ノード*/
class SphereNode :public CollisionNode, public Sphere
{
public:
	/*コンストラクタ*/
	SphereNode();
	/*初期化*/
	void Initialize();
	/*毎フレーム更新*/
	void Update();
	/*描画*/
	void Draw();

	void SetLocalRadius(float radius) { m_LocalRadius = radius; }

protected:
	/*ローカル半径*/
	float m_LocalRadius;
};


