#include "ItemCoin.h"

#include "../../Util/DxLibSystem.h"

namespace
{
	// サイズ
	constexpr float kSize = 2.0f;

	// 角度
	constexpr float kRota = 0.0f;

	// 判定の大きさ
	constexpr float kLeftXSize  = 15.0f;
	constexpr float kLeftYSize  = 15.0f;
	constexpr float kRightXSize = 15.0f;
	constexpr float kRightYSize = 15.0f;
}

ItemCoin::ItemCoin(Vec2 startPos, const std::vector<int>& handle):
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

ItemCoin::~ItemCoin()
{

}

void ItemCoin::StartUpdate()
{
	// 関数ポインタの変更
	m_pFunc = &ItemBase::BattleUpdate;
}

void ItemCoin::BattleUpdate()
{
	// 判定更新
	CollRectUpdate();

	// アニメーション
	AnimUpdate();

	// オブジェトに当たった場合
	if (m_isHit)
	{		
		// 関数ポインタの変更
		m_pFunc = &ItemBase::DeadUpdate;
	}
}

void ItemCoin::DeadUpdate()
{
	Vec2 components{ 0.0f,0.0f };
	Vec2 direction{ 0.0f,0.0f };
	const Vec2 endPos{DxLibSystem::kScreenWidthF / 2.0f , DxLibSystem::kScreenHeightF };

	//成分計算
	components.x = endPos.x - m_item.pos.x;
	components.y = endPos.y - m_item.pos.y;

	//大きさ計算
	const float magnitude = sqrtf(components.x * components.x + components.y * components.y);

	//方向計算（正規化）
	direction.x = components.x / magnitude;
	direction.y = components.y / magnitude;

	//移動後の位置を計算
	m_item.pos.x += direction.x * 50.0f;
	m_item.pos.y += direction.y * 50.0f;

	// 特定の位置に近づくとオブジェクトを消す
	if (magnitude < 100.0f)
	{
		m_isEnable = false;
	}
}
