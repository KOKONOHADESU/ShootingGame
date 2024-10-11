#include "ItemManager.h"

#include "ItemCoin.h"
#include "ItemWeaponMissile.h"

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

	// 武器アイテム
	const char* const kItemWeapon1Path = "Data/Image/Player/Weapon/Weapon1.png";

	// ノーマルショット
	constexpr int kItemWeapon1GrapicNumX = 17;
	constexpr int kItemWeapon1GrapicNumY = 1;
}

ItemManager::ItemManager()
{
	// 画像ハンドルの初期化
	GraphicSprite::InitType(m_handle, ItemType::MAX);
	GraphicSprite::InitGraphic(m_handle, ItemType::COIN, kItemCoinPath, kItemCoinGrapicNumX, kItemCoinGrapicNumY);
	GraphicSprite::InitGraphic(m_handle, ItemType::WEAPONMISSILE, kItemWeapon1Path, kItemWeapon1GrapicNumX, kItemWeapon1GrapicNumY);

	CreateItemCoin(Vec2(GetRand(1920), GetRand(1080)));
	CreateItemCoin(Vec2(GetRand(1920), GetRand(1080)));
	CreateItemCoin(Vec2(GetRand(1920), GetRand(1080)));

	CreateItemWeaponMissile(Vec2(GetRand(1920), GetRand(1080)));
	CreateItemWeaponMissile(Vec2(GetRand(1920), GetRand(1080)));
	CreateItemWeaponMissile(Vec2(GetRand(1920), GetRand(1080)));
}

ItemManager::~ItemManager()
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

	// オブジェクトの存在を確認
	CheckEnable();
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

void ItemManager::SetPos(const Vec2 pos)
{
	for (auto& item : m_pItem)
	{
		item->SetPos(pos);
	}
}

void ItemManager::CreateItemCoin(Vec2 startPos)
{
	// コイン生成
	m_pItem.push_back(new ItemCoin(startPos, m_handle[ItemType::COIN]));
}

void ItemManager::CreateItemWeaponMissile(Vec2 startPos)
{
	// ミサイル武器生成
	m_pItem.push_back(new ItemWeaponMissile(startPos, m_handle[ItemType::WEAPONMISSILE]));
}

void ItemManager::CheckEnable()
{
	// オブジェクトの存在を確認
	for (auto it = m_pItem.begin(); it != m_pItem.end();)
	{
		// エネミーの存在が消える場合
		if (!(*it)->IsEnable())
		{
			// メモリ解放
			delete* it;

			// リストから要素を削除
			it = m_pItem.erase(it);
		}
		else
		{
			// 削除しない場合は次の要素へ進む
			++it;
		}
	}
}
