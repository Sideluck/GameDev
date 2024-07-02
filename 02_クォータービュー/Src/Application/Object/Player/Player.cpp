#include "Player.h"
#include "../../Scene/SceneManager.h"
#include "../Attack/Attack.h"

void Player::Init()
{
	//板ポリゴンにテクスチャをセット
	m_polygon.SetMaterial("Asset/Textures/Player.png");

	//板ポリゴンの原点(真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//アニメーション分割数:横、縦
	m_polygon.SetSplit(4, 8);

	//初期アニメーション情報
	m_animeInfo.start = 4;     //開始コマ
	m_animeInfo.end   = 7;     //終了コマ
	m_animeInfo.count = 0;     //現在のコマ数カウント
	m_animeInfo.speed = 0.2f;  //アニメーションの速度

	//向いている方向
	m_dirType = DirType::Down;

	//座標・移動速度
	m_pos = {};
	m_dir = {};
	m_speed = 0.1f;
	m_attackDir = {};
	m_ara = {};

	//重力
	//0.0で初期化しないとバグが発生する
	m_gravity = 0.0f;

	//行列
	m_mWorld = Math::Matrix::Identity;

	//デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

}

void Player::Update()
{
	//移動関係をクリア
	m_dir = {};
	UINT oldDirType = m_dirType;   //前回の方向タイプを退避
	m_dirType = 0;                 //ビット列をクリア

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_dir += {0, 0, 1};
		m_dirType |= DirType::Up;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_dir += {0, 0, -1};
		m_dirType |= DirType::Down;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_dir += {-1, 0, 0};
		m_ara += {1, 0, 0};
		m_dirType |= DirType::Left;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_dir += {1, 0, 0};
		m_ara += {-1, 0, 0};
		m_dirType |= DirType::Right;
	}
	
	//向きが変わっていればアニメーション情報変更
	if (m_dirType != 0 && m_dirType != oldDirType)
	{
		ChangeAnimetion();

		//向きを確定させる
		m_attackDir = m_dir;
		m_attackDir.Normalize();
	}
	else
	{
		m_dirType = oldDirType;	  //変わっていないなら元の向き(退避データ)に戻す
	}

	//向きを正規化
	m_dir.Normalize();

	//座標 += ベクトルの方向(1.0f固定)*ベクトルの量(向きに対して移動させたい量)
	m_pos += m_dir * m_speed;

	//ジャンプ
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity = -0.1f;
	}

	//重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	if (GetAsyncKeyState('Z') & 0x8000)
	{
		if (!m_keyFlg)
		{
			m_keyFlg = true;
			
			//攻撃オブジェクトを出現させる
			Math::Vector3 _attackPos = {};
			_attackPos  = m_pos;
			_attackPos += m_attackDir * 0.4;
			
			//攻撃オブジェクトを作成
			
				std::shared_ptr<Attack>attack;
				attack = std::make_shared<Attack>();
				attack->Init();
				attack->SetPos(_attackPos);
				if (m_dirType & DirType::Left)
				{
					attack->SetMovePow({ -0.1f,0 , 0 });
				}
				if (m_dirType & DirType::Right)
				{
					attack->SetMovePow({ 0.1f,0 , 0 });
				}
				SceneManager::Instance().AddObject(attack);
			

			//攻撃SE再生
			KdAudioManager::Instance().Play("Asset/Sounds/Attack.WAV");
			//Sounds 二個目の引数 falseなら単発  trueならループ  デフォルト引数はfalse
			//KdAudioManager::Instance().Play("Asset/Sounds/Attack.WAV",true);
			//他にも色んな機能がある！
			//KdAudioManager::Instance().StopAllSound();
		}
	}
	else
	{
		m_keyFlg = false;
	}

	//アニメーション更新

	m_animeInfo.count += m_animeInfo.speed;
	int animeCnt= m_animeInfo.count + m_animeInfo.start;

	//最後のコマまで表示し終えたらループさせる
	if (animeCnt > m_animeInfo.end)
	{
		animeCnt = m_animeInfo.start;
		m_animeInfo.count = 0;
	}


	m_polygon.SetUVRect(animeCnt);

	//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
	//当たり判定・・・レイ判定  ここから
	//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
	
	//レイ判定用に必要なパラメーターを設定する構造体を宣言
	KdCollider::RayInfo rayInfo;

	//レイの発射位置(座標)を設定
	rayInfo.m_pos = m_pos;

	//少し高いところから飛ばす
	//rayInfo.m_pos.y += 0.1f;//中央下段が原点なので少し上から

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
	bool          hit        = false;
	float         maxOverLap = 0;
	Math::Vector3 groundPos  = {};	//レイが遮断された(Hitした)座標
	for (auto& ret : retRayList)
	{
		//レイが当たった場合の貫通した長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos  = ret.m_hitPos;
			hit		   = true;
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

void Player::PostUpdate()
{
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(Math::Vector3(m_pos));
	m_mWorld = transMat;
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::ChangeAnimetion()
{
	//方向別にアニメーション情報をセット

	if (m_dirType & DirType::Up)
	{
		m_animeInfo.start = 24;
		m_animeInfo.end = 27;
		//m_attackDir = { 0,0,1 };
	}
	if (m_dirType & DirType::Down)
	{
		m_animeInfo.start = 4;
		m_animeInfo.end = 7;
		//m_attackDir = { 0, 0, -1 };
	}
	if (m_dirType & DirType::Left)
	{
		m_animeInfo.start = 12;
		m_animeInfo.end = 15;
		//m_attackDir = { -1, 0, 0 };
	}
	if (m_dirType & DirType::Right)
	{
		m_animeInfo.start = 16;
		m_animeInfo.end = 19;
		//m_attackDir = { 1, 0, 0 };
	}

	//斜め方向

	if (m_dirType == (DirType::Up|DirType::Left))
	{
		m_animeInfo.start = 20;
		m_animeInfo.end = 23;
		//m_attackDir = { -1,0,1 };
	}
	if (m_dirType == (DirType::Up|DirType::Right))
	{
		m_animeInfo.start = 28;
		m_animeInfo.end =31;
		//m_attackDir = { 1,0,1 };
	}
	if (m_dirType == (DirType::Down|DirType::Left))
	{
		m_animeInfo.start = 0;
		m_animeInfo.end = 3;
		//m_attackDir = { -1, 0, -1 };
	}
	if (m_dirType == (DirType::Down|DirType::Right))
	{
		m_animeInfo.start = 8;
		m_animeInfo.end = 11;
		//m_attackDir = { 1, 0, -1 };
	}

	//カウントとスピードを初期化
	m_animeInfo.count = 0;    
	m_animeInfo.speed = 0.2f;  

	/*switch (m_dirType)
	{
	case DirType::Up:
		m_animeInfo.start = 24;
		m_animeInfo.end = 27;
		break;	
	case DirType::Down:
		m_animeInfo.start = 4;
		m_animeInfo.end = 7;
		break;
	case DirType::Left:
		m_animeInfo.start = 12;
		m_animeInfo.end = 15;
		break;
	case DirType::Right:
		m_animeInfo.start = 16;
		m_animeInfo.end = 19;
		break;
	default:
		break;
	}*/


}
