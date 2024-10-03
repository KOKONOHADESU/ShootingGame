#pragma once

#include <list>
#include <vector>

class EnemyBase;
// �G�l�~�[�̊Ǘ�
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Init();
	void End();
	void Update();
	void Draw();
public:

	// �G�l�~�[�f�[�^
	std::list<EnemyBase*>& GetEnemyData();

	// ���݂��`�F�b�N����
	void CheckEnable();

private:
	// �m�[�}���G�l�~�[�Ǘ�
	void NomalUpdate();
	// �m�[�}���G�l�~�[�X�|�[��
	void NomalSpawn();
private:

	// �G�l�~�[
	std::list<EnemyBase*> m_pEnemy;

	// �m�[�}���G�l�~�[�����p�t���[���J�E���g
	int m_normalEnemyFrameSpawnCount;

	// �摜�n���h��
	std::vector<std::vector<int>> m_handle;

	// �摜���S�n���h��
	std::vector<std::vector<int>> m_hDead;

};

