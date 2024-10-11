#pragma once

#include "../../Util/Vec2.h"

#include <list>
#include <vector>

class ItemBase;

// �A�C�e���Ǘ��N���X
class ItemManager final
{
public:
	ItemManager();
	~ItemManager();

	void Update();
	void Draw();
public:
	// �V���b�g�f�[�^
	std::list<ItemBase*>& GetItemData();

	// ����̍��W���󂯎��
	void SetPos(const Vec2 pos);

	// �A�C�e���̐���
	void CreateItemCoin(Vec2 startPos);
	void CreateItemWeaponMissile(Vec2 startPos);

private:
	// ���݂��邩�ǂ���
	void CheckEnable();

private:
	// �摜�n���h��
	std::vector<std::vector<int>> m_handle;

	// �A�C�e��
	std::list<ItemBase*> m_pItem;
};

