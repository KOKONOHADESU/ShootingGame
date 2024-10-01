#include "SceneManager.h"

#include "../Object/Map/Map.h"
#include "../Object/Player/Player.h"
#include "../Object/Shot/ShotNomal.h"
#include "../Object/Shot/ShotManager.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Enemy/EnemyBase.h"

#include "../Util/Collision2D.h"

#include <DxLib.h>

SceneManager::SceneManager():
	m_pMap(nullptr),
	m_pPlayer(nullptr),
	m_pEnemyManager(nullptr),
	m_pShotManager(nullptr)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	// �C���X�^���X�̐���
	m_pMap          = new Map();
	m_pPlayer       = new Player();
	m_pEnemyManager = new EnemyManager();
	m_pShotManager  = new ShotManager();

	// ������
	m_pMap->Init();
	m_pPlayer->Init();
	m_pEnemyManager->Init();
	m_pShotManager->Init();
}

void SceneManager::End()
{
	// �������
	m_pMap->End();
	m_pPlayer->End();
	m_pEnemyManager->End();
	m_pShotManager->End();

	delete m_pMap;
	delete m_pPlayer;
	delete m_pEnemyManager;
	delete m_pShotManager;

	m_pMap          = nullptr;
	m_pPlayer       = nullptr;
	m_pEnemyManager = nullptr;
	m_pShotManager  = nullptr;
}

void SceneManager::Update()
{
	// �X�V����
	m_pMap->Update();
	m_pPlayer->Update();
	m_pEnemyManager->Update();
	m_pShotManager->Update();

	// 1�ȏ�̒e�𔭎˂��Ă����ꍇ�e�𐶐�
	if (m_pPlayer->GetShootingNum() >= 1)
	{
		m_pShotManager->SetInitShot(m_pPlayer->GetPos());
	}

	// �v���C���[����V���b�g���X�g���擾
	std::list<ShotNomal*>& shots = m_pShotManager->GetShotData();

	// �G�l�~�[�}�l�[�W���[����G�l�~�[���擾
	std::list<EnemyBase*>& enemies = m_pEnemyManager->GetEnemyData();

	for (auto& shot : shots)
	{
		for (auto& enemy : enemies)
		{
			// ����̃`�F�b�N������
			if (Collision2D::CheckRect(shot->GetCollData(),enemy->GetCollData()))
			{
				// �_���[�W��^����
				enemy->SetDamage(shot->GetDamage());

				// �V���b�g�̑ϋv�͂����炷
				shot->SetCheckHit();
			}
		}
	}
}

void SceneManager::Draw()
{
	// �`�揈��
	m_pMap->Draw();
	m_pShotManager->Draw();
	m_pEnemyManager->Draw();
	m_pPlayer->Draw();
}
