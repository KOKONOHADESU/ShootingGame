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
	// ノーマルエネミー生成フレーム
	constexpr int kNomalEnemySpawnFrameMax = 1;

	// ファイルパス
	const char* const kEnemyNormalPath = "Data/Image/Enemy/enemy1.png";
	const char* const kEnemyDeadPath   = "Data/Image/Destroy/explosion.png";

	// ノーマルエネミー
	constexpr int kEnemyNormalGrapicNumX = 1;
	constexpr int kEnemyNormalGrapicNumY = 1;

	// エネミー死亡演出
	constexpr int kEnemyDeadGrapicNumX = 7;
	constexpr int kEnemyDeadGrapicNumY = 1;
}

EnemyManager::EnemyManager():
	m_normalEnemyFrameSpawnCount(0)
{
	// 画像タイプを指定
	GraphicSprite::InitType(m_handle, EnemyType::MAX);
	// 画像タイプ別画像分割数を指定
	GraphicSprite::InitGraphic(m_handle, EnemyType::NORMAL, kEnemyNormalPath, kEnemyNormalGrapicNumX, kEnemyNormalGrapicNumY);

	// 画像死亡タイプを指定
	GraphicSprite::InitType(m_hDead, 1);
	// 画像タイプ別画像分割数を指定
	GraphicSprite::InitGraphic(m_hDead, 0, kEnemyDeadPath, kEnemyDeadGrapicNumX, kEnemyDeadGrapicNumY);
}

EnemyManager::~EnemyManager()
{
	// 解放処理
	for (auto it = m_pEnemy.begin(); it != m_pEnemy.end(); ++it)
	{
		// メモリ解放
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
	// ノーマルエネミー管理
	NomalUpdate();

	// 存在を確認する
	CheckEnable();

	// 更新処理
	for (auto& enemy : m_pEnemy)
	{
		enemy->Update();
	}
}

void EnemyManager::Draw()
{
	// 描画処理
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
	// エネミーの存在を確認
	for (auto it = m_pEnemy.begin(); it != m_pEnemy.end();)
	{
		// エネミーの存在が消える場合
		if (!(*it)->IsEnable())
		{
			// メモリ解放
			(*it)->End();
			delete* it;

			// リストから要素を削除
			it = m_pEnemy.erase(it);
		}
		else
		{
			// 削除しない場合は次の要素へ進む
			++it;
		}
	}
}

void EnemyManager::NomalUpdate()
{
	// カウントが指定したフレームに到達した場合ノーマルエネミーを生成する
	if (m_normalEnemyFrameSpawnCount == kNomalEnemySpawnFrameMax)
	{
		// 生成
		NomalSpawn();
		m_normalEnemyFrameSpawnCount = 0;
	}
	else
	{
		// フレームカウント
		m_normalEnemyFrameSpawnCount++;
	}
}

void EnemyManager::NomalSpawn()
{
	// 機体の初期化
	Airframe data{};
	data.pos = Vec2{ static_cast<float>(MTRandom::GetInstance()->GetMTRand(0,DxLibSystem::kScreenWidth)),0.0f };
	data.rota = 0.0f;
	data.size = 1.0f;

	// 機体の追加
	m_pEnemy.push_back(new EnemyNormal(data,m_handle[EnemyType::NORMAL], m_hDead[0]));
}
