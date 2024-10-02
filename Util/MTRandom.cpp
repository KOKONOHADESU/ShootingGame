#include "MTRandom.h"

MTRandom::MTRandom()
{
    // 乱数生成器を初期化
    std::random_device rand;
    // メルセンヌツイスタで乱数生成
    m_randGenerator = std::mt19937(rand());
}

int MTRandom::GetMTRand(int randMin, int randMax)
{
    // メルセンヌツイスタで乱数の範囲を設定
    std::uniform_int_distribution<> distrib(randMin, randMax);

    // 範囲でしたいした値をランダムで返す
    return static_cast<int>(distrib(m_randGenerator));
}