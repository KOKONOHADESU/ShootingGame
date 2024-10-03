#include "EnemyNormal.h"

namespace
{
	// 移動速度
	constexpr float kSpeed = 5.0f;

	// 体力
	constexpr int kHitPointMax = 1;

	// 判定の大きさ
	constexpr float kLeftXSize  = 35.0f;
	constexpr float kLeftYSize  = 35.0f;
	constexpr float kRightXSize = 35.0f;
	constexpr float kRightYSize = 35.0f;
}

EnemyNormal::EnemyNormal(Airframe airframe, const std::vector<int>& handle, const std::vector<int>& hDead):
	EnemyBase::EnemyBase(airframe, handle, hDead)
{
	// 体力の初期化
	m_airframe.hitPoint = kHitPointMax;

	// 判定用
	Rect collSize{ kLeftXSize ,kLeftYSize ,kRightXSize ,kRightYSize };
	CollRectUpdate(collSize);
}

EnemyNormal::~EnemyNormal()
{
}

void EnemyNormal::StartUpdate()
{
	// 関数ポインタの変更
	m_pFunc = &EnemyBase::BattleUpdate;	
}

void EnemyNormal::BattleUpdate()
{
	// 位置更新
	m_airframe.pos.y += kSpeed;

	// 判定用
	Rect collSize{ kLeftXSize ,kLeftYSize ,kRightXSize ,kRightYSize };
	CollRectUpdate(collSize);

	// 体力の確認
	EnemyBase::CheckHitPoint();

	// 位置の確認
	CheckEnablePos();

	// 死んだかどうか
	if (m_isDead)
	{
		// 関数ポインタの変更
		m_pFunc = &EnemyBase::DeadUpdate;
	}
}

void EnemyNormal::DeadUpdate()
{
	// 死亡演出の更新処理
	ExplosionUpdate();
}
