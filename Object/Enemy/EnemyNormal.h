#pragma once
#include "EnemyBase.h"

class EnemyNormal : public EnemyBase
{
public:
	EnemyNormal(Airframe airframe, const std::vector<int>& handle, const std::vector<int>& hDead);
	virtual ~EnemyNormal();

	void StartUpdate()override;
	void BattleUpdate()override;
	void DeadUpdate()override;
};

