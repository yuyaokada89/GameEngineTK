//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// �J�����𐧌䂷��N���X
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>



class Camera
{
public:
	/*�����o�[�֐�*/

	/*�R���X�g���N�^*/
	Camera(int width,int height);

	/*�f�X�g���N�^*/
	virtual ~Camera();

	/*�X�V*/
	virtual void Update();

	/*�r���[�s����擾*/
	const DirectX::SimpleMath::Matrix& GetView();

	/*�ˉe�s����擾*/
	const DirectX::SimpleMath::Matrix& GetProj();

	/*���_���Z�b�g*/
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);
	/*�����_/�Q�Ɠ_���Z�b�g*/
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);
	/*������x�N�g�����Z�b�g*/
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);

	/*������������p���Z�b�g*/
	void SetFovY(float fovY);

	/*�A�X�y�N�g��(�c�E���̔䗦)���Z�b�g*/
	void SetAspect(float aspect);

	/*��O�̕\�����E�������Z�b�g*/
	void SetNearClip(float nearclip);

	/*���̕\�����E�������Z�b�g*/
	void SetFarClip(float farcllip);

protected:
	/*�ޗ��͂�����(�����o�ϐ�)*/
	/*�r���[�s��*/
	DirectX::SimpleMath::Matrix m_view;
	/*�ǂ����猩��̂�(���_)*/
	DirectX::SimpleMath::Vector3 m_eyepos;
	/*�ǂ�������̂�(�����_/�Q�Ɠ_)*/
	DirectX::SimpleMath::Vector3 m_refpos;
	/*�ǂ��炪��ʏ������(������x�N�g��)*/
	DirectX::SimpleMath::Vector3 m_upvec;
	/*�v���W�F�N�V�����s��*/
	DirectX::SimpleMath::Matrix m_proj;
	/*������������p*/
	float m_fovY;
	/*�A�X�y�N�g��(�c�E���̔䗦)*/
	float m_aspect;
	/*��O�̕\�����E����*/
	float m_nearclip;
	/*���̕\�����E����*/
	float m_farclip;

};