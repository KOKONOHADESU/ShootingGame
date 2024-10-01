#pragma once

#include "Vec2.h"

// 機体の基本データ
struct Airframe
{
	// 位置
	Vec2 pos;

	// サイズ
	float size;

	// 角度
	float rota;

	// 体力
	int hitPoint;
};