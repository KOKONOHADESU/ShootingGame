#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Rect.h"
#include "../../Util/Bullet.h"

#include <vector>

class ShotBase
{
public:
	ShotBase(Vec2 startPos ,std::vector<int> handle);
	virtual~ShotBase();

	virtual void End();
	virtual void Update() = 0;
	virtual void Draw();

public:
	// 位置を渡す
	Vec2 GetPos()const;

	// 判定用座標を渡す
	Rect GetCollData()const;

	// 存在するかどうか
	bool IsEnable()const;

	// 攻撃力
	int GetDamage();

	// 当たったかを確認する
	void SetCheckHit();

	// 存在を消す
	void IsEnd();

protected:
	// 耐久力の確認
	void CheckHitPoint();

	// 判定用座標を更新する
	void CollRectUpdate();

	// 位置を確認する
	void CheckEnablePos();

protected:
	// 画像ハンドル
	std::vector<int> m_handle;

	// 画像再生用画像の数
	int m_graphNum;

	// 弾データ
	Bullet m_bullet;

	// 四角形判定用
	Rect m_collRect;

	// 四角形判定サイズ
	Rect m_collSize;

	// オブジェクトが消滅するかどうか
	bool m_isEnable;
};

