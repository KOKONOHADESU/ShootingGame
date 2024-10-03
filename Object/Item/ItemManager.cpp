#include "ItemManager.h"

#include "ItemCoin.h"

#include "../../Util/GraphicSprite.h"
#include "../../Util/ItemType.h"

#include <DxLib.h>

namespace
{
	// �R�C���A�C�e��
	const char* const kItemCoinPath = "Data/Image/Item/Coin.png";

	// �m�[�}���V���b�g
	constexpr int kItemCoinGrapicNumX = 5;
	constexpr int kItemCoinGrapicNumY = 1;
}

ItemManager::ItemManager()
{
	// �摜�n���h���̏�����
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
	// �������
	for (auto it = m_pItem.begin(); it != m_pItem.end(); ++it)
	{
		// ���������
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
	// �X�V����
	for (auto& item : m_pItem)
	{
		item->Update();
	}	
}

void ItemManager::Draw()
{
	// �`�揈��
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
	// �R�C������
	m_pItem.push_back(new ItemCoin(startPos, m_handle[ItemType::COIN]));
}
