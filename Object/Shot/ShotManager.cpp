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
	// �摜�^�C�v���w��
	InitType(m_handle, 2);
	// �摜�^�C�v�ʉ摜���������w��
	InitGraphic(m_handle, 0, kShotNomalpath, 1, 1);
	InitGraphic(m_handle, 1, kShotMissilepath, 3, 1);
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

void ShotManager::InitType(std::vector<std::vector<int>>& handle, int shotTypeNum)
{
	// �V���b�g�̎�ޕ��̔z��𐶐�
	handle.resize(shotTypeNum);
}

void ShotManager::InitGraphic(std::vector<std::vector<int>>& handle, int shotType, const char* path, int graphXNum, int graphYNum)
{
	if (graphXNum * graphYNum == 1)
	{
		handle[shotType].push_back(LoadGraph(path));
	}
	else
	{
		float x = 0.0f;
		float y = 0.0f;
	//	GetGraphSizeF(handle[shotType], &x, &y)
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
