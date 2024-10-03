#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Item.h"
#include "../../Util/Rect.h"

#include<vector>

// アイテムの規定クラス
class ItemBase
{
public:
	ItemBase(Vec2 startPos, const std::vector<int>& handle);
	virtual ~ItemBase();

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
	// 位置を渡す
	Vec2 GetPos()const;

	// 判定用座標を渡す
	Rect GetCollData()const;

	// オブジェクトに当たった場合
	void IsHitObject();

	// 存在するかどうか
	bool IsEnable()const;

protected:
	// 判定更新処理
	void CollRectUpdate();

	// アニメーション用
	virtual void AnimUpdate();

private:
	// 画像アニメーション用
	int m_animGraphChangeFrameCount;
	int m_animGraphChangeNum;

protected:
	// 画像ハンドル
	std::vector<int> m_handle;

	// アイテムに生成に必要なデータ
	Item m_item;

	// 四角形判定用
	Rect m_collRect;

	// 四角形判定サイズ
	Rect m_collSize;

	// プレイヤーにあったたかどうか
	bool m_isHit;

	// オブジェクトが消滅するかどうか
	bool m_isEnable;

	// メンバ関数ポインタ
	void(ItemBase::* m_pFunc)();
};

