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
	// インスタンスの生成
	m_pMap           = new Map();
	m_pPlayerManager = new PlayerManager();
	m_pEnemyManager  = new EnemyManager();
	m_pShotManager   = new ShotManager();
	m_pItemManager   = new ItemManager();
}

void SceneManager::End()
{
	// 解放処理
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
	// 更新処理
	m_pMap->Update();
	m_pPlayerManager->Update();
	m_pEnemyManager->Update();
	m_pShotManager->Update();

	// プレイヤーマネージャーからプレイヤーを取得
	std::list<Player*>& players = m_pPlayerManager->GetPlayerData();
	
	// ショットマネージャーからショットを取得
	std::list<ShotBase*>& shots = m_pShotManager->GetShotData();

	// エネミーマネージャーからエネミーを取得
	std::list<EnemyBase*>& enemies = m_pEnemyManager->GetEnemyData();

	// アイテムマネージャーからアイテムを取得
	std::list<ItemBase*>& items = m_pItemManager->GetItemData();

	// プレイヤー
	for (auto& player : players)
	{
		// 1つ以上の弾を発射していた場合弾を生成
		if (player->GetShootingNum() >= 1)
		{
			//	m_pShotManager->CreateShotNormal(m_pPlayer->GetPos());
			m_pShotManager->CreateShotMissile(player->GetPos());
			//	m_pShotManager->CreateShotRocket(m_pPlayer->GetPos());
		}

		// プレイヤーの判定座標
		const Rect playerRectData = player->GetCollData();

		// プレイヤーとエネミーの判定
		for (auto& enemy : enemies)
		{
			if (Collision2D::CheckRect(playerRectData, enemy->GetCollData()))
			{
			}
		}

		// プレイヤーとアイテム
		for (auto& item : items)
		{
			if (Collision2D::CheckRect(playerRectData, item->GetCollData()))
			{
				// アイテムに当たったことを確認
				item->IsHitObject();
			}

			// アイテムにプレイヤー座標を渡す
			item->SetPos(player->GetPos());
		}
	}

	// 弾とエネミーの判定
	for (auto& shot : shots)
	{
		for (auto& enemy : enemies)
		{
			// 判定のチェックをする
			if (Collision2D::CheckRect(shot->GetCollData(), enemy->GetCollData()))
			{
				// ダメージを与える
				enemy->SetDamage(shot->GetDamage());

				// ショットの耐久力を減らす
				shot->SetCheckHit();
			}
		}

		for (auto& player : players)
		{

		}
	}

	// アイテム更新処理
	m_pItemManager->Update();
}

void SceneManager::Draw()
{
	// 描画処理
	m_pMap->Draw();
	m_pItemManager->Draw();
	m_pShotManager->Draw();
	m_pEnemyManager->Draw();
	m_pPlayerManager->Draw();
}
