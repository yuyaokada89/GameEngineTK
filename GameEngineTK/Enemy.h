//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Enemy.h
//!
//! @brief  �G�̃w�b�_�[�t�@�C��
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

	/*���@�p�[�c*/
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

	/*�R���X�g���N�^*/
	Enemy();

	/*�f�X�g���N�^*/
	~Enemy();

	/*������*/
	void Initialize();
	/*�X�V*/
	void Update();
	/*�`��*/
	void Draw();

	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetTrans();
	// ��]���擾
	const DirectX::SimpleMath::Vector3& GetRot();
	// ���W��ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// ��]��ݒ�
	void SetRot(const DirectX::SimpleMath::Vector3& rot);

	/*�e�ۗp�����蔻����擾*/
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; }

protected:

	/*�����o�ϐ�*/
	/*���@�̉�]�p*/
	float Enemy_angle;

	/*�^�C�}�[*/
	int m_Timer;
	/*�ڕW�̊p�x*/
	float m_DistAngle;

	/*���@��3D�I�u�W�F�N�g*/
	std::vector<Obj3d>m_ObjEnemy;


	/*��]�p(XYZ)*/
	DirectX::SimpleMath::Vector3	m_roration;
	/*���s�ړ�(XYZ)*/
	DirectX::SimpleMath::Vector3	m_translation;

	/*�e�ۗp�̂����蔻��*/
	SphereNode m_CollisionNodeBullet;
};
