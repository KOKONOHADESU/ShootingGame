#pragma once

#include "ShotBase.h"

class ShotRocket : public ShotBase
{
public:
	ShotRocket(Vec2 startPos, const std::vector<int>& handle);
	virtual ~ShotRocket();

	void Update()override;
private:
	bool m_isExplosion;
};

