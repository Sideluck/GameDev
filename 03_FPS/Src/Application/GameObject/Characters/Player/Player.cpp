#include "Player.h"
#include "../../../GameObject/Camera/FPSCamera/FPSCamera.h"

void Player::Update()
{
	if (GetAsyncKeyState('D')) { m_moveDir += {1,0,0}; }
	if (GetAsyncKeyState('A')) { m_moveDir += {-1,0,0}; }
	if (GetAsyncKeyState('W')) { m_moveDir += {0,0,1}; }
	if (GetAsyncKeyState('S')) { m_moveDir += {0,0,-1}; }

	m_pos = m_moveDir * m_moveSpeed;

	const std::shared_ptr<CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		m_pos =
			m_pos.TransformNormal(m_pos, _spCamera->GetRotationYMatrix());
	}

	Math::Matrix TransMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = TransMat;
}

void Player::Init()
{

}
