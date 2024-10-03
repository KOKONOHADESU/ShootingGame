#pragma once

#include <list>
#include <vector>

class EnemyBase;
// エネミーの管理
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

	// エネミーデータ
	std::list<EnemyBase*>& GetEnemyData();

	// 存在をチェックする
	void CheckEnable();

private:
	// ノーマルエネミー管理
	void NomalUpdate();
	// ノーマルエネミースポーン
	void NomalSpawn();
private:

	// エネミー
	std::list<EnemyBase*> m_pEnemy;

	// ノーマルエネミー生成用フレームカウント
	int m_normalEnemyFrameSpawnCount;

	// 画像ハンドル
	std::vector<std::vector<int>> m_handle;

	// 画像死亡ハンドル
	std::vector<std::vector<int>> m_hDead;

};

