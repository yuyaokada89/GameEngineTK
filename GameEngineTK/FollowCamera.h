///_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// ���@�ɒǏ]����J�����N���X
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#pragma once

#include "Camera.h"
#include "FollowCamera.h"
#include "Player.h"
#include <Keyboard.h>

class FollowCamera : public Camera
{
public:

	/*���@�ƃJ�����̋���*/
	static const float CAMERA_DISTANCE;

	/*�R���X�g���N�^*/
	FollowCamera(int width, int height);

	/*���t���[���X�V*/
	void Update() override;

	/*�Ǐ]�Ώۂ̍��W���Z�b�g*/
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);

	/*�Ǐ]�Ώۂ̍��W���Z�b�g*/
	void SetTargetAngle(float targetangle);

	/*�L�[�{�[�h���Z�b�g*/
	void SetKeybord(DirectX::Keyboard* keybord);

	/*�v���C���[���Z�b�g*/
	void SetPlayer(Player* player) { m_player = player; }

protected:

	/*�Ǐ]�Ώۂ̍��W*/
	DirectX::SimpleMath::Vector3 m_targetPos;

	/*�Ǐ]�Ώۂ̉�]�p*/
	float m_targetAngle;

	/*�L�[�{�[�h*/
	DirectX::Keyboard* m_keybord;
	/*�L�[�{�[�h�g���b�J�[*/
	DirectX::Keyboard::KeyboardStateTracker m_keybordTracker;

	/*FPS�J�����t���O*/
	bool m_isFPS;

	/*�v���C���[*/
	Player* m_player;
};

