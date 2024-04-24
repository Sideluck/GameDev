#pragma once

class BaseObject
{
public:
	BaseObject(){}
	virtual ~BaseObject(){}

	//objectの種類
	enum class ObjectType
	{
		Player,
		Enemy,
	};

	//仮想関数
	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

	void SetTexture(std::string _fileName);

	ObjectType GetObjType() { return m_objType; }

	Math::Vector3 GetPos() { return m_pos; }

	//Hit時の処理
	virtual void OnHit();

protected:

	KdTexture		m_tex;
	Math::Matrix	m_mat;
	Math::Vector3	m_pos;

	bool			m_aliveFlg = true;

	ObjectType		m_objType;
};