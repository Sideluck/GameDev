#include "Enemy.h"
#include "../../Scene/SceneManager.h"
#include "../Player/Player.h"

void Enemy::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Enemy.png");
	m_pos = { 0,0,0 };
	m_speed = 0.05;
	m_animeCnt = 0;
	m_animeSpeed = 0.1;
	m_searchArea = 3.0f;
	m_chaseFlg = false;

	//画像分割
	m_polygon->SetSplit(6, 6);

	//原点変更
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//重力
	m_gravity = 0.0f;

	//行列
	m_mWorld = Math::Matrix::Identity;

	//デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//コライダー(当たり判定の情報)の初期化(登録)
	m_pCollider = std::make_unique<KdCollider>();  //生成
	//判定情報
	m_pCollider->RegisterCollisionShape("Enemy",m_polygon, KdCollider::TypeDamage);
}

void Enemy::Update()
{

	//アニメーション処理
	int Walk[4] = { 3,4,3,5 };
	m_polygon->SetUVRect(Walk[(int)m_animeCnt]);
	m_animeCnt += m_animeSpeed;
	if (m_animeCnt >= 4)
	{
		m_animeCnt = 0;
	}

	//ターゲットを追従
	Math::Vector3 targetPos = {};

	if (m_target.expired() == false)
	{
		//lock・・・weakをsharedに変換
		targetPos = m_target.lock()->GetPos();

		//対象との距離で判定 球判定
		Math::Vector3 v = targetPos - m_pos;
		//ベクトルの長さが一定以上なら追従
		if (v.Length() < m_searchArea)
		{
			m_chaseFlg = true;
		}
		else
		{
			m_chaseFlg = false;
		}

		if (m_chaseFlg)
		{
			//y軸を0にしておく 空を飛んで追いかけるのを防止
			v.y = 0.0f;

			//対象へのベクトルの長さを1に
			v.Normalize();

			//方向確定
			m_dir = v;
		}
		else
		{
			//対象がいない状態は動かない
			m_dir = {};
		}
	}

	m_pDebugWire->AddDebugSphere(m_pos+Math::Vector3(0,0.5f,0),m_searchArea, kGreenColor);

	//座標 += ベクトルの方向(1.0f固定)*ベクトルの量(向きに対して移動させたい量)
	m_pos += m_dir * m_speed;

	//重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;



	//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
	//当たり判定・・・レイ判定  ここから
	//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆

	//レイ判定用に必要なパラメーターを設定する構造体を宣言
	KdCollider::RayInfo rayInfo;

	//レイの発射位置(座標)を設定
	rayInfo.m_pos = m_pos;

	//レイの方向を設定
	rayInfo.m_dir = { 0,-1.0f,0 };

	//段差の許容範囲を設定
	static const float enableStepHigh = 0.2f;
	rayInfo.m_pos.y += enableStepHigh;

	//レイの長さを設定
	rayInfo.m_range = m_gravity + enableStepHigh;

	//当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;

	//デバッグ用の情報としてライン描画を追加
	m_pDebugWire->AddDebugLine(rayInfo.m_pos, rayInfo.m_dir, rayInfo.m_range);

	//レイに当たったオブジェクト情報を格納するリストを生成
	std::list<KdCollider::CollisionResult> retRayList;

	//作成したレイ情報でオブジェクトリストと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &retRayList);
	}

	//レイに当たったリストから一番近いオブジェクトを検出
	bool          hit = false;
	float         maxOverLap = 0;
	Math::Vector3 groundPos = {};	//レイが遮断された(Hitした)座標
	for (auto& ret : retRayList)
	{
		//レイが当たった場合の貫通した長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			hit = true;
		}
	}

	//当たっていたら
	if (hit)
	{
		m_pos = groundPos;
		m_gravity = 0;
	}

	//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
	//当たり判定・・・レイ判定  ここまで
	//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
}

void Enemy::PostUpdate()
{
	//座標更新
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(Math::Vector3(m_pos));
	m_mWorld = transMat;
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Enemy::SetTarget(std::weak_ptr<Player> _target)
{
	//_targetがshared_ptrとして有効なら
	if (_target.expired() == false)
	{
		m_target = _target;
	}
}

void Enemy::OnHit()
{
	KdAudioManager::Instance().Play("Asset/Sounds/kiyo-voice.wav");
	m_isExpired = true;
}
