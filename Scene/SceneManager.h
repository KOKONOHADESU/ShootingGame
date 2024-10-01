
class Map;
class Player;
class EnemyManager;
class ShotManager;
class SceneManager final
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void End();
	void Update();
	void Draw();
private:

	// �}�b�v
	Map* m_pMap;
	// �v���C���[
	Player* m_pPlayer;
	// �G�l�~�[�Ǘ�
	EnemyManager* m_pEnemyManager;
	// �V���b�g�Ǘ�
	ShotManager* m_pShotManager;
};