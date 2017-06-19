//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Enemy.h
//!
//! @brief  敵のヘッダーファイル
//!
//! @date   2017/06/02
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "Obj3d.h"
#include <Keyboard.h>
#include <vector>
#include "CollisionNode.h"


class Enemy
{
public:

	/*自機パーツ*/
	enum PLAYER_PARTS
	{
		ENEMY_PARTS_TANK,
		ENEMY_PARTS_BODY,
		ENEMY_PARTS_HEAD,
		ENEMY_PARTS_LEFTSHIELD,
		ENEMY_PARTS_RIGHTSHIELD,
		ENEMY_PARTS_LEFTSHIELD2,
		ENEMY_PARTS_RIGHTSHIELD2,
		ENEMY_PARTS_DRILL,

		ENEMY_PARTS_NUM
	};

	/*コンストラクタ*/
	Enemy();

	/*デストラクタ*/
	~Enemy();

	/*初期化*/
	void Initialize();
	/*更新*/
	void Update();
	/*描画*/
	void Draw();

	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetTrans();
	// 回転を取得
	const DirectX::SimpleMath::Vector3& GetRot();
	// 座標を設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// 回転を設定
	void SetRot(const DirectX::SimpleMath::Vector3& rot);

	/*弾丸用あたり判定を取得*/
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; }

protected:

	/*メンバ変数*/
	/*自機の回転角*/
	float Enemy_angle;

	/*タイマー*/
	int m_Timer;
	/*目標の角度*/
	float m_DistAngle;

	/*自機の3Dオブジェクト*/
	std::vector<Obj3d>m_ObjEnemy;


	/*回転角(XYZ)*/
	DirectX::SimpleMath::Vector3	m_roration;
	/*平行移動(XYZ)*/
	DirectX::SimpleMath::Vector3	m_translation;

	/*弾丸用のあたり判定*/
	SphereNode m_CollisionNodeBullet;
};
