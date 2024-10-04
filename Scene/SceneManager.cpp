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
	// インスタンスの生成
	m_pMap          = new Map();
	m_pPlayer       = new Player();
	m_pEnemyManager = new EnemyManager();
	m_pShotManager  = new ShotManager();
	m_pItemManager  = new ItemManager();

	// 初期化
	m_pMap->Init();
	m_pPlayer->Init();
	m_pEnemyManager->Init();
	m_pShotManager->Init();
}

void SceneManager::End()
{
	// 解放処理
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
	// 更新処理
	m_pMap->Update();
	m_pPlayer->Update();
	m_pEnemyManager->Update();
	m_pShotManager->Update();

	// アイテムマネージャーに位置座標を渡す
	m_pItemManager->SetPos(m_pPlayer->GetPos());
	m_pItemManager->Update();

	// 1つ以上の弾を発射していた場合弾を生成
	if (m_pPlayer->GetShootingNum() >= 1)
	{
	//	m_pShotManager->CreateShotNormal(m_pPlayer->GetPos());
		m_pShotManager->CreateShotMissile(m_pPlayer->GetPos());
	//	m_pShotManager->CreateShotRocket(m_pPlayer->GetPos());
	}

	// ショットマネージャーからショットリストを取得
	std::list<ShotBase*>& shots = m_pShotManager->GetShotData();

	// エネミーマネージャーからエネミーを取得
	std::list<EnemyBase*>& enemies = m_pEnemyManager->GetEnemyData();

	// アイテムマネージャーからアイテムを取得
	std::list<ItemBase*>& items = m_pItemManager->GetItemData();
	
	// プレイヤーの判定座標
	const Rect player = m_pPlayer->GetCollData();

	// 弾とエネミーの判定
	for (auto& shot : shots)
	{
		for (auto& enemy : enemies)
		{
			// 判定のチェックをする
			if (Collision2D::CheckRect(shot->GetCollData(),enemy->GetCollData()))
			{
				// ダメージを与える
				enemy->SetDamage(shot->GetDamage());

				// ショットの耐久力を減らす
				shot->SetCheckHit();
			}
		}
	}
	// プレイヤーとエネミーの判定
	for (auto& enemy : enemies)
	{
		if (Collision2D::CheckRect(player, enemy->GetCollData()))
		{
		}
	}
	// プレイヤーとアイテム
	for (auto& item : items)
	{
		if (Collision2D::CheckRect(player, item->GetCollData()))
		{
			// アイテムに当たったことを確認
			item->IsHitObject();
		}
	}	
}

void SceneManager::Draw()
{
	// 描画処理
	m_pMap->Draw();
	m_pItemManager->Draw();
	m_pShotManager->Draw();
	m_pEnemyManager->Draw();
	m_pPlayer->Draw();
}
