#pragma once

class Player :public KdGameObject
{
public:

	enum DirType
	{
		Up     = 1 << 0,	//上
		Down   = 1 << 1,	//下
		Left   = 1 << 2,	//左
		Right  = 1 << 3,	//右
	};

	struct AnimationInfo
	{
		int start;		//開始コマ
		int end;		//終了コマ
		float count;    //現在のコマ数カウント
		float speed;	//アニメーションの速度
	};

	Player(){}
	~Player() override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

private:

	void ChangeAnimetion();

	//板ポリゴン
	KdSquarePolygon m_polygon;

	//キャラが向いている方向種類 ビット管理
	UINT m_dirType;

	AnimationInfo m_animeInfo;

	//座標
	Math::Vector3 m_pos;

	//方向
	Math::Vector3 m_dir;

	//攻撃方向
	Math::Vector3 m_attackDir;
	Math::Vector3 m_ara;

	//移動量(ベクトルの大きさ)
	float m_speed;

	//重力
	float m_gravity;

	//押しっぱ防止
	bool m_keyFlg = false;

};