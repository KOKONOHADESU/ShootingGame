#pragma once

#include "ShotBase.h"

class ShotMissile : public ShotBase
{
public:
	ShotMissile(Vec2 startPos, const std::vector<int>& handle);
	virtual ~ShotMissile();

	void Update()override;
};

