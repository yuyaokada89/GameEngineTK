#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera(int width, int height)
{
	/*�����o�ϐ��̏�����*/
	m_eyepos = Vector3(0, 0, 5.0f);
	m_refpos = Vector3(0, 0, 0);
	m_upvec = Vector3(0, 1, 0);

	m_fovY =DirectX::XMConvertToRadians(60.0f);
	m_aspect = (float)width / height;
	m_nearclip = 0.1f;
	m_farclip = 1000.0f;



	/*�r���[�s��̐���*/
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	/*�ˉe�s��̐���(�������e)*/
	m_proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

Camera::~Camera()
{

}

void Camera::Update()
{
	/*�r���[�s��̐���*/
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	/*�ˉe�s��̐���(�������e)*/
	m_proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

/*�r���[�s����擾*/
const DirectX::SimpleMath::Matrix& Camera::GetView()
{
	return m_view;
}
 
/*�ˉe�s����擾*/
const DirectX::SimpleMath::Matrix& Camera::GetProj()
{
	return m_proj;
}

/*���_���Z�b�g*/
void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& eyepos)
{
	m_eyepos = eyepos;
}

/*�����_/�Q�Ɠ_���Z�b�g*/
void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos =refpos;

}

/*������x�N�g�����Z�b�g*/
void Camera::SetUpVec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}

/*������������p���Z�b�g*/
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

/*�A�X�y�N�g��(�c�E���̔䗦)���Z�b�g*/
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

/*��O�̕\�����E�������Z�b�g*/
void Camera::SetNearClip(float nearclip)
{
	m_nearclip = nearclip;
}

/*���̕\�����E�������Z�b�g*/
void Camera::SetFarClip(float farclip)
{
	m_farclip = farclip;
}

