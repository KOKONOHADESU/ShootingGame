#pragma once
#include "ItemBase.h"

// ÉRÉCÉì
class ItemWeaponMissile : public ItemBase
{
public:
	ItemWeaponMissile(Vec2 startPos, const std::vector<int>& handle);
	~ItemWeaponMissile();

	void StartUpdate()override;
	void BattleUpdate()override;
	void AfterHitUpdate()override;
};

