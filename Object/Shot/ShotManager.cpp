#include "ShotManager.h"

#include "ShotNomal.h"
#include "ShotMissile.h"
#include "ShotRocket.h"

#include "../../Util/GraphicSprite.h"
#include "../../Util/ShotType.h"

#include <DxLib.h>
#include <string>

namespace
{
	// 画像ファイルパス
	// ノーマルショット
	const char* const kShotNomalPath = "Data/Image/Shot/shot.png";
	// ミサイルショット
	const char* const kShotMissilePath = "Data/Image/Shot/Shoot1.png";
	// ロケットショット
	const char* const kShotRocketPath = "Data/Image/Shot/Shoot2.png";

	// ノーマルショット
	constexpr int kShotNomalGrapicNumX = 1;
	constexpr int kShotNomalGrapicNumY = 1;

	// ミサイルショット
	constexpr int kShotMissileGrapicNumX = 3;
	constexpr int kShotMissileGrapicNumY = 1;

	// ロケットショット
	constexpr int kShotRocketGrapicNumX = 4;
	constexpr int kShotRocketGrapicNumY = 1;
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
	GraphicSprite::InitType(m_handle, ShotType::MAX);
	// 画像タイプ別画像分割数を指定
	GraphicSprite::InitGraphic(m_handle, ShotType::NORMAL, kShotNomalPath, kShotNomalGrapicNumX, kShotNomalGrapicNumY);
	GraphicSprite::InitGraphic(m_handle, ShotType::MISSILE, kShotMissilePath, kShotMissileGrapicNumX, kShotMissileGrapicNumY);
	GraphicSprite::InitGraphic(m_handle, ShotType::ROCKET, kShotRocketPath, kShotRocketGrapicNumX, kShotRocketGrapicNumY);
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

	for (int i = 0; i < static_cast<int>(ShotType::MAX); i++)
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

void ShotManager::CreateShotNormal(Vec2 startPos)
{
	// ノーマルショットの初期化
	m_pShot.push_back(new ShotNomal(startPos, m_handle[ShotType::NORMAL]));
}

void ShotManager::CreateShotMissile(Vec2 startPos)
{
	Vec2 pos = startPos;

	pos.x = startPos.x + 30.0f;

	// ミサイルショットの初期化
	m_pShot.push_back(new ShotMissile(pos, m_handle[ShotType::MISSILE]));

	pos.x = startPos.x - 30.0f;

	// ミサイルショットの初期化
	m_pShot.push_back(new ShotMissile(pos, m_handle[ShotType::MISSILE]));
}

void ShotManager::CreateShotRocket(Vec2 startPos)
{
	// ロケットショットの初期化
	m_pShot.push_back(new ShotRocket(startPos, m_handle[ShotType::ROCKET]));
}
