#include "ShotManager.h"

#include "ShotNomal.h"
#include "ShotMissile.h"
#include "ShotRocket.h"

#include "../../Util/GraphicSprite.h"
#include "../../Util/ShotType.h"

#include <DxLib.h>
#include <string>

namespace
{
	// �摜�t�@�C���p�X
	// �m�[�}���V���b�g
	const char* const kShotNomalPath = "Data/Image/Shot/shot.png";
	// �~�T�C���V���b�g
	const char* const kShotMissilePath = "Data/Image/Shot/Shoot1.png";
	// ���P�b�g�V���b�g
	const char* const kShotRocketPath = "Data/Image/Shot/Shoot2.png";

	// �m�[�}���V���b�g
	constexpr int kShotNomalGrapicNumX = 1;
	constexpr int kShotNomalGrapicNumY = 1;

	// �~�T�C���V���b�g
	constexpr int kShotMissileGrapicNumX = 3;
	constexpr int kShotMissileGrapicNumY = 1;

	// ���P�b�g�V���b�g
	constexpr int kShotRocketGrapicNumX = 4;
	constexpr int kShotRocketGrapicNumY = 1;
}

ShotManager::ShotManager()
{
}

ShotManager::~ShotManager()
{
}

void ShotManager::Init()
{
	// �摜�^�C�v���w��
	GraphicSprite::InitType(m_handle, ShotType::MAX);
	// �摜�^�C�v�ʉ摜���������w��
	GraphicSprite::InitGraphic(m_handle, ShotType::NORMAL, kShotNomalPath, kShotNomalGrapicNumX, kShotNomalGrapicNumY);
	GraphicSprite::InitGraphic(m_handle, ShotType::MISSILE, kShotMissilePath, kShotMissileGrapicNumX, kShotMissileGrapicNumY);
	GraphicSprite::InitGraphic(m_handle, ShotType::ROCKET, kShotRocketPath, kShotRocketGrapicNumX, kShotRocketGrapicNumY);
}

void ShotManager::End()
{
	// �������
	for (auto it = m_pShot.begin(); it != m_pShot.end(); ++it)
	{
		// ���������
		(*it)->End();
		delete* it;
		(*it) = nullptr;
	}

	for (int i = 0; i < static_cast<int>(ShotType::MAX); i++)
	{
		for (int j = 0; j < m_handle[i].size(); j++)
		{
			DeleteGraph(m_handle[i][j]);
		}
	}
}

void ShotManager::Update()
{
	// �X�V
	for (auto& shot : m_pShot)
	{
		shot->Update();
	}

	// ���݂��m�F����
	CheckEnable();
}

void ShotManager::Draw()
{
	// �`��
	for (auto& shot : m_pShot)
	{
		shot->Draw();
	}
}

void ShotManager::CheckEnable()
{
	// �V���b�g�̑��݂��m�F
	for (auto it = m_pShot.begin(); it != m_pShot.end();)
	{
		// �G�l�~�[�̑��݂�������ꍇ
		if (!(*it)->IsEnable())
		{
			// ���������
			(*it)->End();
			delete* it;

			// ���X�g����v�f���폜
			it = m_pShot.erase(it);
		}
		else
		{
			// �폜���Ȃ��ꍇ�͎��̗v�f�֐i��
			++it;
		}
	}
}

std::list<ShotBase*>& ShotManager::GetShotData()
{
	return m_pShot;
}

void ShotManager::CreateShotNormal(Vec2 startPos)
{
	// �m�[�}���V���b�g�̏�����
	m_pShot.push_back(new ShotNomal(startPos, m_handle[ShotType::NORMAL]));
}

void ShotManager::CreateShotMissile(Vec2 startPos)
{
	Vec2 pos = startPos;

	pos.x = startPos.x + 30.0f;

	// �~�T�C���V���b�g�̏�����
	m_pShot.push_back(new ShotMissile(pos, m_handle[ShotType::MISSILE]));

	pos.x = startPos.x - 30.0f;

	// �~�T�C���V���b�g�̏�����
	m_pShot.push_back(new ShotMissile(pos, m_handle[ShotType::MISSILE]));
}

void ShotManager::CreateShotRocket(Vec2 startPos)
{
	// ���P�b�g�V���b�g�̏�����
	m_pShot.push_back(new ShotRocket(startPos, m_handle[ShotType::ROCKET]));
}
