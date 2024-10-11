#pragma once

#include "../../Util/Vec2.h"

#include <list>
#include <vector>

class ItemBase;

// アイテム管理クラス
class ItemManager final
{
public:
	ItemManager();
	~ItemManager();

	void Update();
	void Draw();
public:
	// ショットデータ
	std::list<ItemBase*>& GetItemData();

	// 特定の座標を受け取る
	void SetPos(const Vec2 pos);

	// アイテムの生成
	void CreateItemCoin(Vec2 startPos);
	void CreateItemWeaponMissile(Vec2 startPos);

private:
	// 存在するかどうか
	void CheckEnable();

private:
	// 画像ハンドル
	std::vector<std::vector<int>> m_handle;

	// アイテム
	std::list<ItemBase*> m_pItem;
};

