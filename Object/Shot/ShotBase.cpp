#include "ShotBase.h"

#include <DxLib.h>

namespace
{
	// ���g�̑ϋv�͂ւ̃_���[�W
	constexpr int kMyHitDamage = 1;
}

ShotBase::ShotBase(Vec2 startPos) :
	m_hGraph(-1),
	m_collRect({ 0.0f,0.0f ,0.0f,0.0f }),
	m_collSize({ 0.0f,0.0f ,0.0f,0.0f }),
	m_isEnable(true)
{
	// �����ʒu
	m_bullet.pos = startPos;
}

ShotBase::~ShotBase()
{
}

void ShotBase::Init(Vec2 pos, const char* pathName)
{
	// �X�^�[�g�ʒu�̃Z�b�g
	m_bullet.pos = pos;

	// �摜�̓ǂݍ���
	m_hGraph = LoadGraph(pathName);
}

void ShotBase::End()
{
	// �������
	DeleteGraph(m_hGraph);
}

void ShotBase::Draw()
{
	// �`�揈��
	DrawRotaGraphF(m_bullet.pos.x, m_bullet.pos.y, m_bullet.size, m_bullet.rota, m_hGraph, true);

#if _DEBUG
	// ����p�f�o�b�O�`��
	DrawBox(m_collRect.left.x, m_collRect.left.y, m_collRect.right.x, m_collRect.right.y, 0xff0000, false);
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

