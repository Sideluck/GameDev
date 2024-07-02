#include "Ground.h"

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Ground::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Ground.gltf");

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(100.0f);

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, 0, 0);

	m_mWorld = scaleMat * transMat;

	//コライダー(当たり判定の情報)の初期化(登録)
	m_pCollider = std::make_unique<KdCollider>();  //生成
	m_pCollider->RegisterCollisionShape			   //判定情報
	(
		"Ground",				//登録名
		m_model,				//モデルデータ
		KdCollider::TypeGround  //判定種類
	);
}
