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
	// 解放処理
	for (auto it = m_pShot.begin(); it != m_pShot.end(); ++it)
	{
		// メモリ解放
		(*it)->End();
		delete* it;
		(*it) = nullptr;
	}
}

void ShotManager::Update()
{
	// 更新
	for (auto& shot : m_pShot)
	{
		shot->Update();
	}

	// 存在を確認する
	CheckEnable();
}

void ShotManager::Draw()
{
	// 描画
	for (auto& shot : m_pShot)
	{
		shot->Draw();
	}
}

void ShotManager::CheckEnable()
{
	// ショットの存在を確認
	for (auto it = m_pShot.begin(); it != m_pShot.end();)
	{
		// エネミーの存在が消える場合
		if (!(*it)->IsEnable())
		{
			// メモリ解放
			(*it)->End();
			delete* it;

			// リストから要素を削除
			it = m_pShot.erase(it);
		}
		else
		{
			// 削除しない場合は次の要素へ進む
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
	// ショットの初期化
	m_pShot.push_back(new ShotNomal(startPos));
}
