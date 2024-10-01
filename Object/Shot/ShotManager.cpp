#include "ShotManager.h"

#include "ShotNomal.h"

ShotManager::ShotManager()
{
}

ShotManager::~ShotManager()
{
}

void ShotManager::Init()
{
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

std::list<ShotNomal*>& ShotManager::GetShotData()
{
	return m_pShot;
}

void ShotManager::SetInitShot(Vec2 startPos)
{
	// �V���b�g�̏�����
	m_pShot.push_back(new ShotNomal(startPos));
}
