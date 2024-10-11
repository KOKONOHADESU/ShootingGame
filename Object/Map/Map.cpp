#include "Map.h"

#include "../../Util/DxLibSystem.h"

#include <DxLib.h>

namespace
{
	// 背景スクロール速度
	constexpr float kMidScrollSpeed = 7.0f / 2.0f;

	constexpr float kSideScrollSpeed = 7.0f;
}

Map::Map()
{
	// 初期化
	for (int i = 0; i < BGType::MAX; i++)
	{
		m_hBg[i] = -1;

		m_bgSize[i].x = 0.0f;
		m_bgSize[i].y = 0.0f;
	}

	// マップの初期化
	Init();
}

Map::~Map()
{
	// メモリ解放
	for (int i = 0; i < BGType::MAX; i++)
	{
		DeleteGraph(m_hBg[i]);
	}
}

void Map::Init()
{
	// 背景画像の読み込み
	m_hBg[BGType::ALL]       = LoadGraph("Data/Image/Map/bg0.png");
	m_hBg[BGType::MID]       = LoadGraph("Data/Image/Map/bg1.png");
	m_hBg[BGType::SIDELEFT]  = LoadGraph("Data/Image/Map/bg2.png");
	m_hBg[BGType::SIDERIGHT] = LoadGraph("Data/Image/Map/bg3.png");

	// 画像サイズの取得
	GetGraphSizeF(m_hBg[BGType::ALL],       &m_bgSize[BGType::ALL].x,       &m_bgSize[BGType::ALL].y);
	GetGraphSizeF(m_hBg[BGType::MID],       &m_bgSize[BGType::MID].x,       &m_bgSize[BGType::MID].y);
	GetGraphSizeF(m_hBg[BGType::SIDELEFT],  &m_bgSize[BGType::SIDELEFT].x,  &m_bgSize[BGType::SIDELEFT].y);
	GetGraphSizeF(m_hBg[BGType::SIDERIGHT], &m_bgSize[BGType::SIDERIGHT].x, &m_bgSize[BGType::SIDERIGHT].y);

	// 画像サイズの調整
	m_bgSize[BGType::MID].x *= 1.8f;
	m_bgSize[BGType::MID].y *= 1.8f;

	m_bgSize[BGType::SIDELEFT].x *= 1.4f;
	m_bgSize[BGType::SIDELEFT].y *= 1.4f;

	m_bgSize[BGType::SIDERIGHT].x *= 1.4f;
	m_bgSize[BGType::SIDERIGHT].y *= 1.4f;

	// 画像位置の調整
	Rect bgAllPos
	{
		{0.0f,0.0f},
		{ DxLibSystem::kScreenWidthF,DxLibSystem::kScreenHeightF }
	};
	m_graphPos[BGType::ALL].push_back(bgAllPos);

	Rect bgMidPos
	{
		{(DxLibSystem::kScreenWidthF / 2) - (m_bgSize[BGType::MID].x / 2.0f),0.0f},
		{(DxLibSystem::kScreenWidthF / 2) - (m_bgSize[BGType::MID].x / 2.0f) + m_bgSize[BGType::MID].x,m_bgSize[BGType::MID].y}
	};
	for (float y = -m_bgSize[BGType::MID].y; y < DxLibSystem::kScreenHeightF; y += m_bgSize[BGType::MID].y)
	{
		bgMidPos.left.y  = y;
		bgMidPos.right.y = y + m_bgSize[BGType::MID].y;

		m_graphPos[BGType::MID].push_back(bgMidPos);
	}

	Rect bgLeftPos
	{
		{0.0f,0.0f},
		{ m_bgSize[BGType::SIDELEFT].x,m_bgSize[BGType::SIDELEFT].y}
	};
	Rect bgLeftSecondPos
	{
		{0.0f,-m_bgSize[BGType::SIDELEFT].y},
		{ m_bgSize[BGType::SIDELEFT].x,0.0f}
	};
	m_graphPos[BGType::SIDELEFT].push_back(bgLeftPos);
	m_graphPos[BGType::SIDELEFT].push_back(bgLeftSecondPos);

	Rect bgRightPos
	{
		{DxLibSystem::kScreenWidthF - m_bgSize[BGType::SIDERIGHT].x,0.0f},
		{DxLibSystem::kScreenWidthF,m_bgSize[BGType::SIDERIGHT].y }
	};
	Rect bgRightSecondPos
	{
		{DxLibSystem::kScreenWidthF - m_bgSize[BGType::SIDERIGHT].x, -m_bgSize[BGType::SIDERIGHT].y},
		{DxLibSystem::kScreenWidthF,0.0f}
	};
	m_graphPos[BGType::SIDERIGHT].push_back(bgRightPos);
	m_graphPos[BGType::SIDERIGHT].push_back(bgRightSecondPos);
}

void Map::Update()
{		
	// スクロール更新処理
	Scroll(BGType::MID, kMidScrollSpeed);
	Scroll(BGType::SIDERIGHT, kSideScrollSpeed);
	Scroll(BGType::SIDELEFT, kSideScrollSpeed);
}

void Map::Draw()
{
	// 全体の背景描画
	DrawExtendGraphF(
		m_graphPos[BGType::ALL][0].left.x,
		m_graphPos[BGType::ALL][0].left.y,
		m_graphPos[BGType::ALL][0].right.x,
		m_graphPos[BGType::ALL][0].right.y,
		m_hBg[BGType::ALL], true);

	// 画面中心画像の描画
	for (int i = 0; i < m_graphPos[BGType::MID].size(); i++)
	{
		DrawExtendGraphF(
			m_graphPos[BGType::MID][i].left.x,
			m_graphPos[BGType::MID][i].left.y,
			m_graphPos[BGType::MID][i].right.x,
			m_graphPos[BGType::MID][i].right.y,
			m_hBg[BGType::MID],
			true);
	}

	// 画面端の画像描画左
	for (int i = 0; i < m_graphPos[BGType::SIDELEFT].size(); i++)
	{
		DrawExtendGraphF(
			m_graphPos[BGType::SIDELEFT][i].left.x,
			m_graphPos[BGType::SIDELEFT][i].left.y,
			m_graphPos[BGType::SIDELEFT][i].right.x,
			m_graphPos[BGType::SIDELEFT][i].right.y,
			m_hBg[BGType::SIDELEFT],true);
	}

	// 画面端の画像描画右
	for (int i = 0; i < m_graphPos[BGType::SIDERIGHT].size(); i++)
	{
		DrawExtendGraphF(
			m_graphPos[BGType::SIDERIGHT][i].left.x,
			m_graphPos[BGType::SIDERIGHT][i].left.y,
			m_graphPos[BGType::SIDERIGHT][i].right.x,
			m_graphPos[BGType::SIDERIGHT][i].right.y,
			m_hBg[BGType::SIDERIGHT], true);
	}
}

void Map::Scroll(BGType type, float speed)
{
	// 画面中心のスクロール
	for (size_t i = 0; i < m_graphPos[type].size(); i++)
	{
		// スクロール処理
		m_graphPos[type][i].left.y += speed;
		m_graphPos[type][i].right.y += speed;

		// 画面外にいる場合
		if (m_graphPos[type][i].left.y > DxLibSystem::kScreenHeightF)
		{
			m_graphPos[type][i].left.y = -m_bgSize[type].y;
			m_graphPos[type][i].right.y = 0.0f;
		}
	}
}
