
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

	// マップ
	Map* m_pMap;
	// プレイヤー
	Player* m_pPlayer;
	// エネミー管理
	EnemyManager* m_pEnemyManager;
	// ショット管理
	ShotManager* m_pShotManager;
};