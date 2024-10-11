#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Airframe.h"
#include "../../Util/Rect.h"

class Player final
{
public:
	Player();
	~Player();

	void Update();
	void Draw();

public:
	// ���W��n��
	Vec2 GetPos()const;

	// �l�p�`�p����f�[�^
	Rect GetCollData()const;

	// ���˂��鐔
	int GetShootingNum()const;
private:
	// ����
	void Input();
	// ��ʔ͈͊O����
	void OutSide();
	// ����p���W���X�V����
	void CollRectUpdate();

private:
	// �摜�n���h��
	int m_hGraph;

	// �@�̃f�[�^
	Airframe m_airframe;

	// �l�p�`����p
	Rect m_collRect;

	// ���˂��鐔
	int m_shootingNum;
};

