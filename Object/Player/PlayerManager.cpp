#include "PlayerManager.h"

#include "Player.h"

PlayerManager::PlayerManager()
{
	// ƒƒ‚ƒŠŠm•Û
	m_pPlayer.push_back(new Player());
}

PlayerManager::~PlayerManager()
{
	// ƒƒ‚ƒŠ‰ğ•ú
	for (auto& player : m_pPlayer)
	{
		delete player;
	}
}

void PlayerManager::Update()
{
	// XVˆ—
	for (auto& player : m_pPlayer)
	{
		player->Update();
	}
}

void PlayerManager::Draw()
{
	// •`‰æˆ—
	for (auto& player : m_pPlayer)
	{
		player->Draw();
	}
}

std::list<Player*>& PlayerManager::GetPlayerData()
{
	return m_pPlayer;
}
