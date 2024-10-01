#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Airframe.h"
#include "../../Util/Rect.h"

namespace
{
	// 死亡演出用画像の数
	constexpr int kExplosionGraphAllNum = 7;
}

class EnemyBase
{
public:
	EnemyBase(Airframe airframe);
	virtual ~EnemyBase();
protected:
	virtual void Init(const char* graphPath);
public:
	virtual void End();
	virtual void Update();
	virtual void Draw();

public:
	// 生成後
	virtual void StartUpdate() = 0;
	// バトル状態
	virtual void BattleUpdate() = 0;
	// 消滅状態
	virtual void DeadUpdate() = 0;

public:
	// 判定用座標を渡す
	Rect GetCollData()const;

	// ダメージを受け取る
	void SetDamage(int damage);

	// 存在するかどうかを確認する
	bool IsEnable()const;

protected:
	// 判定用座標を更新する
	void CollRectUpdate(Rect size);
	// 体力を確認
	void CheckHitPoint();
	// 位置を確認する
	void CheckEnablePos();
	// 死亡演出用更新処理
	void ExplosionUpdate();
protected:
	// 画像ハンドル
	int m_hGraph;

	// 死亡演出用ハンドル
	int m_hExplosion[kExplosionGraphAllNum];

	// 死亡演出画像の切り替えフレームカウント
	int m_explosionGraphChangeFrameCount;

	// 死亡演出画像の切り替え数
	int m_explosionGraphChangeNum;

	// 機体データ
	Airframe m_airframe;

	// 四角形判定用
	Rect m_collRect;

	// 死んだかどうか
	bool m_isDead;

	// オブジェクトが消滅するかどうか
	bool m_isEnable;

	// メンバ関数ポインタ
	void(EnemyBase::* m_pFunc)();
};

