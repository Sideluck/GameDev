#include "Bullet.h"

#include "../../Scene/GameScene.h"

void Bullet::Init()
{
	m_tex.Load("Asset/Textures/Bullet.png");
	m_pos = {};
	m_movePow = { 0.0f, 10.0f, 0.0f };
	m_objType = ObjectType::Bullet;
	m_mat = Math::Matrix::Identity;
}

void Bullet::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0,0,13,37 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 13, 37, &rc);
}

void Bullet::Update()
{
	m_pos += m_movePow;

	for (auto& obj : m_owner->GetObjList())
	{
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			if (v.Length() < 32.0f)
			{
				obj->OnHit();
				OnHit();
				break;
			}
		}
	}

	if (m_pos.y > 360)
	{
		m_aliveFlg = false;
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Bullet::OnHit()
{
	m_aliveFlg = false;
}

void Bullet::Release()
{
}
