#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// CollisionNodeのメンバ関数
/// </summary>

void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetParent(parent);
}

/// <summary>
/// SphereNodeのメンバ関数
/// </summary>

SphereNode::SphereNode()
{
	/*デフォルト半径を1メートルにする*/
	m_LocalRadius = 1.0f;
}

void SphereNode::Initialize()
{
	/*デバッグ表示用モデルを読み込む*/
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

