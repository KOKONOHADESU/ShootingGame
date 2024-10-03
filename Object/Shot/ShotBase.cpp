#include "ShotBase.h"

#include <DxLib.h>

namespace
{
	// ���g�̑ϋv�͂ւ̃_���[�W
	constexpr int kMyHitDamage = 1;

	// �A�j���[�V�����t���[��
	constexpr int kAnimFrameMax = 1;
}

ShotBase::ShotBase(Vec2 startPos, const std::vector<int>& handle) :
	m_animGraphChangeFrameCount(-1),
	m_animGraphChangeNum(0),
	m_collRect({ 0.0f,0.0f ,0.0f,0.0f }),
	m_collSize({ 0.0f,0.0f ,0.0f,0.0f }),
	m_isEnable(true)
{
	// �X�^�[�g�ʒu�̃Z�b�g
	m_bullet.pos = startPos;

	// �n���h���̃R�s�[
	m_handle = handle;
}

ShotBase::~ShotBase()
{
}

void ShotBase::End()
{
	
}

void ShotBase::Draw()
{
	// �`�揈��
	DrawRotaGraphF(m_bullet.pos.x, m_bullet.pos.y, m_bullet.size, m_bullet.rota, m_handle[m_animGraphChangeNum], true);

#if _DEBUG
	// ����p�f�o�b�O�`��
	DrawBoxAA(m_collRect.left.x, m_collRect.left.y, m_collRect.right.x, m_collRect.right.y, 0xff0000, false);
#endif
}

Vec2 ShotBase::GetPos()const
{
	return m_bullet.pos;
}

Rect ShotBase::GetCollData() const
{
	return m_collRect;
}

bool ShotBase::IsEnable() const
{
	return m_isEnable;
}

int ShotBase::GetDamage()
{
	return m_bullet.damage;
}

void ShotBase::SetCheckHit()
{
	m_bullet.hitPoint -= kMyHitDamage;
}

void ShotBase::IsEnd()
{
	m_isEnable = false;
}

void ShotBase::CheckHitPoint()
{
	// �ϋv�͂��Ȃ��Ȃ����ꍇ�͑��݂�����
	if (m_bullet.hitPoint < 0)
	{
		IsEnd();
	}
}

void ShotBase::CollRectUpdate()
{
	m_collRect.left.x  = m_bullet.pos.x  - m_collSize.left.x;
	m_collRect.left.y  = m_bullet.pos.y  - m_collSize.left.y;
	m_collRect.right.x = m_bullet.pos.x  + m_collSize.right.x;
	m_collRect.right.y = m_bullet.pos.y  + m_collSize.right.y;
}

void ShotBase::CheckEnablePos()
{
	// ��ʏ�ɂł�Ƒ��݂�����
	if (m_bullet.pos.y < 0.0f)
	{
		m_isEnable = false;
	}
}

void ShotBase::AnimUpdate()
{
	// �V���b�g�A�j���[�V�����p�摜�����̃t���[���Ő؂�ւ��A�j���[�V�������s��
	m_animGraphChangeFrameCount++;
	if (m_animGraphChangeFrameCount > kAnimFrameMax)
	{
		m_animGraphChangeNum++;

		m_animGraphChangeFrameCount = 0;
	}

	// ���o���I������ꍇ�A�j���[�V�������ʒu����
	if (m_animGraphChangeNum == static_cast<int>(m_handle.size()))
	{
		m_animGraphChangeNum = 0;
	}
}
