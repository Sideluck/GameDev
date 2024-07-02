#pragma once

#include"../BaseScene/BaseScene.h"

//前方宣言
class Player;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	//プレイヤーの情報
	std::weak_ptr<Player>m_player;
	//スマートポインタの種類は3つ
	//shared_ptr ...シェア出来る(参照カウンタがある、アクセス可能)
	//weak_ptr   ...シェア出来る(参照カウンタがない、アクセス不可能)
	//unique_ptr ...シェア出来ない(1つのポインタでしか所有出来ない)

};
