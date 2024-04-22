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

private:

	void Release()override;

};