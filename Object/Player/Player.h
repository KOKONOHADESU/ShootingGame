#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Airframe.h"
#include "../../Util/Rect.h"

class Player final
{
public:
	Player();
	~Player();

	void Update();
	void Draw();

public:
	// 座標を渡す
	Vec2 GetPos()const;

	// 四角形用判定データ
	Rect GetCollData()const;

	// 発射する数
	int GetShootingNum()const;
private:
	// 入力
	void Input();
	// 画面範囲外処理
	void OutSide();
	// 判定用座標を更新する
	void CollRectUpdate();

private:
	// 画像ハンドル
	int m_hGraph;

	// 機体データ
	Airframe m_airframe;

	// 四角形判定用
	Rect m_collRect;

	// 発射する数
	int m_shootingNum;
};

