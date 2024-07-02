#pragma once

class CameraBase;

class Player : public KdGameObject
{
public:
	Player(){}
	virtual ~Player()override{}

	void Update()override;

	void Init()override;

	void SetCamera(const std::shared_ptr<CameraBase>& camera)
	{
		m_wpCamera = camera;
	}

private:

	//カメラ情報
	std::weak_ptr<CameraBase>m_wpCamera;

	//ワールド座標
	Math::Vector3 m_pos = Math::Vector3::Zero;

	//進行方向(ベクトルの向き)
	Math::Vector3 m_moveDir= Math::Vector3::Zero;

	//移動速度(ベクトルの大きさ)
	const float m_moveSpeed = 0.3f;

};