#include "ItemBase.h"

#include <DxLib.h>

namespace
{
	// アニメーションフレーム
	constexpr int kAnimFrameMax = 1;
}

ItemBase::ItemBase(Vec2 startPos, const std::vector<int>& handle):
	m_animGraphChangeFrameCount(-1),
	m_animGraphChangeNum(0),
	m_collRect({0.0f,0.0f,0.0f,0.0f }),
	m_collSize({0.0f,0.0f,0.0f,0.0f }),
	m_isHit(false),
	m_isEnable(true)
{
	// メンバ関数の初期
	m_pFunc = &ItemBase::StartUpdate;

	// 初期位置座標
	m_item.pos = startPos;
	// ハンドルデータ
	m_handle = handle;

}

ItemBase::~ItemBase()
{
}

void ItemBase::Update()
{
	// メンバ関数ポインタ
	(this->*m_pFunc)();
}

void ItemBase::Draw()
{
	// 描画
	DrawRotaGraphF(m_item.pos.x, m_item.pos.y, m_item.size, m_item.rota, m_handle[m_animGraphChangeNum], true);

#if _DEBUG
	// 判定用デバッグ描画
	DrawBoxAA(m_collRect.left.x, m_collRect.left.y, m_collRect.right.x, m_collRect.right.y, 0xff0000, false);
#endif
}

Vec2 ItemBase::GetPos() const
{
	return m_item.pos;
}

Rect ItemBase::GetCollData() const
{
	return m_collRect;
}

void ItemBase::SetPos(const Vec2 pos)
{
	m_targetPos = pos;
}

void ItemBase::IsHitObject()
{
	m_isHit = true;
}

bool ItemBase::IsEnable() const
{
	return m_isEnable;
}

void ItemBase::CollRectUpdate()
{
	m_collRect.left.x = m_item.pos.x - m_collSize.left.x;
	m_collRect.left.y = m_item.pos.y - m_collSize.left.y;
	m_collRect.right.x = m_item.pos.x + m_collSize.right.x;
	m_collRect.right.y = m_item.pos.y + m_collSize.right.y;
}

void ItemBase::AnimUpdate(bool isAnim)
{
	if (isAnim)
	{
		// ショットアニメーション用画像を特定のフレームで切り替えアニメーションを行う
		m_animGraphChangeFrameCount++;
		if (m_animGraphChangeFrameCount > kAnimFrameMax)
		{
			m_animGraphChangeNum++;

			m_animGraphChangeFrameCount = 0;
		}

		// 演出が終わった場合アニメーションを位置から
		if (m_animGraphChangeNum == static_cast<int>(m_handle.size()))
		{
			m_animGraphChangeNum = 0;
		}
	}
	else
	{
		m_animGraphChangeNum = 0;
		m_animGraphChangeFrameCount = 0;
	}
}
