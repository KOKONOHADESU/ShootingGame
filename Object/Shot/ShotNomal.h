#pragma once

#include "ShotBase.h"

#include "../../Util/Vec2.h"
#include "../../Util/Rect.h"

class ShotNomal : public ShotBase
{
public:
	ShotNomal(Vec2 startPos);
	~ShotNomal();

	void Update()override;
};

