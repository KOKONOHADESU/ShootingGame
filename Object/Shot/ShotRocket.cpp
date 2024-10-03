#include "ShotRocket.h"

#include "../../Util/MTRandom.h"

namespace
{
	// �T�C�Y
	constexpr float kSize = 2.5f;

	// �p�x
	constexpr float kRota = 0.0f;

	// ���x
	constexpr float kSpeed = 10.0f;

	// �̗�
	constexpr int kHitPoint = 1000000;

	// �_���[�W
	constexpr int kDamage = 10;

	// ����̑傫��
	constexpr float kLeftXSize  = 20.0f;
	constexpr float kLeftYSize  = 20.0f;
	constexpr float kRightXSize = 20.0f;
	constexpr float kRightYSize = 20.0f;

	// �q�b�g�����ۂ̔��j����̑傫��
	constexpr float kExplosionLeftXSize  = 100.0f;
	constexpr float kExplosionLeftYSize  = 100.0f;
	constexpr float kExplosionRightXSize = 100.0f;
	constexpr float kExplosionRightYSize = 100.0f;
}


ShotRocket::ShotRocket(Vec2 startPos, const std::vector<int>& handle) :
	ShotBase::ShotBase(startPos, handle),
	m_isExplosion(false)
{
	// �e�̏�����
	m_bullet.pos = startPos;
	m_bullet.size = kSize;
	m_bullet.rota = kRota;
	m_bullet.hitPoint = kHitPoint;
	m_bullet.damage = kDamage;

	// ����p�T�C�Y
	m_collSize.left.x = kLeftXSize;
	m_collSize.left.y = kLeftYSize;
	m_collSize.right.x = kRightXSize;
	m_collSize.right.y = kRightYSize;
}

ShotRocket::~ShotRocket()
{
}

void ShotRocket::Update()
{
	// �ړ�����
	m_bullet.pos.y -= kSpeed + static_cast<float>(MTRandom::GetInstance()->GetMTRand(0, kSpeed / 2));

	// ����p���W�X�V
	CollRectUpdate();

	// ��ʊO����
	CheckEnablePos();

	// �ϋv�͂̊m�F
	CheckHitPoint();

	// �摜�A�j���[�V����
	AnimUpdate();

	// ���j�����ꍇ��HP��0�ɂ���
	if (m_isExplosion)
	{
		m_bullet.hitPoint = 0;
	}
	
	// �I�u�W�F�N�g�ɓ��������ꍇ
	if (m_bullet.hitPoint < kHitPoint - 1)
	{
		// ����p�T�C�Y
		m_collSize.left.x  = kExplosionLeftXSize;
		m_collSize.left.y  = kExplosionLeftYSize;
		m_collSize.right.x = kExplosionRightXSize;
		m_collSize.right.y = kExplosionRightYSize;

		m_isExplosion = true;
	}
}