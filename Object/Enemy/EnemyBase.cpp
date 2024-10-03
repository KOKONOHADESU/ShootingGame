#include "EnemyBase.h"

#include "../../Util/DxLibSystem.h"

#include <DxLib.h>

namespace
{
	// 死亡演出画像切り替えフレーム
	constexpr int kExplosionChangeFrameMax = 1;
}

EnemyBase::EnemyBase(Airframe airframe, const std::vector<int>& handle, const std::vector<int>& hDead):
	m_explosionGraphChangeFrameCount(-1),
	m_explosionGraphChangeNum(0),
	m_airframe(airframe),
	m_collRect({ 0.0f,0.0f ,0.0f,0.0f }),
	m_isDead(false),
	m_isEnable(true)
{
	// メンバ関数の初期
	m_pFunc = &EnemyBase::StartUpdate;

	// ハンドルの読み込み
	m_handle = handle;
	m_hDead = hDead;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::End()
{
}

void EnemyBase::Update()
{
	// メンバ関数ポインタ
	(this->*m_pFunc)();
}

void EnemyBase::Draw()
{
	if (!m_isDead)
	{
		// 画像描画
		DrawRotaGraphF(
			m_airframe.pos.x,
			m_airframe.pos.y,
			m_airframe.size,
			m_airframe.rota,
			m_handle[0], true);
	}
	else	
	{
		// 死亡演出画像描画
		DrawRotaGraphF(
			m_airframe.pos.x,
			m_airframe.pos.y,
			m_airframe.size,
			m_airframe.rota,
			m_hDead[m_explosionGraphChangeNum], true);
	}

#if _DEBUG
	// 判定用デバッグ描画
	DrawBox(m_collRect.left.x, m_collRect.left.y, m_collRect.right.x, m_collRect.right.y, 0xff0000, false);
#endif
}

Rect EnemyBase::GetCollData() const
{
	return m_collRect;
}

void EnemyBase::SetDamage(int damage)
{
	// ダメージを受け取る
	m_airframe.hitPoint -= damage;
}

bool EnemyBase::IsEnable() const
{
	return m_isEnable;
}

void EnemyBase::CollRectUpdate(Rect size)
{
	m_collRect.left.x  = m_airframe.pos.x - size.left.x;
	m_collRect.left.y  = m_airframe.pos.y - size.left.y;
	m_collRect.right.x = m_airframe.pos.x + size.right.x;
	m_collRect.right.y = m_airframe.pos.y + size.right.y;
}

void EnemyBase::CheckHitPoint()
{
	// 体力の確認
	if (m_airframe.hitPoint < 0)
	{
		m_isDead = true;
	}
}

void EnemyBase::CheckEnablePos()
{
	// 画面上にでると存在を消す
	if (m_airframe.pos.y > DxLibSystem::kScreenHeightF)
	{
		m_isEnable = false;
	}
}

void EnemyBase::ExplosionUpdate()
{
	// 爆破演出用画像を特定のフレームで切り替えアニメーションを行う
	m_explosionGraphChangeFrameCount++;
	if (m_explosionGraphChangeFrameCount > kExplosionChangeFrameMax)
	{
		m_explosionGraphChangeNum++;

		m_explosionGraphChangeFrameCount = 0;
	}

	// 演出が終わった場合存在を消す
	if (m_explosionGraphChangeNum == static_cast<int>(m_hDead.size()) - 1)
	{
		m_isEnable = false;
	}
}
