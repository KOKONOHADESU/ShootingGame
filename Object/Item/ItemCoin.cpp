#include "ItemCoin.h"

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

void ItemCoin::Update()
{
	// 判定サイズ用更新処理
	CollRectUpdate();
	// アニメーションの再生
	AnimUpdate();
}
