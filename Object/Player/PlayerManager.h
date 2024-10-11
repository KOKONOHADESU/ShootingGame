#pragma once

#include <list>

class Player;

// プレイヤー管理クラス
class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	void Update();
	void Draw();

public:
	// プレイヤーデータ
	std::list<Player*>& GetPlayerData();

private:
	// プレイヤー
	std::list<Player*> m_pPlayer;
};

