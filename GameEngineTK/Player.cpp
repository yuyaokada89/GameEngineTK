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
#include "Player.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

//----------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param[in] キーボード
//!
//! @return なし
//----------------------------------------------------------------------
Player::Player(DirectX::Keyboard* keyboard)
{
	/*キーボードの取得*/
	m_Keyboard = keyboard;

	/*自機パーツの読み込み*/
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].LoadModel(L"Resources/shield.cmo");
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].LoadModel(L"Resources/shield.cmo");
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].LoadModel(L"Resources/shield.cmo");
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].LoadModel(L"Resources/shield.cmo");
	m_ObjPlayer[PLAYER_PARTS_DRILL].LoadModel(L"Resources/drill.cmo");
	m_ObjPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/Pit.cmo");

	/*パーツの親子関係をセット*/
	m_ObjPlayer[PLAYER_PARTS_BODY].SetParent(&m_ObjPlayer[PLAYER_PARTS_TANK]);
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_DRILL].SetParent(&m_ObjPlayer[PLAYER_PARTS_TANK]);

	/*親からのオフセット(座標のずらし分)をセット*/
	m_ObjPlayer[PLAYER_PARTS_BODY].SetTranslation(Vector3(0, 0.5f, 0));
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(Vector3(0.5, 0.3f, 0));
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetRotation(Vector3(0, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetTranslation(Vector3(-0.5, 0.3f, 0));
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetRotation(Vector3(0, 0, XM_PI));
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetTranslation(Vector3(0.3, 0.7f, 0));
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetRotation(Vector3(0, 0, XM_PIDIV4));
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetTranslation(Vector3(-0.3, 0.7f, 0));
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetRotation(Vector3(0, 0, XM_PI - XM_PIDIV4));
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetTranslation(Vector3(0, 0.4f, 0));

	FireFlag = false;

	timer = 0.0f;

	{/*弾丸用のあたり判定を設定*/
		m_CollisionNodeBullet.Initialize();
		/*親パーツを指定*/
		m_CollisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD]);
		m_CollisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		m_CollisionNodeBullet.SetLocalRadius(0.5f);
	}
}

//----------------------------------------------------------------------
//! @brief 更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Player::Update()
{

	/*キーボードの状態取得*/
	Keyboard::State g_key = m_Keyboard->GetState();
	m_KeyboardTracker.Update(g_key);

	/*自機パーツのギミック*/
	/*Kキーが押されていたら*/
	if (g_key.K)
	{
		
		Vector3 pos = m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].GetTranslation();
		m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetTranslation(pos -= Vector3(0.0, 0, 0.1f));
		Vector3 pos2 = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].GetTranslation();
		m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(pos2 -= Vector3(0.0, 0, 0.1f));
		Vector3 pos3 = m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].GetTranslation();
		m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetTranslation(pos3 -= Vector3(0, 0, 0.1f));
		Vector3 pos4 = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].GetTranslation();
		m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetTranslation(pos4 -= Vector3(0, 0, 0.1f));

		/*posが-3以下なら*/
		if (pos.z < -3)
		{
			m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetTranslation(pos += Vector3(0.0, 0, 0.1f));
			m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(pos2 += Vector3(0.0, 0, 0.1f));
			m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetTranslation(pos3 += Vector3(0, 0, 0.1f));
			m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetTranslation(pos4 += Vector3(0, 0, 0.1f));

			Vector3 angle = m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].GetRotation();
			m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetRotation(angle -= Vector3(0, 0.1f, 0));
			Vector3 angle2 = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].GetRotation();
			m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetRotation(angle2 += Vector3(0, 0.1f, 0));
			Vector3 angle3 = m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].GetRotation();
			m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetRotation(angle3 -= Vector3(0, 0.1f, 0));
			Vector3 angle4 = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].GetRotation();
			m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetRotation(angle4 += Vector3(0, 0.1f, 0));

			/*angleのyが-1以下なら*/
			if (angle.y < -1)
			{
				m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetRotation(angle += Vector3(0, 0.1f, 0));
				m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetRotation(angle2 -= Vector3(0, 0.1f, 0));
				m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetRotation(angle3 += Vector3(0, 0.1f, 0));
				m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetRotation(angle4 -= Vector3(0, 0.1f, 0));
			}
		}
	}
	/*Lキーが押されていたら*/
	if (g_key.L)
	{
		Vector3 backangle = m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].GetRotation();
		m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetRotation(backangle += Vector3(0, 0.1f, 0));
		Vector3 backangle2 = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].GetRotation();
		m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetRotation(backangle2 -= Vector3(0, 0.1f, 0));
		Vector3 backangle3 = m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].GetRotation();
		m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetRotation(backangle3 += Vector3(0, 0.1f, 0));
		Vector3 backangle4 = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].GetRotation();
		m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetRotation(backangle4 -= Vector3(0, 0.1f, 0));

		/*backangleのyが0以上なら*/
		if (backangle.y > 0)
		{

			m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetRotation(backangle -= Vector3(0, 0.1f, 0));
			m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetRotation(backangle2 += Vector3(0, 0.1f, 0));
			m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetRotation(backangle3 -= Vector3(0, 0.1f, 0));
			m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetRotation(backangle4 += Vector3(0, 0.1f, 0));

			Vector3 backpos = m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].GetTranslation();
			m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetTranslation(backpos += Vector3(0,0,0.1f));
			Vector3 backpos2 = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].GetTranslation();
			m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(backpos2 += Vector3(0, 0,0.1f));
			Vector3 backpos3 = m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].GetTranslation();
			m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetTranslation(backpos3 += Vector3(0,0,0.1f));
			Vector3 backpos4 = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].GetTranslation();
			m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetTranslation(backpos4 += Vector3(0,0,0.1f));

			/*backposのzが0以上なら*/
			if (backpos.z > 0)
			{
				m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetTranslation(backpos -= Vector3(0.0, 0, 0.1f));
				m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(backpos2 -= Vector3(0.0, 0, 0.1f));
				m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetTranslation(backpos3 -= Vector3(0, 0, 0.1f));
				m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetTranslation(backpos4 -= Vector3(0, 0, 0.1f));
			}
		}
	}

	/*Aキーが押されていたら*/
	if (g_key.A)
	{
		/*自機の角度を回転させる*/
		Player_angle += 0.03f;
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	/*Dキーが押されていたら*/
	if (g_key.D)
	{
		/*自機の角度を回転させる*/
		Player_angle += -0.03f;
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(Vector3(0, angle - 0.03f, 0));
	}

	/*Wキーが押されていたら*/
	if (g_key.W)
	{
		/*移動量のベクトル*/
		Vector3 moveV(0, 0, -0.1f);

		/*移動量ベクトルを自機の角度分回転させる*/
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmatY = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmatY);

		/*自機の座標の移動*/
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		m_ObjPlayer[0].SetTranslation(pos + moveV);
	}

	/*Sキーが押されていたら*/
	if (g_key.S)
	{
		/*移動量のベクトル*/
		Vector3 moveV(0, 0, 0.1f);

		/*移動量ベクトルを自機の角度分回転させる*/
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmatY = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmatY);

		/*自機の座標の移動*/
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		m_ObjPlayer[0].SetTranslation(pos + moveV);
	}

	if (g_key.Space)
	{
		if (!FireFlag)
		{
			FireBullet();	
		}
		else
		{
			ResetBullet();
		}
	}

	/*弾丸を前進させる処理*/
	if(FireFlag)
	{

		/*自機の座標の移動*/
		Vector3 pos = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].GetTranslation();
		m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(pos + m_BulletVel);
		timer++;
		if (timer >= 120)
		{
			timer = 0;
			ResetBullet();
		}
		
	}
	



	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end(); it++)
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
void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end(); it++)
	{
		it->Draw();
	}

	m_CollisionNodeBullet.Draw();
}

void Player::FireBullet()
{
	/*発射するパーツのワールド行列を取得*/
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].GetWorld();

	/*ワールド行列から各要素を抽出*/
	Vector3 scale;				/*ワールドスケーリング*/
	Quaternion rotation;		/*ワールド回転*/
	Vector3 trancelation;		/*ワールド座標*/

	worldm.Decompose(scale, rotation, trancelation);

	/*発射パーツを親から分離して独立*/
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetParent(nullptr);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetScale(scale);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetRotationQ(rotation);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(trancelation);

	/*弾丸の速度を設定*/
	m_BulletVel = Vector3(0, 0, -0.1f);
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

	FireFlag = true;

	
}

void Player::ResetBullet()
{
	if (!FireFlag)return;
	//Matrix World = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].GetWorld();
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetScale(Vector3(1, 1, 1));
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetRotation(Vector3(0, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(Vector3(0.5f, 0.3f, 0));

	FireFlag = false;

	
}


