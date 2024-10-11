#include "Player.h"

#include "../../Util/DxLibSystem.h"

#include <DxLib.h>
#include <math.h>
#include <algorithm>

namespace
{
	// サイズ
	constexpr float kSize = 3.0f;

	// 角度
	constexpr float kRota = 0.0f;

	// 速度
	constexpr float kSpeed = 15.0f;

	// 体力
	constexpr int kHitPoint = 30;

	// 初期位置
	constexpr Vec2 kStartPos = { DxLibSystem::kScreenWidthF / 2.0f , DxLibSystem::kScreenHeightF - 300.0f };

	// 初期機体用
	Airframe kAirframe{ kStartPos , kSize , kRota ,kHitPoint };

	// 判定の大きさ
	constexpr float kLeftXSize  = 35.0f;
	constexpr float kLeftYSize  = 35.0f;
	constexpr float kRightXSize = 35.0f;
	constexpr float kRightYSize = 50.0f;

	// プレイヤー画像パス
	const char* const kPlayerPath = "Data/Image/Player/Player1.png";
}

Player::Player():
	m_hGraph(-1),
	m_airframe(kAirframe),
	m_collRect({ 0.0f,0.0f ,0.0f,0.0f }),
	m_shootingNum(0)
{
	// メモリ確保
	m_hGraph = LoadGraph(kPlayerPath);

	// 判定用位置座標更新
	CollRectUpdate();
}

Player::~Player()
{
	// メモリ解放
	DeleteGraph(m_hGraph);
}

void Player::Update()
{
	// 入力
	Input();

	// 画面外処理
	OutSide();

	// 判定用位置座標更新
	CollRectUpdate();
}

void Player::Draw()
{
	// プレイヤーの描画
	DrawRotaGraphF(m_airframe.pos.x, m_airframe.pos.y, m_airframe.size, m_airframe.rota, m_hGraph, true);

#if _DEBUG
	// 判定用デバッグ描画
	DrawBox(m_collRect.left.x, m_collRect.left.y, m_collRect.right.x, m_collRect.right.y, 0xff0000, false);
#endif
}

Vec2 Player::GetPos() const
{
	return m_airframe.pos;
}

Rect Player::GetCollData()const
{
	return m_collRect;
}

int Player::GetShootingNum()const
{
	return m_shootingNum;
}

void Player::Input()
{
	// ベクトル
	Vec2 vec = {0.0f,0.0f};

	// 移動
	if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP))
	{
		vec.y += -1.0f;
	}
	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT))
	{
		vec.x += -1.0f;
	}
	if (CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_DOWN))
	{
		vec.y += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT))
	{
		vec.x += 1.0f;
	}

	// ショット
	if (CheckHitKey(KEY_INPUT_SPACE) || GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		// 発射する数を指定
		m_shootingNum = 1;
	}
	else
	{
		m_shootingNum = 0;
	}

	// ベクトルの長さを計算
	const float length = sqrtf(vec.x * vec.x + vec.y * vec.y);

	// 長さが0でない場合のみノーマライズ
	if (length > 0.0f)
	{
		vec.x /= length;
		vec.y /= length;
	}

	// 位置を変更
	m_airframe.pos.x += vec.x * kSpeed;
	m_airframe.pos.y += vec.y * kSpeed;
}

void Player::OutSide()
{
	// 左
	m_airframe.pos.x = (std::max)(m_airframe.pos.x, 0.0f);

	// 右
	m_airframe.pos.x = (std::min)(m_airframe.pos.x, DxLibSystem::kScreenWidthF);

	// 上
	m_airframe.pos.y = (std::max)(m_airframe.pos.y, 0.0f);

	// 下
	m_airframe.pos.y = (std::min)(m_airframe.pos.y, DxLibSystem::kScreenHeightF);
}

void Player::CollRectUpdate()
{
	m_collRect.left.x  = m_airframe.pos.x - kLeftXSize;
	m_collRect.left.y  = m_airframe.pos.y - kLeftYSize;
	m_collRect.right.x = m_airframe.pos.x + kRightXSize;
	m_collRect.right.y = m_airframe.pos.y + kRightYSize;
}
