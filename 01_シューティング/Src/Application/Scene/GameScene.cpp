#include "GameScene.h"

#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"

void GameScene::PreUpdate()
{
}

void GameScene::Update()
{
	/*m_player->Update();
	m_enemy->Update();*/

	//3%の確率で敵を出す
	
	if (rand() % 100 < 3)
	{
		std::shared_ptr<Enemy>enemy;
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos((640.0f + 32.0f), 0);
		enemy->SetMovePow({ -2.0f, -2.0f, 0});
		m_objList.push_back(enemy);
	}


	//謎の動き
	/*for (int i = 0; i < m_objList.size(); i++)
	{
		if (rand() % 3)
		{
			m_objList[i]->Update();
		}
	}*/
	
	//全オブジェクトの更新関数を一括で呼ぶ
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Update();
	}
}

void GameScene::Draw()
{
	/*m_player->Draw();

	m_enemy->Draw();*/
	/*for (auto& obj:m_objList)
	{
		obj->Draw();
	}*/

	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Draw();
	}
}

void GameScene::init()
{
	//m_player=new Player();				//生ポインタ インスタンス生成
	//m_player = std::make_shared<Player>();	// スマートポインタ インスタンス生成
	//m_player->Init();
	//m_player->SetOwner(this);
	std::shared_ptr<Player>player;
	player = std::make_shared<Player>();
	player->Init();
	player->SetOwner(this);
	m_objList.push_back(player);	//リストへ追加

	std::shared_ptr<Enemy>enemy;
	for (int i = 0; i < 10; i++)
	{
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		//enemy->SetPos((-640.0f + 32.0f) + i * 128.0f, 360.0f - 32.0f);
		enemy->SetPos((-640.0f + 32.0f) + i * 128.0f, (360.0f - 32.0f) - i * 70.0f);
		m_objList.push_back(enemy);
	}

	//m_enemy = std::make_shared<Enemy>();
	//m_enemy->Init();
}

void GameScene::Release()
{
	//delete m_player;	//生ポインタ インスタンス削除
}
