#include "Player.h"
#include "../../Scene/GameScene.h"
#include "../Bullet/Bullet.h"

void Player::Init()
{
	std::shared_ptr<Bullet>bullet;
	for (int i = 0; i < 10; i++)
	{
		bullet = std::make_shared<Bullet>();
		bullet->Init();
	
		bullet->SetPos(m_pos);
	}

	m_tex.Load("Asset/Textures/Player.png");
	m_pos = {};							//0,0で初期化
	m_objType = ObjectType::Player;		//種類はプレイヤー
	m_mat = Math::Matrix::Identity;		//単位行列で初期化


	//単位行列・・・拡大率全て1.0，他の値は0
}

void Player::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 64, 64, &rc);
}

void Player::Update()
{
	if (GetAsyncKeyState('W') & 0x8000|| GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 5.0f;
	}
	if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 5.0f;
	}
	if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 5.0f;
	}
	if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 5.0f;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		std::shared_ptr<Bullet>bullet;
		bullet = std::make_shared<Bullet>();
		bullet->Init();							//初期化
					//発射Ⅰ
		bullet->SetPos(m_pos);					//オーナー
		bullet->SetMovePow({ 0, 10.0f, 0 });	

		m_owner->AddObject(bullet);
	}

	//プレイヤーと敵の当たり判定
	for (auto&obj:m_owner->GetObjList())
	{
		//自分自身とは当たり判定をしない
		if (obj->GetObjType()==ObjectType::Player)
		{
			continue;
		}
		//敵なら当たり判定を行う
		if (obj->GetObjType()==ObjectType::Enemy)
		{
			//対象座標-自身の座標＝対象へのベクトル
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			//球判定...ベクトルの長さで判定
			if (v.Length() < 64.0f)
			{
				obj->OnHit();
				break;
			}
		}
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Player::Release()
{
	//自動リリースされるのでいらない
}
