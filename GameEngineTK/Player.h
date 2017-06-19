//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  プレイヤーのヘッダーファイル
//!
//! @date   2017/06/02
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/*ヘッダーファイルのインクルード*/
#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"
#include "CollisionNode.h"


class Player 
{
public:

	/*自機パーツ*/
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_TANK,
		PLAYER_PARTS_BODY,
		PLAYER_PARTS_HEAD,
		PLAYER_PARTS_LEFTSHIELD,
		PLAYER_PARTS_RIGHTSHIELD,
		PLAYER_PARTS_LEFTSHIELD2,
		PLAYER_PARTS_RIGHTSHIELD2,
		PLAYER_PARTS_DRILL,

		PLAYER_PARTS_NUM
	};

	/*コンストラクタ*/
	Player(DirectX::Keyboard* keyboard);
	/*更新*/
	void Update();
	/*描画*/
	void Draw();
	/*弾丸を発射*/
	void FireBullet();
	/*弾丸を再装着(リセット)*/
	void ResetBullet();

	/*getter*/
	/*回転角(XYZ)*/
	DirectX::SimpleMath::Vector3 GetRotation() { return m_ObjPlayer[PLAYER_PARTS_TANK].GetRotation(); }
	/*平行移動(XYZ)*/
	DirectX::SimpleMath::Vector3 GetTranslation() { return m_ObjPlayer[PLAYER_PARTS_TANK].GetTranslation(); }

	/*弾丸用あたり判定を取得*/
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; }

protected:

	/*メンバ変数*/
	/*自機の回転角*/
	float Player_angle;

	/*自機の3Dオブジェクト*/
	std::vector<Obj3d>m_ObjPlayer;

	/*キーボード*/
	DirectX::Keyboard* m_Keyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	/*回転角(XYZ)*/
	DirectX::SimpleMath::Vector3 m_roration;
	/*平行移動(XYZ)*/
	DirectX::SimpleMath::Vector3 m_translation;

	/*弾丸の速度ベクトル*/
	DirectX::SimpleMath::Vector3 m_BulletVel;

	bool FireFlag;

	float timer;

	/*弾丸用のあたり判定*/
	SphereNode m_CollisionNodeBullet;
};
