#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/BackGround/BackGround.h"
#include"../../Object/Ground/Ground.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Enemy/Enemy.h"

void GameScene::Event()
{
	//プレイヤーの座標を取得する
	Math::Vector3 playerPos = {};

	//weak_ptrで所持している m_player が有効かどうか調べる
	//expired()...期限切れならtrueを返す
	if (m_player.expired() == false)
	{
		//lockしたことによりweak_ptrをshared_ptrにして返してもらう
		playerPos = m_player.lock()->GetPos();
	}

	Math::Matrix _mRotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));

	Math::Matrix _mTransPos = Math::Matrix::CreateTranslation(Math::Vector3(0, 3, -3) + playerPos);

	Math::Matrix _mWorld = _mRotationX *_mTransPos;

	m_camera->SetCameraMatrix(_mWorld);
}

void GameScene::Init()
{
	/*m_camera = std::make_shared<KdCamera>();
	std::shared_ptr<KdCamera> p2;
	p2 = m_camera;*/

	//カメラ   生成&視野角
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);

//背景
	//メモリ生成
	std::shared_ptr<BackGround> back;
	back = std::make_shared<BackGround>();

	//初期化
	back->Init();

	//リストへ追加
	m_objList.push_back(back);

//地面
	std::shared_ptr<Ground> ground;
	ground = std::make_shared<Ground>();

	ground->Init();

	m_objList.push_back(ground);

//プレイヤー
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();

	player->Init();

	m_objList.push_back(player);

//プレイヤーの情報を保持しておく
	m_player = player;

//敵
	std::shared_ptr<Enemy> enemy;
	for (int i = 0; i < 20; i++)
	{
		enemy = std::make_shared<Enemy>();

		enemy->Init();

		enemy->SetTarget(player);

		enemy->SetPos({ -50.0f + 10.0f * i,0,20 });

		m_objList.push_back(enemy);
	}
}
