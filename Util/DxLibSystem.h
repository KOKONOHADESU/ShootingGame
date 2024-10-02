#pragma once

namespace DxLibSystem
{
	// ウィンドウ設定
#if _DEBUG
	constexpr int kWindowMode = true;
#else
	constexpr int kWindowMode = false;
#endif
	// ウィンドウタイトル
	const char* const kTitleText = "ShootingGame";

	// 画面サイズ設定
	constexpr int kScreenWidth     = 1920;
	constexpr int kScreenHeight    = 1080;
	constexpr float	kScreenWidthF  = 1920.0f;
	constexpr float kScreenHeightF = 1080.0f;

	constexpr int kColorDepth   = 32;

	// ウィンドウのサイズを変更できるか
	constexpr int kWindowSizeChange = true;

	// ログを残すかどうか
	constexpr int kCreateLogText = false;
}