#include "Map.h"

#include "../../Util/DxLibSystem.h"

#include <DxLib.h>

namespace
{
	// �w�i�X�N���[�����x
	constexpr float kMidScrollSpeed = 7.0f / 2.0f;

	constexpr float kSideScrollSpeed = 7.0f;
}

Map::Map()
{
	// ������
	for (int i = 0; i < BGType::MAX; i++)
	{
		m_hBg[i] = -1;

		m_bgSize[i].x = 0.0f;
		m_bgSize[i].y = 0.0f;
	}

	// �}�b�v�̏�����
	Init();
}

Map::~Map()
{
	// ���������
	for (int i = 0; i < BGType::MAX; i++)
	{
		DeleteGraph(m_hBg[i]);
	}
}

void Map::Init()
{
	// �w�i�摜�̓ǂݍ���
	m_hBg[BGType::ALL]       = LoadGraph("Data/Image/Map/bg0.png");
	m_hBg[BGType::MID]       = LoadGraph("Data/Image/Map/bg1.png");
	m_hBg[BGType::SIDELEFT]  = LoadGraph("Data/Image/Map/bg2.png");
	m_hBg[BGType::SIDERIGHT] = LoadGraph("Data/Image/Map/bg3.png");

	// �摜�T�C�Y�̎擾
	GetGraphSizeF(m_hBg[BGType::ALL],       &m_bgSize[BGType::ALL].x,       &m_bgSize[BGType::ALL].y);
	GetGraphSizeF(m_hBg[BGType::MID],       &m_bgSize[BGType::MID].x,       &m_bgSize[BGType::MID].y);
	GetGraphSizeF(m_hBg[BGType::SIDELEFT],  &m_bgSize[BGType::SIDELEFT].x,  &m_bgSize[BGType::SIDELEFT].y);
	GetGraphSizeF(m_hBg[BGType::SIDERIGHT], &m_bgSize[BGType::SIDERIGHT].x, &m_bgSize[BGType::SIDERIGHT].y);

	// �摜�T�C�Y�̒���
	m_bgSize[BGType::MID].x *= 1.8f;
	m_bgSize[BGType::MID].y *= 1.8f;

	m_bgSize[BGType::SIDELEFT].x *= 1.4f;
	m_bgSize[BGType::SIDELEFT].y *= 1.4f;

	m_bgSize[BGType::SIDERIGHT].x *= 1.4f;
	m_bgSize[BGType::SIDERIGHT].y *= 1.4f;

	// �摜�ʒu�̒���
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
	// �X�N���[���X�V����
	Scroll(BGType::MID, kMidScrollSpeed);
	Scroll(BGType::SIDERIGHT, kSideScrollSpeed);
	Scroll(BGType::SIDELEFT, kSideScrollSpeed);
}

void Map::Draw()
{
	// �S�̂̔w�i�`��
	DrawExtendGraphF(
		m_graphPos[BGType::ALL][0].left.x,
		m_graphPos[BGType::ALL][0].left.y,
		m_graphPos[BGType::ALL][0].right.x,
		m_graphPos[BGType::ALL][0].right.y,
		m_hBg[BGType::ALL], true);

	// ��ʒ��S�摜�̕`��
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

	// ��ʒ[�̉摜�`�捶
	for (int i = 0; i < m_graphPos[BGType::SIDELEFT].size(); i++)
	{
		DrawExtendGraphF(
			m_graphPos[BGType::SIDELEFT][i].left.x,
			m_graphPos[BGType::SIDELEFT][i].left.y,
			m_graphPos[BGType::SIDELEFT][i].right.x,
			m_graphPos[BGType::SIDELEFT][i].right.y,
			m_hBg[BGType::SIDELEFT],true);
	}

	// ��ʒ[�̉摜�`��E
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
	// ��ʒ��S�̃X�N���[��
	for (size_t i = 0; i < m_graphPos[type].size(); i++)
	{
		// �X�N���[������
		m_graphPos[type][i].left.y += speed;
		m_graphPos[type][i].right.y += speed;

		// ��ʊO�ɂ���ꍇ
		if (m_graphPos[type][i].left.y > DxLibSystem::kScreenHeightF)
		{
			m_graphPos[type][i].left.y = -m_bgSize[type].y;
			m_graphPos[type][i].right.y = 0.0f;
		}
	}
}
