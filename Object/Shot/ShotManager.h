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
	// �摜�^�C�v���̔z��𐶐�
	void InitType(std::vector<std::vector<int>>& handle,int shotTypeNum);
	// �摜�n���h���ɓǂݍ���
	void InitGraphic(std::vector<std::vector<int>>& handle, int shotType, const char* path, int graphXNum, int graphYNum);

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

