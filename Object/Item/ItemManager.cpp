#include "ItemManager.h"

#include "ItemCoin.h"

#include "../../Util/GraphicSprite.h"
#include "../../Util/ItemType.h"

#include <DxLib.h>

namespace
{
	// コインアイテム
	const char* const kItemCoinPath = "Data/Image/Item/Coin.png";

	// ノーマルショット
	constexpr int kItemCoinGrapicNumX = 5;
	constexpr int kItemCoinGrapicNumY = 1;
}

ItemManager::ItemManager()
{
	// 画像ハンドルの初期化
	GraphicSprite::InitType(m_handle, ItemType::MAX);
	GraphicSprite::InitGraphic(m_handle, ItemType::COIN, kItemCoinPath, kItemCoinGrapicNumX, kItemCoinGrapicNumY);

	CreateItemCoin(Vec2(GetRand(1920), GetRand(1080)));
	CreateItemCoin(Vec2(GetRand(1920), GetRand(1080)));
	CreateItemCoin(Vec2(GetRand(1920), GetRand(1080)));
}

ItemManager::~ItemManager()
{
}

void ItemManager::End()
{
	// 解放処理
	for (auto it = m_pItem.begin(); it != m_pItem.end(); ++it)
	{
		// メモリ解放
		delete* it;
		(*it) = nullptr;
	}

	for (int i = 0; i < static_cast<int>(ItemType::MAX); i++)
	{
		for (int j = 0; j < m_handle[i].size(); j++)
		{
			DeleteGraph(m_handle[i][j]);
		}
	}
}

void ItemManager::Update()
{
	// 更新処理
	for (auto& item : m_pItem)
	{
		item->Update();
	}	
}

void ItemManager::Draw()
{
	// 描画処理
	for (auto& item : m_pItem)
	{
		item->Draw();
	}
}

std::list<ItemBase*>& ItemManager::GetItemData()
{
	return m_pItem;
}

void ItemManager::CreateItemCoin(Vec2 startPos)
{
	// コイン生成
	m_pItem.push_back(new ItemCoin(startPos, m_handle[ItemType::COIN]));
}
