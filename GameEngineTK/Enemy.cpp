//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  プレイヤーのcpp
//!
//! @date   2017/06/02
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/*ヘッダーファイルのインクルード*/
#include "Enemy.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

//----------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param[in]
//!
//! @return なし
//----------------------------------------------------------------------
Enemy::Enemy()
{
	Initialize();
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{

	/*自機パーツの読み込み*/
	m_ObjEnemy.resize(ENEMY_PARTS_NUM);
	m_ObjEnemy[ENEMY_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_ObjEnemy[ENEMY_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD].LoadModel(L"Resources/shield.cmo");
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD].LoadModel(L"Resources/shield.cmo");
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD2].LoadModel(L"Resources/shield.cmo");
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD2].LoadModel(L"Resources/shield.cmo");
	m_ObjEnemy[ENEMY_PARTS_DRILL].LoadModel(L"Resources/drill.cmo");
	m_ObjEnemy[ENEMY_PARTS_HEAD].LoadModel(L"Resources/Pit.cmo");

	/*パーツの親子関係をセット*/
	m_ObjEnemy[ENEMY_PARTS_BODY].SetParent(&m_ObjEnemy[ENEMY_PARTS_TANK]);
	m_ObjEnemy[ENEMY_PARTS_HEAD].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD2].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD2].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_DRILL].SetParent(&m_ObjEnemy[ENEMY_PARTS_TANK]);

	/*親からのオフセット(座標のずらし分)をセット*/
	m_ObjEnemy[ENEMY_PARTS_BODY].SetTranslation(Vector3(0, 0.5f, 0));
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD].SetTranslation(Vector3(0.5, 0.3f, 0));
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD].SetRotation(Vector3(0, 0, 0));
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD].SetTranslation(Vector3(-0.5, 0.3f, 0));
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD].SetRotation(Vector3(0, 0, XM_PI));
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD2].SetTranslation(Vector3(0.3, 0.7f, 0));
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD2].SetRotation(Vector3(0, 0, XM_PIDIV4));
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD2].SetTranslation(Vector3(-0.3, 0.7f, 0));
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD2].SetRotation(Vector3(0, 0, XM_PI - XM_PIDIV4));
	m_ObjEnemy[ENEMY_PARTS_HEAD].SetTranslation(Vector3(0, 0.4f, 0));

	/*初期配置*/

	// 初期配置
	Vector3 pos;
	pos.x = rand() % 10;
	pos.z = rand() % 10;

	this->SetTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;

	{/*弾丸用のあたり判定を設定*/
		m_CollisionNodeBullet.Initialize();
		/*親パーツを指定*/
		m_CollisionNodeBullet.SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
		m_CollisionNodeBullet.SetTrans(Vector3(0, 0.3f, 0));
		m_CollisionNodeBullet.SetLocalRadius(1.0f);
	}
}

//----------------------------------------------------------------------
//! @brief 更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Enemy::Update()
{

	m_Timer--;
	if (m_Timer < 0)
	{
		m_Timer = 60;
		// -0.5～+0.5の乱数
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// 自機の角度を回転させる
		Vector3 rotv = m_ObjEnemy[0].GetRotation();

		float angle = m_DistAngle - rotv.y;

		// 180度を超えていた場合、逆回りの方が近い
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}

		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		// 補間
		rotv.y += angle * 0.05f;

		SetRot(rotv);
	}


	///*Aキーが押されていたら*/
	//if (g_key.A)
	//{
	//	/*自機の角度を回転させる*/
	//	Enemy_angle += 0.03f;
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	m_ObjEnemy[0].SetRotation(Vector3(0, angle + 0.03f, 0));
	//}

	///*Dキーが押されていたら*/
	//if (g_key.D)
	//{
	//	/*自機の角度を回転させる*/
	//	Enemy_angle += -0.03f;
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	m_ObjEnemy[0].SetRotation(Vector3(0, angle - 0.03f, 0));
	//}

	// 機体が向いている方向に進む
	{
		// 移動量のベクトル
		Vector3 moveV(0, 0, -0.1f);
		// 移動量ベクトルを自機の角度分回転させる
		//moveV = Vector3::TransformNormal(moveV, tank_world);
		float angle = m_ObjEnemy[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動させる
		Vector3 pos = m_ObjEnemy[0].GetTranslation();
		m_ObjEnemy[0].SetTranslation(pos + moveV);
	}
	

	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin();
		it != m_ObjEnemy.end(); it++)
	{
		it->Update();
	}

	/*あたり判定の更新*/
	m_CollisionNodeBullet.Update();
}

//----------------------------------------------------------------------
//! @brief 描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Enemy::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin();
		it != m_ObjEnemy.end(); it++)
	{
		it->Draw();
	}

	m_CollisionNodeBullet.Draw();
}

const DirectX::SimpleMath::Vector3& Enemy::GetTrans()
{
	// タンクパーツの座標を返す
	return m_ObjEnemy[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3 & Enemy::GetRot()
{
	// タンクパーツの回転を返す
	return m_ObjEnemy[0].GetRotation();
}

void Enemy::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// タンクパーツの座標を設定
	m_ObjEnemy[0].SetTranslation(trans);
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// タンクパーツの座標を設定
	m_ObjEnemy[0].SetRotation(rot);
}

