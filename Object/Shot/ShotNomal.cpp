#include "ShotNomal.h"

#include "../../Util/MTRandom.h"

#include <DxLib.h>

namespace
{
	// サイズ
	constexpr float kSize = 1.0f;

	// 角度
	constexpr float kRota = 0.0f;

	// 速度
	constexpr float kSpeed = 60.0f;

	// 体力
	constexpr int kHitPoint = 1;

	// ダメージ
	constexpr int kDamage = 1;

	// 判定の大きさ
	constexpr float kLeftXSize  = 5.0f;
	constexpr float kLeftYSize  = 20.0f;
	constexpr float kRightXSize = 5.0f;
	constexpr float kRightYSize = 20.0f;

	// 画像パス
	const char* const kPathName = "Data/Image/Shot/shot.png";
}

ShotNomal::ShotNomal(Vec2 startPos):
	ShotBase::ShotBase(startPos)
{
	// 弾の初期化
	m_bullet.pos      = startPos;
	m_bullet.size     = kSize;
	m_bullet.rota     = kRota;
	m_bullet.hitPoint = kHitPoint;
	m_bullet.damage   = kDamage;

	// 判定用サイズ
	m_collSize.left.x  = kLeftXSize;
	m_collSize.left.y  = kLeftYSize;
	m_collSize.right.x = kRightXSize;
	m_collSize.right.y = kRightYSize;

	// 初期化
	ShotBase::Init(m_bullet.pos, kPathName);
}

ShotNomal::~ShotNomal()
{
}

void ShotNomal::Update()
{
	// 移動処理
	m_bullet.pos.y -= kSpeed + static_cast<float>(MTRandom::GetInstance()->GetMTRand(0, kSpeed / 2));

	// 判定用座標更新
	CollRectUpdate();

	// 画面外処理
	CheckEnablePos();

	// 耐久力の確認
	CheckHitPoint();
}