#include "Enemy.h"

void Enemy::Init()
{
	m_tex.Load("Asset/Textures/enemy.png");
	m_pos = {};
	m_movePow = { 0.0f, -2.0f, 0.0f};
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
	m_pos += m_movePow;

	if (m_pos.y < -360 - 32)
	{
		m_pos.y = 360 + 32;
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Enemy::OnHit()
{
	m_aliveFlg = false;
}

void Enemy::Release()
{
}
