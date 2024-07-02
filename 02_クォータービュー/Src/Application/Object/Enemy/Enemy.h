#pragma once

//前方宣言
class Player;

class Enemy:public KdGameObject
{
public:
	Enemy() {}
	~Enemy() override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetTarget(std::weak_ptr<Player>_target);

	void OnHit()override;

private:

	//板ポリゴン
	std::shared_ptr<KdSquarePolygon> m_polygon;

	//座標
	Math::Vector3 m_pos;

	//方向
	Math::Vector3 m_dir;

	//移動量(ベクトルの大きさ)
	float m_speed;

	//重力
	float m_gravity;

	//実際の使用するコマ
	float m_animeCnt;

	//アニメーション速度
	float m_animeSpeed;

	//プレイヤーの情報
	std::weak_ptr<Player>m_target;

	bool m_chaseFlg = false;
	float m_searchArea;

};