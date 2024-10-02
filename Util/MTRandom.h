#pragma once

#include "SingletonBase.h"

#include <random>

// �����Z���k�E�c�C�X�^�g�p����
class MTRandom : public SingletonBase<MTRandom>
{
public:
	// SingletonBase�N���X�̃A�N�Z�X��������
	friend class SingletonBase<MTRandom>;

	~MTRandom() {};
private:
	MTRandom();
public:
	/// <summary>
	/// �����Z���k�E�c�C�X�^���g�p���������̐��� 
	/// </summary>
	/// <param name="randMin">�ŏ���</param>
	/// <param name="randMax">�ő吔</param>
	/// <returns></returns>
	int GetMTRand(int randMin, int randMax);
private:
	// ����������
	std::mt19937 m_randGenerator;
};