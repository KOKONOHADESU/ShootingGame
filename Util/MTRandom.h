#pragma once

#include "SingletonBase.h"

#include <random>

// メルセンヌ・ツイスタ使用乱数
class MTRandom : public SingletonBase<MTRandom>
{
public:
	// SingletonBaseクラスのアクセスを許可する
	friend class SingletonBase<MTRandom>;

	~MTRandom() {};
private:
	MTRandom();
public:
	/// <summary>
	/// メルセンヌ・ツイスタを使用した乱数の生成 
	/// </summary>
	/// <param name="randMin">最小数</param>
	/// <param name="randMax">最大数</param>
	/// <returns></returns>
	int GetMTRand(int randMin, int randMax);
private:
	// 乱数生成器
	std::mt19937 m_randGenerator;
};