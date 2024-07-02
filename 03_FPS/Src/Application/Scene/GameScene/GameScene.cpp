#include "GameScene.h"
#include"../SceneManager.h"
#include"../../main.h"
#include "../../GameObject/Characters/Player/Player.h"
#include "../../GameObject/Terrains/Terrain/Terrain.h"
#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"

void GameScene::Event()
{
	//おためし
	/*static float test = 0;

	test += 0.3;
	
	Application::Instance().m_log.AddLog("test:%f\n", test);*/
}

void GameScene::Init()
{
	//カーソル非表示
	ShowCursor(false);

	std::shared_ptr<Player> _player;
	_player = std::make_shared<Player>();
	_player->Init();
	m_objList.push_back(_player);

	std::shared_ptr<FPSCamera> _camera;
	_camera = std::make_shared<FPSCamera>();
	_camera->Init();
	_camera->SetTarget(_player);
	_player->SetCamera(_camera);
	m_objList.push_back(_camera);

	std::shared_ptr<Terrain> _terrain;
	_terrain = std::make_shared<Terrain>();
	_terrain->Init();
	m_objList.push_back(_terrain);
}
