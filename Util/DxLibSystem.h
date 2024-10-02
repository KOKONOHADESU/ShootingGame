#pragma once

namespace DxLibSystem
{
	// �E�B���h�E�ݒ�
#if _DEBUG
	constexpr int kWindowMode = true;
#else
	constexpr int kWindowMode = false;
#endif
	// �E�B���h�E�^�C�g��
	const char* const kTitleText = "ShootingGame";

	// ��ʃT�C�Y�ݒ�
	constexpr int kScreenWidth     = 1920;
	constexpr int kScreenHeight    = 1080;
	constexpr float	kScreenWidthF  = 1920.0f;
	constexpr float kScreenHeightF = 1080.0f;

	constexpr int kColorDepth   = 32;

	// �E�B���h�E�̃T�C�Y��ύX�ł��邩
	constexpr int kWindowSizeChange = true;

	// ���O���c�����ǂ���
	constexpr int kCreateLogText = false;
}