#pragma once

#include <vector>

namespace GraphicSprite
{
	// 画像タイプ分の配列を生成
	void InitType(std::vector<std::vector<int>>& handle, int shotTypeNum);
	// 画像ハンドルに読み込む
	void InitGraphic(std::vector<std::vector<int>>& handle, int shotType, const char* path, int graphXNum, int graphYNum);
};

