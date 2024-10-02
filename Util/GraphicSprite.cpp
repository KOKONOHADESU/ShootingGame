#include "GraphicSprite.h"

#include <DxLib.h>

void GraphicSprite::InitType(std::vector<std::vector<int>>& handle, int shotTypeNum)
{
	// ショットの種類分の配列を生成
	handle.resize(shotTypeNum);
}

void GraphicSprite::InitGraphic(std::vector<std::vector<int>>& handle, int shotType, const char* path, int graphXNum, int graphYNum)
{
	// 画像分割数
	const int allGraphNum = graphXNum * graphYNum;

	// 画像分割しない場合
	if (allGraphNum == 1)
	{
		handle[shotType].push_back(LoadGraph(path));
	}
	else
	{
		// 画像サイズ用変数
		float x = 0.0f;
		float y = 0.0f;

		// 画像サイズを知る為に読み込み
		const int graphhandle = LoadGraph(path);

		// 画像分割数のメモリ確保
		int* arrayHandle = new int[allGraphNum];

		// 画像サイズを受け取る
		GetGraphSizeF(graphhandle, &x, &y);

		// 画像を分割する
		LoadDivGraphF(
			path,
			allGraphNum,
			graphXNum, graphYNum,
			x / graphXNum, y / graphYNum,
			arrayHandle);

		// 画像分割したハンドルを割り当てる
		for (int i = 0; i < allGraphNum; i++)
		{
			handle[shotType].push_back(arrayHandle[i]);
		}

		// メモリの解放
		delete[] arrayHandle;
		DeleteGraph(graphhandle);
	}
}
