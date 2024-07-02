#pragma once

#include "../BaseObject.h"

class GameScene;

class Bullet:public BaseObject
{
public:
	Bullet(){}
	~Bullet(){ Release(); }

	void Init()override;
	void Draw()override;
	void Update()override;

	void OnHit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetPos(float _x, float _y) { m_pos = { _x, _y,0.0f }; }	//SetPosのオーバーロード

	void SetOwner(GameScene* _owner) { m_owner = _owner; }

	void SetMovePow(Math::Vector3 _movePow) { m_movePow = _movePow; }

private:

	GameScene* m_owner = nullptr;

	Math::Vector3 m_movePow;

	void Release()override;

};