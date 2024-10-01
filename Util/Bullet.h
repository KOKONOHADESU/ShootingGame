#pragma once

#include "Vec2.h"

struct Bullet
{
	// 座標
	Vec2 pos;

	// サイズ
	float size;

	// 角度
	float rota;

	// 体力
	int hitPoint;

	// 攻撃力
	int damage;
};