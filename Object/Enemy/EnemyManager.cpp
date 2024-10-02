#include "EnemyManager.h"
#include "EnemyNormal.h"

#include "../../Util/Airframe.h"
#include "../../Util/DxLibSystem.h"
#include "../../Util/MTRandom.h"

#include <DxLib.h>

namespace
{
//	constexpr int kNomalEnemySpawnFrameMax = 60 * 1;
	constexpr int kNomalEnemySpawnFrameMax = 1;
}

EnemyManager::EnemyManager():
	m_normalEnemyFrameSpawnCount(0)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{

}

void EnemyManager::End()
{
	// �������
	for (auto it = m_pEnemy.begin(); it != m_pEnemy.end(); ++it)
	{
		// ���������
		(*it)->End();
		delete* it;
		(*it) = nullptr;
	}
}

void EnemyManager::Update()
{
	// �m�[�}���G�l�~�[�Ǘ�
	NomalUpdate();

	// ���݂��m�F����
	CheckEnable();


	// �X�V����
	for (auto& enemy : m_pEnemy)
	{
		enemy->Update();
	}
}

void EnemyManager::Draw()
{
	// �`�揈��
	for (auto& enemy : m_pEnemy)
	{
		enemy->Draw();
	}
}

std::list<EnemyBase*>& EnemyManager::GetEnemyData()
{
	return m_pEnemy;
}

void EnemyManager::CheckEnable()
{
	// �G�l�~�[�̑��݂��m�F
	for (auto it = m_pEnemy.begin(); it != m_pEnemy.end();)
	{
		// �G�l�~�[�̑��݂�������ꍇ
		if (!(*it)->IsEnable())
		{
			// ���������
			(*it)->End();
			delete* it;

			// ���X�g����v�f���폜
			it = m_pEnemy.erase(it);
		}
		else
		{
			// �폜���Ȃ��ꍇ�͎��̗v�f�֐i��
			++it;
		}
	}
}

void EnemyManager::NomalUpdate()
{
	// �J�E���g���w�肵���t���[���ɓ��B�����ꍇ�m�[�}���G�l�~�[�𐶐�����
	if (m_normalEnemyFrameSpawnCount == kNomalEnemySpawnFrameMax)
	{
		// ����
//		NomalSpawn();
		m_normalEnemyFrameSpawnCount = 0;
	}
	else
	{
		// �t���[���J�E���g
		m_normalEnemyFrameSpawnCount++;
	}
}

void EnemyManager::NomalSpawn()
{
	// �@�̂̏�����
	Airframe data{};
	data.pos = Vec2{ static_cast<float>(MTRandom::GetInstance()->GetMTRand(0,DxLibSystem::kScreenWidth)),0.0f };
	data.rota = 0.0f;
	data.size = 1.0f;

	// �@�̂̒ǉ�
	m_pEnemy.push_back(new EnemyNormal(data));
}
