#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Airframe.h"
#include "../../Util/Rect.h"

namespace
{
	// ���S���o�p�摜�̐�
	constexpr int kExplosionGraphAllNum = 7;
}

class EnemyBase
{
public:
	EnemyBase(Airframe airframe);
	virtual ~EnemyBase();
protected:
	virtual void Init(const char* graphPath);
public:
	virtual void End();
	virtual void Update();
	virtual void Draw();

public:
	// ������
	virtual void StartUpdate() = 0;
	// �o�g�����
	virtual void BattleUpdate() = 0;
	// ���ŏ��
	virtual void DeadUpdate() = 0;

public:
	// ����p���W��n��
	Rect GetCollData()const;

	// �_���[�W���󂯎��
	void SetDamage(int damage);

	// ���݂��邩�ǂ������m�F����
	bool IsEnable()const;

protected:
	// ����p���W���X�V����
	void CollRectUpdate(Rect size);
	// �̗͂��m�F
	void CheckHitPoint();
	// �ʒu���m�F����
	void CheckEnablePos();
	// ���S���o�p�X�V����
	void ExplosionUpdate();
protected:
	// �摜�n���h��
	int m_hGraph;

	// ���S���o�p�n���h��
	int m_hExplosion[kExplosionGraphAllNum];

	// ���S���o�摜�̐؂�ւ��t���[���J�E���g
	int m_explosionGraphChangeFrameCount;

	// ���S���o�摜�̐؂�ւ���
	int m_explosionGraphChangeNum;

	// �@�̃f�[�^
	Airframe m_airframe;

	// �l�p�`����p
	Rect m_collRect;

	// ���񂾂��ǂ���
	bool m_isDead;

	// �I�u�W�F�N�g�����ł��邩�ǂ���
	bool m_isEnable;

	// �����o�֐��|�C���^
	void(EnemyBase::* m_pFunc)();
};

