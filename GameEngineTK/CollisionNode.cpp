#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// CollisionNode�̃����o�֐�
/// </summary>

void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetParent(parent);
}

/// <summary>
/// SphereNode�̃����o�֐�
/// </summary>

SphereNode::SphereNode()
{
	/*�f�t�H���g���a��1���[�g���ɂ���*/
	m_LocalRadius = 1.0f;
}

void SphereNode::Initialize()
{
	/*�f�o�b�O�\���p���f����ǂݍ���*/
	m_Obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_Obj.SetTranslation(m_Trans);
	m_Obj.SetScale(Vector3(m_LocalRadius));
	m_Obj.Update();
}

void SphereNode::Draw()
{
	m_Obj.Draw();
}

