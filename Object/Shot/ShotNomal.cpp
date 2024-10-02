#include "ShotNomal.h"

#include "../../Util/MTRandom.h"

#include <DxLib.h>

namespace
{
	// �T�C�Y
	constexpr float kSize = 1.0f;

	// �p�x
	constexpr float kRota = 0.0f;

	// ���x
	constexpr float kSpeed = 60.0f;

	// �̗�
	constexpr int kHitPoint = 1;

	// �_���[�W
	constexpr int kDamage = 1;

	// ����̑傫��
	constexpr float kLeftXSize  = 5.0f;
	constexpr float kLeftYSize  = 20.0f;
	constexpr float kRightXSize = 5.0f;
	constexpr float kRightYSize = 20.0f;

	// �摜�p�X
	const char* const kPathName = "Data/Image/Shot/shot.png";
}

ShotNomal::ShotNomal(Vec2 startPos):
	ShotBase::ShotBase(startPos)
{
	// �e�̏�����
	m_bullet.pos      = startPos;
	m_bullet.size     = kSize;
	m_bullet.rota     = kRota;
	m_bullet.hitPoint = kHitPoint;
	m_bullet.damage   = kDamage;

	// ����p�T�C�Y
	m_collSize.left.x  = kLeftXSize;
	m_collSize.left.y  = kLeftYSize;
	m_collSize.right.x = kRightXSize;
	m_collSize.right.y = kRightYSize;

	// ������
	ShotBase::Init(m_bullet.pos, kPathName);
}

ShotNomal::~ShotNomal()
{
}

void ShotNomal::Update()
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