#include "ShotManager.h"

#include "ShotNomal.h"
#include "ShotMissile.h"

#include <DxLib.h>
#include <string>

namespace
{
	const char* const kShotNomalpath = "Data/Image/Shot/shot.png";

	const char* const kShotMissilepath = "Data/Image/Player/Shoot/Shoot1.png";

	// ファイルパス
	std::vector<std::string>kGraphFilePath =
	{
		"Data/Image/Shot/shot.png",			// ショット
		"Data/Image/Player/Shoot/Shoot1.png"// ミサイル
	};
}

ShotManager::ShotManager()
{
}

ShotManager::~ShotManager()
{
}

void ShotManager::Init()
{
	// 画像タイプを指定
	InitType(m_handle, 2);
	// 画像タイプ別画像分割数を指定
	InitGraphic(m_handle, 0, kShotNomalpath, 1, 1);
	InitGraphic(m_handle, 1, kShotMissilepath, 3, 1);
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

	for (int i = 0; i < static_cast<int>(kGraphFilePath.size()); i++)
	{
		for (int j = 0; j < m_handle[i].size(); j++)
		{
			DeleteGraph(m_handle[i][j]);
		}
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

void ShotManager::InitType(std::vector<std::vector<int>>& handle, int shotTypeNum)
{
	// ショットの種類分の配列を生成
	handle.resize(shotTypeNum);
}

void ShotManager::InitGraphic(std::vector<std::vector<int>>& handle, int shotType, const char* path, int graphXNum, int graphYNum)
{
	if (graphXNum * graphYNum == 1)
	{
		handle[shotType].push_back(LoadGraph(path));
	}
	else
	{
		float x = 0.0f;
		float y = 0.0f;
	//	GetGraphSizeF(handle[shotType], &x, &y)
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

std::list<ShotBase*>& ShotManager::GetShotData()
{
	return m_pShot;
}

void ShotManager::SetInitShot(Vec2 startPos)
{
	// ショットの初期化
	m_pShot.push_back(new ShotNomal(startPos, m_handle[0]));
}
