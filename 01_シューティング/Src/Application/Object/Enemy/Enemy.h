#pragma once

#include "../BaseObject.h"

class Enemy : public BaseObject
{
public:
	Enemy(){}
	~Enemy(){ Release(); }

	void Init()override;
	void Draw()override;
	void Update()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetPos(float _x, float _y) { m_pos = { _x, _y,0.0f }; }	//SetPosのオーバーロード

	void SetMovePow(Math::Vector3 _movePow) { m_movePow = _movePow; }

private:

	Math::Vector3 m_movePow;

	void Release()override;

};