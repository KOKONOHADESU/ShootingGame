#include "EnemyNormal.h"

namespace
{
	// �t�@�C���p�X
	const char* const kPathName = "Data/Image/Enemy/enemy1.png";

	// �ړ����x
	constexpr float kSpeed = 5.0f;

	// �̗�
	constexpr int kHitPointMax = 1;

	// ����̑傫��
	constexpr float kLeftXSize  = 35;
	constexpr float kLeftYSize  = 35;
	constexpr float kRightXSize = 35;
	constexpr float kRightYSize = 35;
}

EnemyNormal::EnemyNormal(Airframe airframe):
	EnemyBase::EnemyBase(airframe)
{
	// �̗͂̏�����
	m_airframe.hitPoint = kHitPointMax;

	// ������
	EnemyBase::Init(kPathName);
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
