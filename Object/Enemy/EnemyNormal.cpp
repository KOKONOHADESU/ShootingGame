#include "EnemyNormal.h"

namespace
{
	// �ړ����x
	constexpr float kSpeed = 5.0f;

	// �̗�
	constexpr int kHitPointMax = 1;

	// ����̑傫��
	constexpr float kLeftXSize  = 35.0f;
	constexpr float kLeftYSize  = 35.0f;
	constexpr float kRightXSize = 35.0f;
	constexpr float kRightYSize = 35.0f;
}

EnemyNormal::EnemyNormal(Airframe airframe, const std::vector<int>& handle, const std::vector<int>& hDead):
	EnemyBase::EnemyBase(airframe, handle, hDead)
{
	// �̗͂̏�����
	m_airframe.hitPoint = kHitPointMax;

	// ����p
	Rect collSize{ kLeftXSize ,kLeftYSize ,kRightXSize ,kRightYSize };
	CollRectUpdate(collSize);
}

EnemyNormal::~EnemyNormal()
{
}

void EnemyNormal::StartUpdate()
{
	// �֐��|�C���^�̕ύX
	m_pFunc = &EnemyBase::BattleUpdate;	
}

void EnemyNormal::BattleUpdate()
{
	// �ʒu�X�V
	m_airframe.pos.y += kSpeed;

	// ����p
	Rect collSize{ kLeftXSize ,kLeftYSize ,kRightXSize ,kRightYSize };
	CollRectUpdate(collSize);

	// �̗͂̊m�F
	EnemyBase::CheckHitPoint();

	// �ʒu�̊m�F
	CheckEnablePos();

	// ���񂾂��ǂ���
	if (m_isDead)
	{
		// �֐��|�C���^�̕ύX
		m_pFunc = &EnemyBase::DeadUpdate;
	}
}

void EnemyNormal::DeadUpdate()
{
	// ���S���o�̍X�V����
	ExplosionUpdate();
}
