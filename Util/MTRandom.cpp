#include "MTRandom.h"

MTRandom::MTRandom()
{
    // �����������������
    std::random_device rand;
    // �����Z���k�c�C�X�^�ŗ�������
    m_randGenerator = std::mt19937(rand());
}

int MTRandom::GetMTRand(int randMin, int randMax)
{
    // �����Z���k�c�C�X�^�ŗ����͈̔͂�ݒ�
    std::uniform_int_distribution<> distrib(randMin, randMax);

    // �͈͂ł����������l�������_���ŕԂ�
    return static_cast<int>(distrib(m_randGenerator));
}