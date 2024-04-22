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

private:

	void Release()override;

};