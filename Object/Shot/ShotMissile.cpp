#include "ShotMissile.h"

#include "../../Util/MTRandom.h"

namespace
{
	// �T�C�Y
	constexpr float kSize = 2.5f;

	// �p�x
	constexpr float kRota = 0.0f;

	// ���x
	constexpr float kSpeed = 60.0f;

	// �̗�
	constexpr int kHitPoint = 1;

	// �_���[�W
	constexpr int kDamage = 1;

	// ����̑傫��
	constexpr float kLeftXSize = 5.0f;
	constexpr float kLeftYSize = 17.0f;
	constexpr float kRightXSize = 5.0f;
	constexpr float kRightYSize = 20.0f;
}


ShotMissile::ShotMissile(Vec2 startPos, const std::vector<int>& handle) :
	ShotBase::ShotBase(startPos, handle)
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

ShotMissile::~ShotMissile()
{
}

void ShotMissile::Update()
{
	// �ړ�����
	m_bullet.pos.y -= kSpeed + static_cast<float>(MTRandom::GetInstance()->GetMTRand(0, kSpeed / 2));

	// ����p���W�X�V
	CollRectUpdate();

	// ��ʊO����
	CheckEnablePos();

	// �ϋv�͂̊m�F
	CheckHitPoint();
}
