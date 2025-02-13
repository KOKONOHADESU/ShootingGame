#include "PlayerManager.h"

#include "Player.h"

PlayerManager::PlayerManager()
{
	// メモリ確保
	m_pPlayer.push_back(new Player());
}

PlayerManager::~PlayerManager()
{
	// メモリ解放
	for (auto& player : m_pPlayer)
	{
		delete player;
	}
}

void PlayerManager::Update()
{
	// 更新処理
	for (auto& player : m_pPlayer)
	{
		player->Update();
	}
}

void PlayerManager::Draw()
{
	// 描画処理
	for (auto& player : m_pPlayer)
	{
		player->Draw();
	}
}

std::list<Player*>& PlayerManager::GetPlayerData()
{
	return m_pPlayer;
}
