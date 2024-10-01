#pragma once
#include "EnemyBase.h"

class EnemyNormal : public EnemyBase
{
public:
	EnemyNormal(Airframe airframe);
	virtual ~EnemyNormal();

	void StartUpdate()override;
	void BattleUpdate()override;
	void DeadUpdate()override;
};

