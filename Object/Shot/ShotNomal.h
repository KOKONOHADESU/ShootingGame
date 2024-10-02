#pragma once

#include "ShotBase.h"

class ShotNomal : public ShotBase
{
public:
	ShotNomal(Vec2 startPos, const std::vector<int>& handle);
	~ShotNomal();

	void Update()override;
};

