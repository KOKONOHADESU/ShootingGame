#include "SceneManager.h"

#include "../Object/Map/Map.h"
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
	m_pPlayer(nullptr),
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
	m_pMap          = new Map();
	m_pPlayer       = new Player();
	m_pEnemyManager = new EnemyManager();
	m_pShotManager  = new ShotManager();
	m_pItemManager  = new ItemManager();

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
	m_pItemManager->End();

	delete m_pMap;
	delete m_pPlayer;
	delete m_pEnemyManager;
	delete m_pShotManager;
	delete m_pItemManager;

	m_pMap          = nullptr;
	m_pPlayer       = nullptr;
	m_pEnemyManager = nullptr;
	m_pShotManager  = nullptr;
	m_pItemManager = nullptr;
}

void SceneManager::Update()
{
	// �X�V����
	m_pMap->Update();
	m_pPlayer->Update();
	m_pEnemyManager->Update();
	m_pShotManager->Update();

	// �A�C�e���}�l�[�W���[�Ɉʒu���W��n��
	m_pItemManager->SetPos(m_pPlayer->GetPos());
	m_pItemManager->Update();

	// 1�ȏ�̒e�𔭎˂��Ă����ꍇ�e�𐶐�
	if (m_pPlayer->GetShootingNum() >= 1)
	{
	//	m_pShotManager->CreateShotNormal(m_pPlayer->GetPos());
		m_pShotManager->CreateShotMissile(m_pPlayer->GetPos());
	//	m_pShotManager->CreateShotRocket(m_pPlayer->GetPos());
	}

	// �V���b�g�}�l�[�W���[����V���b�g���X�g���擾
	std::list<ShotBase*>& shots = m_pShotManager->GetShotData();

	// �G�l�~�[�}�l�[�W���[����G�l�~�[���擾
	std::list<EnemyBase*>& enemies = m_pEnemyManager->GetEnemyData();

	// �A�C�e���}�l�[�W���[����A�C�e�����擾
	std::list<ItemBase*>& items = m_pItemManager->GetItemData();
	
	// �v���C���[�̔�����W
	const Rect player = m_pPlayer->GetCollData();

	// �e�ƃG�l�~�[�̔���
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
	// �v���C���[�ƃG�l�~�[�̔���
	for (auto& enemy : enemies)
	{
		if (Collision2D::CheckRect(player, enemy->GetCollData()))
		{
		}
	}
	// �v���C���[�ƃA�C�e��
	for (auto& item : items)
	{
		if (Collision2D::CheckRect(player, item->GetCollData()))
		{
			// �A�C�e���ɓ����������Ƃ��m�F
			item->IsHitObject();
		}
	}	
}

void SceneManager::Draw()
{
	// �`�揈��
	m_pMap->Draw();
	m_pItemManager->Draw();
	m_pShotManager->Draw();
	m_pEnemyManager->Draw();
	m_pPlayer->Draw();
}
