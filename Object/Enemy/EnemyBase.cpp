#include "EnemyBase.h"

#include "../../Util/System.h"

#include <DxLib.h>

namespace
{
	// ���S���o�p�摜
	const char* const kExplosionPath = "Data/Image/Destroy/explosion.png";

	// ���S���o�p�摜�̉��̗�̐�
	constexpr int kExplosionGraphXNum = 7;
	// ���S���o�p�摜�̏c�̗�̐�
	constexpr int kExplosionGraphYNum = 1;
	// ���S���o�p�摜�̉��̃T�C�Y
	constexpr int kExplosionGraphXSize = 128;
	// ���S���o�p�摜�̏c�̃T�C�Y
	constexpr int kExplosionGraphYSize = 128;

	// ���S���o�摜�؂�ւ��t���[��
	constexpr int kExplosionChangeFrameMax = 1;
}

EnemyBase::EnemyBase(Airframe airframe):
	m_hGraph(-1),
	m_explosionGraphChangeFrameCount(-1),
	m_explosionGraphChangeNum(-1),
	m_airframe(airframe),
	m_collRect({ 0.0f,0.0f ,0.0f,0.0f }),
	m_isDead(false),
	m_isEnable(true)
{
	// �����o�֐��̏���
	m_pFunc = &EnemyBase::StartUpdate;

	for (int i = 0; i < kExplosionGraphXNum * kExplosionGraphYNum; i++)
	{
		m_hExplosion[i] = -1;
	}
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init(const char* graphPath)
{
	// �摜�̓ǂݍ���
	m_hGraph = LoadGraph(graphPath);

	// �摜�t�@�C���̃������ւ̕����ǂ݂���
	LoadDivGraph(kExplosionPath, kExplosionGraphXNum * kExplosionGraphYNum,
		kExplosionGraphXNum, kExplosionGraphYNum,
		kExplosionGraphXSize, kExplosionGraphYSize, m_hExplosion);
}

void EnemyBase::End()
{
	// ���������
	DeleteGraph(m_hGraph);

	for (int i = 0; i < kExplosionGraphXNum * kExplosionGraphYNum; i++)
	{
		DeleteGraph(m_hExplosion[i]);
	}
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
			m_hGraph, true);
	}
	else	
	{
		// ���S���o�摜�`��
		DrawRotaGraphF(
			m_airframe.pos.x,
			m_airframe.pos.y,
			m_airframe.size,
			m_airframe.rota,
			m_hExplosion[m_explosionGraphChangeNum], true);
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
	if (m_airframe.pos.y > System::ScreenSizeYF)
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
	if (m_explosionGraphChangeNum == kExplosionGraphXNum * kExplosionGraphYNum)
	{
		m_isEnable = false;
	}
}
