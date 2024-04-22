#include "Enemy.h"

void Enemy::Init()
{
	m_tex.Load("Asset/Textures/enemy.png");
	m_pos = { 0, 0, 0 };
	m_mat = Math::Matrix::Identity;
}

void Enemy::Draw()
{
	Math::Rectangle rct;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rct = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 64, 64, &rct);
}

void Enemy::Update()
{
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Enemy::Release()
{
}
