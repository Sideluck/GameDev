#pragma once

class BaseObject
{
public:
	BaseObject(){}
	virtual ~BaseObject(){}

	//仮想関数
	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

	void SetTexture(std::string _fileName);

protected:

	KdTexture m_tex;
	Math::Matrix m_mat;
	Math::Vector3 m_pos;

	bool m_aliveFlg = false;
};