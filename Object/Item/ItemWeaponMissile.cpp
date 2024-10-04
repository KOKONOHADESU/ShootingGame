#include "ItemWeaponMissile.h"

#include "../../Util/DxLibSystem.h"

namespace
{
	// サイズ
	constexpr float kSize = 3.0f;

	// 角度
	constexpr float kRota = 0.0f;

	// 判定の大きさ
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

	// 判定用サイズ
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
	// 関数ポインタの変更
	m_pFunc = &ItemBase::BattleUpdate;
}

void ItemWeaponMissile::BattleUpdate()
{
	// 判定更新
	CollRectUpdate();

	// アニメーション
	AnimUpdate(false);

	// オブジェトに当たった場合
	if (m_isHit)
	{		
		// 関数ポインタの変更
		m_pFunc = &ItemBase::AfterHitUpdate;
	}
}

void ItemWeaponMissile::AfterHitUpdate()
{
	// アニメーション
	AnimUpdate(true);

	m_item.pos = m_targetPos;
}
