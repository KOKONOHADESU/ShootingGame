#pragma once

#include "ShotBase.h"

class ShotMissile : public ShotBase
{
public:
	ShotMissile(Vec2 startPos, std::vector<int> handle);
	virtual ~ShotMissile();

	void Update()override;
};

