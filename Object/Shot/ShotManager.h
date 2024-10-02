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

	// 存在を確認する
	void CheckEnable();

public:
	// ショットデータ
	std::list<ShotBase*>& GetShotData();
	// ショットの初期化
	void SetInitShot(Vec2 startPos);
private:
	// ショット
	std::list<ShotBase*> m_pShot;
	
	// 画像ハンドル
	std::vector<std::vector<int>> m_handle;
};

