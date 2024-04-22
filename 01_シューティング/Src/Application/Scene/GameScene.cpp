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
}

void GameScene::Draw()
{
	/*m_player->Draw();

	m_enemy->Draw();*/
}

void GameScene::init()
{
	//m_player=new Player();				//生ポインタ インスタンス生成
	//m_player = std::make_shared<Player>();	// スマートポインタ インスタンス生成
	//m_player->Init();

	//m_enemy = std::make_shared<Enemy>();
	//m_enemy->Init();
	//m_player->SetOwner(this);
}

void GameScene::Release()
{
	//delete m_player;	//生ポインタ インスタンス削除
}
