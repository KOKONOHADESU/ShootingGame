#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Item.h"
#include "../../Util/Rect.h"

#include<vector>

// �A�C�e���̋K��N���X
class ItemBase
{
public:
	ItemBase(Vec2 startPos, const std::vector<int>& handle);
	virtual ~ItemBase();

	virtual void Update() = 0;
	virtual void Draw();
public:
	// �ʒu��n��
	Vec2 GetPos()const;

	// ����p���W��n��
	Rect GetCollData()const;

protected:
	// ����X�V����
	void CollRectUpdate();

	// �A�j���[�V�����p
	virtual void AnimUpdate();

private:
	// �摜�A�j���[�V�����p
	int m_animGraphChangeFrameCount;
	int m_animGraphChangeNum;

protected:
	// �摜�n���h��
	std::vector<int> m_handle;

	// �A�C�e���ɐ����ɕK�v�ȃf�[�^
	Item m_item;

	// �l�p�`����p
	Rect m_collRect;

	// �l�p�`����T�C�Y
	Rect m_collSize;
};

