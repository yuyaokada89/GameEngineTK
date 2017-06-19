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
#include "Enemy.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

//----------------------------------------------------------------------
//! @brief �R���X�g���N�^
//!
//! @param[in]
//!
//! @return �Ȃ�
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

	/*���@�p�[�c�̓ǂݍ���*/
	m_ObjEnemy.resize(ENEMY_PARTS_NUM);
	m_ObjEnemy[ENEMY_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_ObjEnemy[ENEMY_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD].LoadModel(L"Resources/shield.cmo");
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD].LoadModel(L"Resources/shield.cmo");
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD2].LoadModel(L"Resources/shield.cmo");
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD2].LoadModel(L"Resources/shield.cmo");
	m_ObjEnemy[ENEMY_PARTS_DRILL].LoadModel(L"Resources/drill.cmo");
	m_ObjEnemy[ENEMY_PARTS_HEAD].LoadModel(L"Resources/Pit.cmo");

	/*�p�[�c�̐e�q�֌W���Z�b�g*/
	m_ObjEnemy[ENEMY_PARTS_BODY].SetParent(&m_ObjEnemy[ENEMY_PARTS_TANK]);
	m_ObjEnemy[ENEMY_PARTS_HEAD].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_RIGHTSHIELD2].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_LEFTSHIELD2].SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_DRILL].SetParent(&m_ObjEnemy[ENEMY_PARTS_TANK]);

	/*�e����̃I�t�Z�b�g(���W�̂��炵��)���Z�b�g*/
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

	/*�����z�u*/

	// �����z�u
	Vector3 pos;
	pos.x = rand() % 10;
	pos.z = rand() % 10;

	this->SetTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;

	{/*�e�ۗp�̂����蔻���ݒ�*/
		m_CollisionNodeBullet.Initialize();
		/*�e�p�[�c���w��*/
		m_CollisionNodeBullet.SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
		m_CollisionNodeBullet.SetTrans(Vector3(0, 0.3f, 0));
		m_CollisionNodeBullet.SetLocalRadius(1.0f);
	}
}

//----------------------------------------------------------------------
//! @brief �X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Enemy::Update()
{

	m_Timer--;
	if (m_Timer < 0)
	{
		m_Timer = 60;
		// -0.5�`+0.5�̗���
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// ���@�̊p�x����]������
		Vector3 rotv = m_ObjEnemy[0].GetRotation();

		float angle = m_DistAngle - rotv.y;

		// 180�x�𒴂��Ă����ꍇ�A�t���̕����߂�
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}

		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		// ���
		rotv.y += angle * 0.05f;

		SetRot(rotv);
	}


	///*A�L�[��������Ă�����*/
	//if (g_key.A)
	//{
	//	/*���@�̊p�x����]������*/
	//	Enemy_angle += 0.03f;
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	m_ObjEnemy[0].SetRotation(Vector3(0, angle + 0.03f, 0));
	//}

	///*D�L�[��������Ă�����*/
	//if (g_key.D)
	//{
	//	/*���@�̊p�x����]������*/
	//	Enemy_angle += -0.03f;
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	m_ObjEnemy[0].SetRotation(Vector3(0, angle - 0.03f, 0));
	//}

	// �@�̂������Ă�������ɐi��
	{
		// �ړ��ʂ̃x�N�g��
		Vector3 moveV(0, 0, -0.1f);
		// �ړ��ʃx�N�g�������@�̊p�x����]������
		//moveV = Vector3::TransformNormal(moveV, tank_world);
		float angle = m_ObjEnemy[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�������
		Vector3 pos = m_ObjEnemy[0].GetTranslation();
		m_ObjEnemy[0].SetTranslation(pos + moveV);
	}
	

	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin();
		it != m_ObjEnemy.end(); it++)
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
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_ObjEnemy[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3 & Enemy::GetRot()
{
	// �^���N�p�[�c�̉�]��Ԃ�
	return m_ObjEnemy[0].GetRotation();
}

void Enemy::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_ObjEnemy[0].SetTranslation(trans);
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_ObjEnemy[0].SetRotation(rot);
}

