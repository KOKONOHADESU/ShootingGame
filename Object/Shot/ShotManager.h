#pragma once

#include "ShotNomal.h"

#include "../../Util/Vec2.h"

#include <list>

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
	std::list<ShotNomal*>& GetShotData();
	// ショットの初期化
	void SetInitShot(Vec2 startPos);
private:
	// ショット
	std::list<ShotNomal*> m_pShot;
};

