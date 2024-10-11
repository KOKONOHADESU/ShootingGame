#include "Player.h"

#include "../../Util/DxLibSystem.h"

#include <DxLib.h>
#include <math.h>
#include <algorithm>

namespace
{
	// �T�C�Y
	constexpr float kSize = 3.0f;

	// �p�x
	constexpr float kRota = 0.0f;

	// ���x
	constexpr float kSpeed = 15.0f;

	// �̗�
	constexpr int kHitPoint = 30;

	// �����ʒu
	constexpr Vec2 kStartPos = { DxLibSystem::kScreenWidthF / 2.0f , DxLibSystem::kScreenHeightF - 300.0f };

	// �����@�̗p
	Airframe kAirframe{ kStartPos , kSize , kRota ,kHitPoint };

	// ����̑傫��
	constexpr float kLeftXSize  = 35.0f;
	constexpr float kLeftYSize  = 35.0f;
	constexpr float kRightXSize = 35.0f;
	constexpr float kRightYSize = 50.0f;

	// �v���C���[�摜�p�X
	const char* const kPlayerPath = "Data/Image/Player/Player1.png";
}

Player::Player():
	m_hGraph(-1),
	m_airframe(kAirframe),
	m_collRect({ 0.0f,0.0f ,0.0f,0.0f }),
	m_shootingNum(0)
{
	// �������m��
	m_hGraph = LoadGraph(kPlayerPath);

	// ����p�ʒu���W�X�V
	CollRectUpdate();
}

Player::~Player()
{
	// ���������
	DeleteGraph(m_hGraph);
}

void Player::Update()
{
	// ����
	Input();

	// ��ʊO����
	OutSide();

	// ����p�ʒu���W�X�V
	CollRectUpdate();
}

void Player::Draw()
{
	// �v���C���[�̕`��
	DrawRotaGraphF(m_airframe.pos.x, m_airframe.pos.y, m_airframe.size, m_airframe.rota, m_hGraph, true);

#if _DEBUG
	// ����p�f�o�b�O�`��
	DrawBox(m_collRect.left.x, m_collRect.left.y, m_collRect.right.x, m_collRect.right.y, 0xff0000, false);
#endif
}

Vec2 Player::GetPos() const
{
	return m_airframe.pos;
}

Rect Player::GetCollData()const
{
	return m_collRect;
}

int Player::GetShootingNum()const
{
	return m_shootingNum;
}

void Player::Input()
{
	// �x�N�g��
	Vec2 vec = {0.0f,0.0f};

	// �ړ�
	if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP))
	{
		vec.y += -1.0f;
	}
	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT))
	{
		vec.x += -1.0f;
	}
	if (CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_DOWN))
	{
		vec.y += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT))
	{
		vec.x += 1.0f;
	}

	// �V���b�g
	if (CheckHitKey(KEY_INPUT_SPACE) || GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		// ���˂��鐔���w��
		m_shootingNum = 1;
	}
	else
	{
		m_shootingNum = 0;
	}

	// �x�N�g���̒������v�Z
	const float length = sqrtf(vec.x * vec.x + vec.y * vec.y);

	// ������0�łȂ��ꍇ�̂݃m�[�}���C�Y
	if (length > 0.0f)
	{
		vec.x /= length;
		vec.y /= length;
	}

	// �ʒu��ύX
	m_airframe.pos.x += vec.x * kSpeed;
	m_airframe.pos.y += vec.y * kSpeed;
}

void Player::OutSide()
{
	// ��
	m_airframe.pos.x = (std::max)(m_airframe.pos.x, 0.0f);

	// �E
	m_airframe.pos.x = (std::min)(m_airframe.pos.x, DxLibSystem::kScreenWidthF);

	// ��
	m_airframe.pos.y = (std::max)(m_airframe.pos.y, 0.0f);

	// ��
	m_airframe.pos.y = (std::min)(m_airframe.pos.y, DxLibSystem::kScreenHeightF);
}

void Player::CollRectUpdate()
{
	m_collRect.left.x  = m_airframe.pos.x - kLeftXSize;
	m_collRect.left.y  = m_airframe.pos.y - kLeftYSize;
	m_collRect.right.x = m_airframe.pos.x + kRightXSize;
	m_collRect.right.y = m_airframe.pos.y + kRightYSize;
}
