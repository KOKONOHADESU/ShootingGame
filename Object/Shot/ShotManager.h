#pragma once

#include "ShotNomal.h"

#include "../../Util/Vec2.h"

#include <list>

class ShotManager final
{
public:
	ShotManager();
	~ShotManager();

	void Init();
	void End();
	void Update();
	void Draw();

private:

	// ���݂��m�F����
	void CheckEnable();

public:
	// �V���b�g�f�[�^
	std::list<ShotNomal*>& GetShotData();
	// �V���b�g�̏�����
	void SetInitShot(Vec2 startPos);
private:
	// �V���b�g
	std::list<ShotNomal*> m_pShot;
};

