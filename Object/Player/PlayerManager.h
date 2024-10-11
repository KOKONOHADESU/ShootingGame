#pragma once

#include <list>

class Player;

// �v���C���[�Ǘ��N���X
class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	void Update();
	void Draw();

public:
	// �v���C���[�f�[�^
	std::list<Player*>& GetPlayerData();

private:
	// �v���C���[
	std::list<Player*> m_pPlayer;
};

