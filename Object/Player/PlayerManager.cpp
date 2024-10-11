#include "PlayerManager.h"

#include "Player.h"

PlayerManager::PlayerManager()
{
	// �������m��
	m_pPlayer.push_back(new Player());
}

PlayerManager::~PlayerManager()
{
	// ���������
	for (auto& player : m_pPlayer)
	{
		delete player;
	}
}

void PlayerManager::Update()
{
	// �X�V����
	for (auto& player : m_pPlayer)
	{
		player->Update();
	}
}

void PlayerManager::Draw()
{
	// �`�揈��
	for (auto& player : m_pPlayer)
	{
		player->Draw();
	}
}

std::list<Player*>& PlayerManager::GetPlayerData()
{
	return m_pPlayer;
}
