#include "SceneManager.h"

#include "../Object/Map/Map.h"
#include "../Object/Player/PlayerManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Shot/ShotManager.h"
#include "../Object/Shot/ShotBase.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Item/ItemManager.h"
#include "../Object/Item/ItemBase.h"

#include "../Util/Collision2D.h"

#include <DxLib.h>

SceneManager::SceneManager():
	m_pMap(nullptr),
	m_pPlayerManager(nullptr),
	m_pEnemyManager(nullptr),
	m_pShotManager(nullptr),
	m_pItemManager(nullptr)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	// �C���X�^���X�̐���
	m_pMap           = new Map();
	m_pPlayerManager = new PlayerManager();
	m_pEnemyManager  = new EnemyManager();
	m_pShotManager   = new ShotManager();
	m_pItemManager   = new ItemManager();
}

void SceneManager::End()
{
	// �������
	delete m_pMap;
	delete m_pPlayerManager;
	delete m_pEnemyManager;
	delete m_pShotManager;
	delete m_pItemManager;

	m_pMap           = nullptr;
	m_pPlayerManager = nullptr;
	m_pEnemyManager  = nullptr;
	m_pShotManager   = nullptr;
	m_pItemManager   = nullptr;
}

void SceneManager::Update()
{
	// �X�V����
	m_pMap->Update();
	m_pPlayerManager->Update();
	m_pEnemyManager->Update();
	m_pShotManager->Update();

	// �v���C���[�}�l�[�W���[����v���C���[���擾
	std::list<Player*>& players = m_pPlayerManager->GetPlayerData();
	
	// �V���b�g�}�l�[�W���[����V���b�g���擾
	std::list<ShotBase*>& shots = m_pShotManager->GetShotData();

	// �G�l�~�[�}�l�[�W���[����G�l�~�[���擾
	std::list<EnemyBase*>& enemies = m_pEnemyManager->GetEnemyData();

	// �A�C�e���}�l�[�W���[����A�C�e�����擾
	std::list<ItemBase*>& items = m_pItemManager->GetItemData();

	// �v���C���[
	for (auto& player : players)
	{
		// 1�ȏ�̒e�𔭎˂��Ă����ꍇ�e�𐶐�
		if (player->GetShootingNum() >= 1)
		{
			//	m_pShotManager->CreateShotNormal(m_pPlayer->GetPos());
			m_pShotManager->CreateShotMissile(player->GetPos());
			//	m_pShotManager->CreateShotRocket(m_pPlayer->GetPos());
		}

		// �v���C���[�̔�����W
		const Rect playerRectData = player->GetCollData();

		// �v���C���[�ƃG�l�~�[�̔���
		for (auto& enemy : enemies)
		{
			if (Collision2D::CheckRect(playerRectData, enemy->GetCollData()))
			{
			}
		}

		// �v���C���[�ƃA�C�e��
		for (auto& item : items)
		{
			if (Collision2D::CheckRect(playerRectData, item->GetCollData()))
			{
				// �A�C�e���ɓ����������Ƃ��m�F
				item->IsHitObject();
			}

			// �A�C�e���Ƀv���C���[���W��n��
			item->SetPos(player->GetPos());
		}
	}

	// �e�ƃG�l�~�[�̔���
	for (auto& shot : shots)
	{
		for (auto& enemy : enemies)
		{
			// ����̃`�F�b�N������
			if (Collision2D::CheckRect(shot->GetCollData(), enemy->GetCollData()))
			{
				// �_���[�W��^����
				enemy->SetDamage(shot->GetDamage());

				// �V���b�g�̑ϋv�͂����炷
				shot->SetCheckHit();
			}
		}

		for (auto& player : players)
		{

		}
	}

	// �A�C�e���X�V����
	m_pItemManager->Update();
}

void SceneManager::Draw()
{
	// �`�揈��
	m_pMap->Draw();
	m_pItemManager->Draw();
	m_pShotManager->Draw();
	m_pEnemyManager->Draw();
	m_pPlayerManager->Draw();
}
