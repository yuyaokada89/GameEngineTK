//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  �v���C���[��cpp
//!
//! @date   2017/06/02
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/*�w�b�_�[�t�@�C���̃C���N���[�h*/
#include "Player.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

//----------------------------------------------------------------------
//! @brief �R���X�g���N�^
//!
//! @param[in] �L�[�{�[�h
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Player::Player(DirectX::Keyboard* keyboard)
{
	/*�L�[�{�[�h�̎擾*/
	m_Keyboard = keyboard;

	/*���@�p�[�c�̓ǂݍ���*/
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].LoadModel(L"Resources/shield.cmo");
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].LoadModel(L"Resources/shield.cmo");
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].LoadModel(L"Resources/shield.cmo");
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].LoadModel(L"Resources/shield.cmo");
	m_ObjPlayer[PLAYER_PARTS_DRILL].LoadModel(L"Resources/drill.cmo");
	m_ObjPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/Pit.cmo");

	/*�p�[�c�̐e�q�֌W���Z�b�g*/
	m_ObjPlayer[PLAYER_PARTS_BODY].SetParent(&m_ObjPlayer[PLAYER_PARTS_TANK]);
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_DRILL].SetParent(&m_ObjPlayer[PLAYER_PARTS_TANK]);

	/*�e����̃I�t�Z�b�g(���W�̂��炵��)���Z�b�g*/
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

	{/*�e�ۗp�̂����蔻���ݒ�*/
		m_CollisionNodeBullet.Initialize();
		/*�e�p�[�c���w��*/
		m_CollisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD]);
		m_CollisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		m_CollisionNodeBullet.SetLocalRadius(0.5f);
	}
}

//----------------------------------------------------------------------
//! @brief �X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Player::Update()
{

	/*�L�[�{�[�h�̏�Ԏ擾*/
	Keyboard::State g_key = m_Keyboard->GetState();
	m_KeyboardTracker.Update(g_key);

	/*���@�p�[�c�̃M�~�b�N*/
	/*K�L�[��������Ă�����*/
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

		/*pos��-3�ȉ��Ȃ�*/
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

			/*angle��y��-1�ȉ��Ȃ�*/
			if (angle.y < -1)
			{
				m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetRotation(angle += Vector3(0, 0.1f, 0));
				m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetRotation(angle2 -= Vector3(0, 0.1f, 0));
				m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetRotation(angle3 += Vector3(0, 0.1f, 0));
				m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetRotation(angle4 -= Vector3(0, 0.1f, 0));
			}
		}
	}
	/*L�L�[��������Ă�����*/
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

		/*backangle��y��0�ȏ�Ȃ�*/
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

			/*backpos��z��0�ȏ�Ȃ�*/
			if (backpos.z > 0)
			{
				m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD].SetTranslation(backpos -= Vector3(0.0, 0, 0.1f));
				m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(backpos2 -= Vector3(0.0, 0, 0.1f));
				m_ObjPlayer[PLAYER_PARTS_LEFTSHIELD2].SetTranslation(backpos3 -= Vector3(0, 0, 0.1f));
				m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD2].SetTranslation(backpos4 -= Vector3(0, 0, 0.1f));
			}
		}
	}

	/*A�L�[��������Ă�����*/
	if (g_key.A)
	{
		/*���@�̊p�x����]������*/
		Player_angle += 0.03f;
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	/*D�L�[��������Ă�����*/
	if (g_key.D)
	{
		/*���@�̊p�x����]������*/
		Player_angle += -0.03f;
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(Vector3(0, angle - 0.03f, 0));
	}

	/*W�L�[��������Ă�����*/
	if (g_key.W)
	{
		/*�ړ��ʂ̃x�N�g��*/
		Vector3 moveV(0, 0, -0.1f);

		/*�ړ��ʃx�N�g�������@�̊p�x����]������*/
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmatY = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmatY);

		/*���@�̍��W�̈ړ�*/
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		m_ObjPlayer[0].SetTranslation(pos + moveV);
	}

	/*S�L�[��������Ă�����*/
	if (g_key.S)
	{
		/*�ړ��ʂ̃x�N�g��*/
		Vector3 moveV(0, 0, 0.1f);

		/*�ړ��ʃx�N�g�������@�̊p�x����]������*/
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmatY = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmatY);

		/*���@�̍��W�̈ړ�*/
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

	/*�e�ۂ�O�i�����鏈��*/
	if(FireFlag)
	{

		/*���@�̍��W�̈ړ�*/
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

	/*�����蔻��̍X�V*/
	m_CollisionNodeBullet.Update();
}

//----------------------------------------------------------------------
//! @brief �`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
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
	/*���˂���p�[�c�̃��[���h�s����擾*/
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].GetWorld();

	/*���[���h�s�񂩂�e�v�f�𒊏o*/
	Vector3 scale;				/*���[���h�X�P�[�����O*/
	Quaternion rotation;		/*���[���h��]*/
	Vector3 trancelation;		/*���[���h���W*/

	worldm.Decompose(scale, rotation, trancelation);

	/*���˃p�[�c��e���番�����ēƗ�*/
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetParent(nullptr);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetScale(scale);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetRotationQ(rotation);
	m_ObjPlayer[PLAYER_PARTS_RIGHTSHIELD].SetTranslation(trancelation);

	/*�e�ۂ̑��x��ݒ�*/
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


