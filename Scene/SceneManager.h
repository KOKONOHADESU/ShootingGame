
class Map;
class PlayerManager;
class EnemyManager;
class ShotManager;
class ItemManager;
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
	// �v���C���[�Ǘ�
	PlayerManager* m_pPlayerManager;
	// �G�l�~�[�Ǘ�
	EnemyManager* m_pEnemyManager;
	// �V���b�g�Ǘ�
	ShotManager* m_pShotManager;
	// �A�C�e���Ǘ�
	ItemManager* m_pItemManager;
};