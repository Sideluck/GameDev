#include "Attack.h"
#include "../../Scene/SceneManager.h"

void Attack::Init()
{
	//板ポリゴンにテクスチャをセット
	m_polygon.SetMaterial("Asset/Textures/Attack.png");

	//板ポリゴンの原点(真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//画像分割
	m_polygon.SetSplit(9, 1);

	m_pos = {};
	m_movePow = { 0.0f, 0.0f, 0.0f };

	//実際の使用するコマ
	m_animeCnt = 0;

	//アニメーション速度
	m_animeSpeed = 0.3f;

	//攻撃判定のエリア
	m_searchArea = 0.3f;

	m_aliveflg = false;

	//行列
	m_mWorld = Math::Matrix::Identity;

	//デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Attack::Update()
{
	m_pos += m_movePow;

	m_polygon.SetUVRect((int)m_animeCnt);
	m_animeCnt += m_animeSpeed;

	//最後のコマまで表示し終えたらループさせる
	if (m_animeCnt > 9)
	{
		m_isExpired = true;
	}

	//球判定
	
	//球判定用の変数を作成
	KdCollider::SphereInfo sphereInfo;
	//球の中心位置を設定
	sphereInfo.m_sphere.Center =m_pos + Math::Vector3(0, 0.5f, 0);
	//球の半径を設定
	sphereInfo.m_sphere.Radius = m_searchArea;
	//当たり判定をしたいタイプを設定
	sphereInfo.m_type = KdCollider::TypeDamage;
	//レイに当たったオブジェクト情報を格納するリストを生成
	std::list<KdCollider::CollisionResult>retSphereList;

	//デバッグ用
	m_pDebugWire->AddDebugSphere(sphereInfo.m_sphere.Center, sphereInfo.m_sphere.Radius, kRedColor);

	//球情報と当たり判定
	bool hit = false;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		hit = obj->Intersects(sphereInfo, nullptr);

		//攻撃が当たった場合
		if (hit)
		{
			//Hit時の相手のオブジェクトの処理
			obj->OnHit();

			//Hit時の自分の処理
			OnHit();

			//ループから抜ける
			break;
		}
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Attack::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Attack::OnHit()
{
	KdAudioManager::Instance().Play("Asset/Sounds/Slash.wav");
	m_isExpired = true;
}
