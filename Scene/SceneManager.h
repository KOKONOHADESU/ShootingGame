
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

	// マップ
	Map* m_pMap;
	// プレイヤー管理
	PlayerManager* m_pPlayerManager;
	// エネミー管理
	EnemyManager* m_pEnemyManager;
	// ショット管理
	ShotManager* m_pShotManager;
	// アイテム管理
	ItemManager* m_pItemManager;
};