#pragma once

#include "../../Util/Vec2.h"

#include <list>
#include <vector>

class ShotBase;
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
	std::list<ShotBase*>& GetShotData();
	// �V���b�g�̏�����
	void SetInitShot(Vec2 startPos);
private:
	// �V���b�g
	std::list<ShotBase*> m_pShot;
	
	// �摜�n���h��
	std::vector<std::vector<int>> m_handle;
};

