#include "ItemCoin.h"

#include "../../Util/DxLibSystem.h"

namespace
{
	// �T�C�Y
	constexpr float kSize = 2.0f;

	// �p�x
	constexpr float kRota = 0.0f;

	// ����̑傫��
	constexpr float kLeftXSize  = 15.0f;
	constexpr float kLeftYSize  = 15.0f;
	constexpr float kRightXSize = 15.0f;
	constexpr float kRightYSize = 15.0f;
}

ItemCoin::ItemCoin(Vec2 startPos, const std::vector<int>& handle):
	ItemBase::ItemBase(startPos,handle)
{
	m_item.size = kSize;
	m_item.rota = kRota;

	// ����p�T�C�Y
	m_collSize.left.x  = kLeftXSize;
	m_collSize.left.y  = kLeftYSize;
	m_collSize.right.x = kRightXSize;
	m_collSize.right.y = kRightYSize;
}

ItemCoin::~ItemCoin()
{

}

void ItemCoin::StartUpdate()
{
	// �֐��|�C���^�̕ύX
	m_pFunc = &ItemBase::BattleUpdate;
}

void ItemCoin::BattleUpdate()
{
	// ����X�V
	CollRectUpdate();

	// �A�j���[�V����
	AnimUpdate();

	// �I�u�W�F�g�ɓ��������ꍇ
	if (m_isHit)
	{		
		// �֐��|�C���^�̕ύX
		m_pFunc = &ItemBase::DeadUpdate;
	}
}

void ItemCoin::DeadUpdate()
{
	Vec2 components{ 0.0f,0.0f };
	Vec2 direction{ 0.0f,0.0f };
	const Vec2 endPos{DxLibSystem::kScreenWidthF / 2.0f , DxLibSystem::kScreenHeightF };

	//�����v�Z
	components.x = endPos.x - m_item.pos.x;
	components.y = endPos.y - m_item.pos.y;

	//�傫���v�Z
	const float magnitude = sqrtf(components.x * components.x + components.y * components.y);

	//�����v�Z�i���K���j
	direction.x = components.x / magnitude;
	direction.y = components.y / magnitude;

	//�ړ���̈ʒu���v�Z
	m_item.pos.x += direction.x * 50.0f;
	m_item.pos.y += direction.y * 50.0f;

	// ����̈ʒu�ɋ߂Â��ƃI�u�W�F�N�g������
	if (magnitude < 100.0f)
	{
		m_isEnable = false;
	}
}
