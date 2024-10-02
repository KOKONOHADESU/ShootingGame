#include "ShotManager.h"

#include "ShotNomal.h"
#include "ShotMissile.h"

#include <DxLib.h>
#include <string>

namespace
{
	const char* const kShotNomalpath = "Data/Image/Shot/shot.png";

	const char* const kShotMissilepath = "Data/Image/Player/Shoot/Shoot1.png";

	// �t�@�C���p�X
	std::vector<std::string>kGraphFilePath =
	{
		"Data/Image/Shot/shot.png",			// �V���b�g
		"Data/Image/Player/Shoot/Shoot1.png"// �~�T�C��
	};
}

ShotManager::ShotManager()
{
}

ShotManager::~ShotManager()
{
}

void ShotManager::Init()
{
	// �ǂݍ��݃t�@�C���̐�
	m_handle.resize(static_cast<int>(kGraphFilePath.size()));
	for (int i = 0; i < static_cast<int>(kGraphFilePath.size()); i++)
	{
		m_handle[i].push_back(LoadGraph(kGraphFilePath[i].c_str()));
	}	
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

	for (int i = 0; i < static_cast<int>(kGraphFilePath.size()); i++)
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

void ShotManager::SetInitShot(Vec2 startPos)
{
	// �V���b�g�̏�����
	m_pShot.push_back(new ShotNomal(startPos, m_handle[0]));
}
