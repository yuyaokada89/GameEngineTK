//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  �v���C���[�̃w�b�_�[�t�@�C��
//!
//! @date   2017/06/02
//!
//! @author Y.okada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/*�w�b�_�[�t�@�C���̃C���N���[�h*/
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

	/*���@�p�[�c*/
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

	/*�R���X�g���N�^*/
	Player(DirectX::Keyboard* keyboard);
	/*�X�V*/
	void Update();
	/*�`��*/
	void Draw();
	/*�e�ۂ𔭎�*/
	void FireBullet();
	/*�e�ۂ��đ���(���Z�b�g)*/
	void ResetBullet();

	/*getter*/
	/*��]�p(XYZ)*/
	DirectX::SimpleMath::Vector3 GetRotation() { return m_ObjPlayer[PLAYER_PARTS_TANK].GetRotation(); }
	/*���s�ړ�(XYZ)*/
	DirectX::SimpleMath::Vector3 GetTranslation() { return m_ObjPlayer[PLAYER_PARTS_TANK].GetTranslation(); }

	/*�e�ۗp�����蔻����擾*/
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; }

protected:

	/*�����o�ϐ�*/
	/*���@�̉�]�p*/
	float Player_angle;

	/*���@��3D�I�u�W�F�N�g*/
	std::vector<Obj3d>m_ObjPlayer;

	/*�L�[�{�[�h*/
	DirectX::Keyboard* m_Keyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	/*��]�p(XYZ)*/
	DirectX::SimpleMath::Vector3 m_roration;
	/*���s�ړ�(XYZ)*/
	DirectX::SimpleMath::Vector3 m_translation;

	/*�e�ۂ̑��x�x�N�g��*/
	DirectX::SimpleMath::Vector3 m_BulletVel;

	bool FireFlag;

	float timer;

	/*�e�ۗp�̂����蔻��*/
	SphereNode m_CollisionNodeBullet;
};
