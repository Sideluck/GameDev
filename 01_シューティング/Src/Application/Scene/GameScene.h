#pragma once

class Player;
class BaseObject;

class GameScene
{
public:
	GameScene() {}
	~GameScene() { Release(); } //破棄時にRelease

	void PreUpdate();	//更新前の処理
	void Update();		
	void Draw();	    
	void init();		

private:

	void Release();  //外部に呼ばれたくないのでprivate

	//Player* m_player = nullptr;			//派生クラスのポインタ
	//BaseObject* m_player = nullptr;		//基底クラスのポインタ
	//std::shared_ptr<Player> m_player;		//スマートポインタ
	//std::shared_ptr<BaseObject> m_player;	//スマートポインタ
	//std::shared_ptr<BaseObject> m_enemy;	

	//全オブジェクトをのリストを可変長配列化
	std::vector<std::shared_ptr<BaseObject>> m_objList;
};