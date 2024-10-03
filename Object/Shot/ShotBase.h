#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Rect.h"
#include "../../Util/Bullet.h"

#include <vector>

class ShotBase
{
public:
	ShotBase(Vec2 startPos ,const std::vector<int>& handle);
	virtual~ShotBase();

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

	// �A�j���[�V�����p
	void AnimUpdate();
private:
	// �摜�A�j���[�V�����p
	int m_animGraphChangeFrameCount;
	int m_animGraphChangeNum;

protected:
	// �摜�n���h��
	std::vector<int> m_handle;

	// �e�f�[�^
	Bullet m_bullet;

	// �l�p�`����p
	Rect m_collRect;

	// �l�p�`����T�C�Y
	Rect m_collSize;

	// �I�u�W�F�N�g�����ł��邩�ǂ���
	bool m_isEnable;
};

