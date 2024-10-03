#include "EnemyBase.h"

#include "../../Util/DxLibSystem.h"

#include <DxLib.h>

namespace
{
	// ���S���o�摜�؂�ւ��t���[��
	constexpr int kExplosionChangeFrameMax = 1;
}

EnemyBase::EnemyBase(Airframe airframe, const std::vector<int>& handle, const std::vector<int>& hDead):
	m_explosionGraphChangeFrameCount(-1),
	m_explosionGraphChangeNum(0),
	m_airframe(airframe),
	m_collRect({ 0.0f,0.0f ,0.0f,0.0f }),
	m_isDead(false),
	m_isEnable(true)
{
	// �����o�֐��̏���
	m_pFunc = &EnemyBase::StartUpdate;

	// �n���h���̓ǂݍ���
	m_handle = handle;
	m_hDead = hDead;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::End()
{
}

void EnemyBase::Update()
{
	// �����o�֐��|�C���^
	(this->*m_pFunc)();
}

void EnemyBase::Draw()
{
	if (!m_isDead)
	{
		// �摜�`��
		DrawRotaGraphF(
			m_airframe.pos.x,
			m_airframe.pos.y,
			m_airframe.size,
			m_airframe.rota,
			m_handle[0], true);
	}
	else	
	{
		// ���S���o�摜�`��
		DrawRotaGraphF(
			m_airframe.pos.x,
			m_airframe.pos.y,
			m_airframe.size,
			m_airframe.rota,
			m_hDead[m_explosionGraphChangeNum], true);
	}

#if _DEBUG
	// ����p�f�o�b�O�`��
	DrawBox(m_collRect.left.x, m_collRect.left.y, m_collRect.right.x, m_collRect.right.y, 0xff0000, false);
#endif
}

Rect EnemyBase::GetCollData() const
{
	return m_collRect;
}

void EnemyBase::SetDamage(int damage)
{
	// �_���[�W���󂯎��
	m_airframe.hitPoint -= damage;
}

bool EnemyBase::IsEnable() const
{
	return m_isEnable;
}

void EnemyBase::CollRectUpdate(Rect size)
{
	m_collRect.left.x  = m_airframe.pos.x - size.left.x;
	m_collRect.left.y  = m_airframe.pos.y - size.left.y;
	m_collRect.right.x = m_airframe.pos.x + size.right.x;
	m_collRect.right.y = m_airframe.pos.y + size.right.y;
}

void EnemyBase::CheckHitPoint()
{
	// �̗͂̊m�F
	if (m_airframe.hitPoint < 0)
	{
		m_isDead = true;
	}
}

void EnemyBase::CheckEnablePos()
{
	// ��ʏ�ɂł�Ƒ��݂�����
	if (m_airframe.pos.y > DxLibSystem::kScreenHeightF)
	{
		m_isEnable = false;
	}
}

void EnemyBase::ExplosionUpdate()
{
	// ���j���o�p�摜�����̃t���[���Ő؂�ւ��A�j���[�V�������s��
	m_explosionGraphChangeFrameCount++;
	if (m_explosionGraphChangeFrameCount > kExplosionChangeFrameMax)
	{
		m_explosionGraphChangeNum++;

		m_explosionGraphChangeFrameCount = 0;
	}

	// ���o���I������ꍇ���݂�����
	if (m_explosionGraphChangeNum == static_cast<int>(m_hDead.size()) - 1)
	{
		m_isEnable = false;
	}
}
