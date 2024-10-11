#include "EnemyManager.h"
#include "EnemyNormal.h"

#include "../../Util/Airframe.h"
#include "../../Util/DxLibSystem.h"
#include "../../Util/MTRandom.h"
#include "../../Util/GraphicSprite.h"
#include "../../Util/EnemyType.h"

#include <DxLib.h>

namespace
{
	// �m�[�}���G�l�~�[�����t���[��
	constexpr int kNomalEnemySpawnFrameMax = 1;

	// �t�@�C���p�X
	const char* const kEnemyNormalPath = "Data/Image/Enemy/enemy1.png";
	const char* const kEnemyDeadPath   = "Data/Image/Destroy/explosion.png";

	// �m�[�}���G�l�~�[
	constexpr int kEnemyNormalGrapicNumX = 1;
	constexpr int kEnemyNormalGrapicNumY = 1;

	// �G�l�~�[���S���o
	constexpr int kEnemyDeadGrapicNumX = 7;
	constexpr int kEnemyDeadGrapicNumY = 1;
}

EnemyManager::EnemyManager():
	m_normalEnemyFrameSpawnCount(0)
{
	// �摜�^�C�v���w��
	GraphicSprite::InitType(m_handle, EnemyType::MAX);
	// �摜�^�C�v�ʉ摜���������w��
	GraphicSprite::InitGraphic(m_handle, EnemyType::NORMAL, kEnemyNormalPath, kEnemyNormalGrapicNumX, kEnemyNormalGrapicNumY);

	// �摜���S�^�C�v���w��
	GraphicSprite::InitType(m_hDead, 1);
	// �摜�^�C�v�ʉ摜���������w��
	GraphicSprite::InitGraphic(m_hDead, 0, kEnemyDeadPath, kEnemyDeadGrapicNumX, kEnemyDeadGrapicNumY);
}

EnemyManager::~EnemyManager()
{
	// �������
	for (auto it = m_pEnemy.begin(); it != m_pEnemy.end(); ++it)
	{
		// ���������
		(*it)->End();
		delete* it;
		(*it) = nullptr;
	}

	for (int i = 0; i < static_cast<int>(EnemyType::MAX); i++)
	{
		for (int j = 0; j < m_handle[i].size(); j++)
		{
			DeleteGraph(m_handle[i][j]);
		}
	}

	for (int i = 0; i < static_cast<int>(1); i++)
	{
		for (int j = 0; j < m_hDead[i].size(); j++)
		{
			DeleteGraph(m_hDead[i][j]);
		}
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
		NomalSpawn();
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
	m_pEnemy.push_back(new EnemyNormal(data,m_handle[EnemyType::NORMAL], m_hDead[0]));
}
