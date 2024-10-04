#include "ItemWeaponMissile.h"

#include "../../Util/DxLibSystem.h"

namespace
{
	// �T�C�Y
	constexpr float kSize = 3.0f;

	// �p�x
	constexpr float kRota = 0.0f;

	// ����̑傫��
	constexpr float kLeftXSize  = 15.0f;
	constexpr float kLeftYSize  = 15.0f;
	constexpr float kRightXSize = 15.0f;
	constexpr float kRightYSize = 15.0f;
}

ItemWeaponMissile::ItemWeaponMissile(Vec2 startPos, const std::vector<int>& handle):
	ItemBase::ItemBase(startPos,handle)
{
	m_item.size = kSize;
	m_item.rota = kRota;

	// ����p�T�C�Y
	m_collSize.left.x  = kLeftXSize;
	m_collSize.left.y  = kLeftYSize;
	m_collSize.right.x = kRightXSize;
	m_collSize.right.y = kRightYSize;
}

ItemWeaponMissile::~ItemWeaponMissile()
{

}

void ItemWeaponMissile::StartUpdate()
{
	// �֐��|�C���^�̕ύX
	m_pFunc = &ItemBase::BattleUpdate;
}

void ItemWeaponMissile::BattleUpdate()
{
	// ����X�V
	CollRectUpdate();

	// �A�j���[�V����
	AnimUpdate(false);

	// �I�u�W�F�g�ɓ��������ꍇ
	if (m_isHit)
	{		
		// �֐��|�C���^�̕ύX
		m_pFunc = &ItemBase::AfterHitUpdate;
	}
}

void ItemWeaponMissile::AfterHitUpdate()
{
	// �A�j���[�V����
	AnimUpdate(true);

	m_item.pos = m_targetPos;
}
