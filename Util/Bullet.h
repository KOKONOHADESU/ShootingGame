#pragma once

#include "Vec2.h"

struct Bullet
{
	// ���W
	Vec2 pos;

	// �T�C�Y
	float size;

	// �p�x
	float rota;

	// �̗�
	int hitPoint;

	// �U����
	int damage;
};