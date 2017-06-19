#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/*静的メンバ変数の初期化*/
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

FollowCamera::FollowCamera(int width, int height)
	:Camera(width,height)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0;
	m_keybord = nullptr;
	m_isFPS = false;
	m_player = nullptr;
}

void FollowCamera::Update()
{
	/*キーボードの状態取得*/
	Keyboard::State keybordstate = m_keybord->GetState();
	m_keybordTracker.Update(keybordstate);

	/*Cキーを押すごとにFPS/TPSを切り替え*/
	//if (m_keybordTracker.IsKeyPressed(Keyboard::Keys::C))
	//{
	//	/*フラグを切り替え*/
	//	m_isFPS = !m_isFPS;
	//}

	if (m_player)
	{
		/*目標座標の設定*/
		SetTargetPos(m_player->GetTranslation());
		SetTargetAngle(m_player->GetRotation().y);
	}


	/*視点、参照点座標*/
	Vector3 eyepos, refpos;
	if (!m_isFPS)
	{/*TPSカメラ*/
		
		/*自機の上空2mを参照点とする*/
		refpos = m_targetPos + Vector3(0, 2, 0);

		/*参照点と視点の差分のベクトル*/
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		/*自機の後ろに回り込むための回転行列を生成*/
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		/*差分ベクトルを回転させる*/
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		/*視点座標を計算*/
		eyepos = refpos + cameraV;

		/*視点を現在位置から補間する*/
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;

		/*参照点を現在の位置から補間する*/
		refpos = m_refpos + (refpos - m_refpos) * 0.25;


		SetEyePos(eyepos);
		SetRefPos(refpos);

	}
	else
	{/*FPSカメラ*/

		/*自機の目の位置あたりを参照点とする*/
		Vector3 position;

		position = m_targetPos + Vector3(0, 0.2f, 0);

		/*参照点と視点の差分のベクトル*/
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);

		/*自機の後ろに回り込むための回転行列を生成*/
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		/*差分ベクトルを回転させる*/
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = position + cameraV * 0.1f;

		/*視点座標を計算*/
		refpos = position + cameraV;

		SetEyePos(eyepos);
		SetRefPos(refpos);

	}


	/*基底クラスの更新*/
	Camera::Update();
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos)
{
	m_targetPos = targetpos;
}

void FollowCamera::SetTargetAngle(float targetangle)
{
	m_targetAngle = targetangle;
}

void FollowCamera::SetKeybord(DirectX::Keyboard * keybord)
{
	m_keybord = keybord;
}


