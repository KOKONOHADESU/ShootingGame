#include "EnemyBase.h"

#include "../../Util/System.h"

#include <DxLib.h>

namespace
{
	// 死亡演出用画像
	const char* const kExplosionPath = "Data/Image/Destroy/explosion.png";

	// 死亡演出用画像の横の列の数
	constexpr int kExplosionGraphXNum = 7;
	// 死亡演出用画像の縦の列の数
	constexpr int kExplosionGraphYNum = 1;
	// 死亡演出用画像の横のサイズ
	constexpr int kExplosionGraphXSize = 128;
	// 死亡演出用画像の縦のサイズ
	constexpr int kExplosionGraphYSize = 128;

	// 死亡演出画像切り替えフレーム
	constexpr int kExplosionChangeFrameMax = 1;
}

EnemyBase::EnemyBase(Airframe airframe):
	m_hGraph(-1),
	m_explosionGraphChangeFrameCount(-1),
	m_explosionGraphChangeNum(-1),
	m_airframe(airframe),
	m_collRect({ 0.0f,0.0f ,0.0f,0.0f }),
	m_isDead(false),
	m_isEnable(true)
{
	// メンバ関数の初期
	m_pFunc = &EnemyBase::StartUpdate;

	for (int i = 0; i < kExplosionGraphXNum * kExplosionGraphYNum; i++)
	{
		m_hExplosion[i] = -1;
	}
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init(const char* graphPath)
{
	// 画像の読み込み
	m_hGraph = LoadGraph(graphPath);

	// 画像ファイルのメモリへの分割読みこみ
	LoadDivGraph(kExplosionPath, kExplosionGraphXNum * kExplosionGraphYNum,
		kExplosionGraphXNum, kExplosionGraphYNum,
		kExplosionGraphXSize, kExplosionGraphYSize, m_hExplosion);
}

void EnemyBase::End()
{
	// メモリ解放
	DeleteGraph(m_hGraph);

	for (int i = 0; i < kExplosionGraphXNum * kExplosionGraphYNum; i++)
	{
		DeleteGraph(m_hExplosion[i]);
	}
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
			m_hGraph, true);
	}
	else	
	{
		// 死亡演出画像描画
		DrawRotaGraphF(
			m_airframe.pos.x,
			m_airframe.pos.y,
			m_airframe.size,
			m_airframe.rota,
			m_hExplosion[m_explosionGraphChangeNum], true);
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
	if (m_airframe.pos.y > System::ScreenSizeYF)
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
	if (m_explosionGraphChangeNum == kExplosionGraphXNum * kExplosionGraphYNum)
	{
		m_isEnable = false;
	}
}
