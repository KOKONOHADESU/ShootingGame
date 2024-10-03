#include "ShotRocket.h"

#include "../../Util/MTRandom.h"

namespace
{
	// サイズ
	constexpr float kSize = 2.5f;

	// 角度
	constexpr float kRota = 0.0f;

	// 速度
	constexpr float kSpeed = 10.0f;

	// 体力
	constexpr int kHitPoint = 1000000;

	// ダメージ
	constexpr int kDamage = 10;

	// 判定の大きさ
	constexpr float kLeftXSize  = 20.0f;
	constexpr float kLeftYSize  = 20.0f;
	constexpr float kRightXSize = 20.0f;
	constexpr float kRightYSize = 20.0f;

	// ヒットした際の爆破判定の大きさ
	constexpr float kExplosionLeftXSize  = 100.0f;
	constexpr float kExplosionLeftYSize  = 100.0f;
	constexpr float kExplosionRightXSize = 100.0f;
	constexpr float kExplosionRightYSize = 100.0f;
}


ShotRocket::ShotRocket(Vec2 startPos, const std::vector<int>& handle) :
	ShotBase::ShotBase(startPos, handle),
	m_isExplosion(false)
{
	// 弾の初期化
	m_bullet.pos = startPos;
	m_bullet.size = kSize;
	m_bullet.rota = kRota;
	m_bullet.hitPoint = kHitPoint;
	m_bullet.damage = kDamage;

	// 判定用サイズ
	m_collSize.left.x = kLeftXSize;
	m_collSize.left.y = kLeftYSize;
	m_collSize.right.x = kRightXSize;
	m_collSize.right.y = kRightYSize;
}

ShotRocket::~ShotRocket()
{
}

void ShotRocket::Update()
{
	// 移動処理
	m_bullet.pos.y -= kSpeed + static_cast<float>(MTRandom::GetInstance()->GetMTRand(0, kSpeed / 2));

	// 判定用座標更新
	CollRectUpdate();

	// 画面外処理
	CheckEnablePos();

	// 耐久力の確認
	CheckHitPoint();

	// 画像アニメーション
	AnimUpdate();

	// 爆破した場合はHPを0にする
	if (m_isExplosion)
	{
		m_bullet.hitPoint = 0;
	}
	
	// オブジェクトに当たった場合
	if (m_bullet.hitPoint < kHitPoint - 1)
	{
		// 判定用サイズ
		m_collSize.left.x  = kExplosionLeftXSize;
		m_collSize.left.y  = kExplosionLeftYSize;
		m_collSize.right.x = kExplosionRightXSize;
		m_collSize.right.y = kExplosionRightYSize;

		m_isExplosion = true;
	}
}