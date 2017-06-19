#include "Obj3d.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

/*静的メンバ変数の実体*/

/*デバイス*/
Microsoft::WRL::ComPtr<ID3D11Device>            Obj3d::m_d3dDevice;

/*デバイスコンテキスト*/
Microsoft::WRL::ComPtr<ID3D11DeviceContext>     Obj3d::m_d3dContext;

/*カメラ*/
Camera* Obj3d::m_Camera;

/*汎用描画ステート*/
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;

//エフェクトファクトリ
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	/*汎用描画ステート生成*/
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	// エフェクトファクトリ生成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	// テクスチャの読み込みパス指定
	m_factory->SetDirectory(L"Resources");
}

Obj3d::Obj3d()
{
	/*スケールは1倍がデフォルト*/
	m_scale = Vector3(1, 1, 1);
	
	m_parent = nullptr;

	/*デフォルトでは、オイラー角で計算*/
	m_UseQuaternion = false;
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	/*モデルの読み込み*/
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obj3d::Update()
{
	/*主に行列の計算*/
	/*スケーリング行列*/
	Matrix scalemat = Matrix::CreateScale(m_scale);
	/*回転行列*/
	Matrix rotmat;
	if (m_UseQuaternion)
	{/*クォーターニオンで回転を計算*/
		rotmat = Matrix::CreateFromQuaternion(m_rorationQ);
	}
	else
	{/*オイラー角で回転を計算(Z→X→Y)*/
		Matrix rotmatZ = Matrix::CreateRotationZ(m_roration.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_roration.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_roration.y);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}
	/*平行移動*/
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	/*ワールド行列の合成(親の行列もかける)*/
	m_world = scalemat* rotmat * transmat;

	/*親の行列をかける*/
	if (m_parent)
	{
		m_world *= m_parent->m_world;
	}
}

void Obj3d::Draw()
{
	assert(m_Camera);

	//*3Dモデルの描画*/
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetView(), m_Camera->GetProj());
	}
}
