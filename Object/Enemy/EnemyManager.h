#pragma once

#include <list>

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

};

