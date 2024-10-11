#include "ItemManager.h"

#include "ItemCoin.h"
#include "ItemWeaponMissile.h"

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

	// ����A�C�e��
	const char* const kItemWeapon1Path = "Data/Image/Player/Weapon/Weapon1.png";

	// �m�[�}���V���b�g
	constexpr int kItemWeapon1GrapicNumX = 17;
	constexpr int kItemWeapon1GrapicNumY = 1;
}

ItemManager::ItemManager()
{
	// �摜�n���h���̏�����
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

	// �I�u�W�F�N�g�̑��݂��m�F
	CheckEnable();
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

void ItemManager::SetPos(const Vec2 pos)
{
	for (auto& item : m_pItem)
	{
		item->SetPos(pos);
	}
}

void ItemManager::CreateItemCoin(Vec2 startPos)
{
	// �R�C������
	m_pItem.push_back(new ItemCoin(startPos, m_handle[ItemType::COIN]));
}

void ItemManager::CreateItemWeaponMissile(Vec2 startPos)
{
	// �~�T�C�����퐶��
	m_pItem.push_back(new ItemWeaponMissile(startPos, m_handle[ItemType::WEAPONMISSILE]));
}

void ItemManager::CheckEnable()
{
	// �I�u�W�F�N�g�̑��݂��m�F
	for (auto it = m_pItem.begin(); it != m_pItem.end();)
	{
		// �G�l�~�[�̑��݂�������ꍇ
		if (!(*it)->IsEnable())
		{
			// ���������
			delete* it;

			// ���X�g����v�f���폜
			it = m_pItem.erase(it);
		}
		else
		{
			// �폜���Ȃ��ꍇ�͎��̗v�f�֐i��
			++it;
		}
	}
}
