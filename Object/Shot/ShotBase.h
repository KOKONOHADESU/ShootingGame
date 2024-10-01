#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Rect.h"
#include "../../Util/Bullet.h"

class ShotBase
{
public:
	ShotBase(Vec2 startPos);
	virtual~ShotBase();

	virtual void Init(Vec2 pos, const char* pathName);
	virtual void End();
	virtual void Update() = 0;
	virtual void Draw();

public:
	// �ʒu��n��
	Vec2 GetPos()const;

	// ����p���W��n��
	Rect GetCollData()const;

	// ���݂��邩�ǂ���
	bool IsEnable()const;

	// �U����
	int GetDamage();

	// �������������m�F����
	void SetCheckHit();

	// ���݂�����
	void IsEnd();

protected:
	// �ϋv�͂̊m�F
	void CheckHitPoint();

	// ����p���W���X�V����
	void CollRectUpdate();

	// �ʒu���m�F����
	void CheckEnablePos();

protected:
	// �摜�n���h��
	int m_hGraph;

	// �e�f�[�^
	Bullet m_bullet;

	// �l�p�`����p
	Rect m_collRect;

	// �l�p�`����T�C�Y
	Rect m_collSize;

	// �I�u�W�F�N�g�����ł��邩�ǂ���
	bool m_isEnable;
};

