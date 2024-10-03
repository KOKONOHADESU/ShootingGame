#pragma once
#include "ItemBase.h"

// ÉRÉCÉì
class ItemCoin : public ItemBase
{
public:
	ItemCoin(Vec2 startPos, const std::vector<int>& handle);
	~ItemCoin();

	void StartUpdate()override;
	void BattleUpdate()override;
	void DeadUpdate()override;
};

