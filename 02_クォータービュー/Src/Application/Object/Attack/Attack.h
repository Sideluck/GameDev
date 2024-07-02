#pragma once

class Attack :public KdGameObject
{
public:

	Attack(){}
	~Attack()override{}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;

	void OnHit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetMovePow(Math::Vector3 _movePow) { m_movePow = _movePow; }

private:

	KdSquarePolygon m_polygon;

	Math::Vector3 m_pos;
	Math::Vector3 m_movePow;

	//実際の使用するコマ
	float m_animeCnt;

	//アニメーション速度
	float m_animeSpeed;

	//攻撃判定のエリア
	float m_searchArea;

	bool m_aliveflg;
};