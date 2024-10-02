#include "GraphicSprite.h"

#include <DxLib.h>

void GraphicSprite::InitType(std::vector<std::vector<int>>& handle, int shotTypeNum)
{
	// �V���b�g�̎�ޕ��̔z��𐶐�
	handle.resize(shotTypeNum);
}

void GraphicSprite::InitGraphic(std::vector<std::vector<int>>& handle, int shotType, const char* path, int graphXNum, int graphYNum)
{
	// �摜������
	const int allGraphNum = graphXNum * graphYNum;

	// �摜�������Ȃ��ꍇ
	if (allGraphNum == 1)
	{
		handle[shotType].push_back(LoadGraph(path));
	}
	else
	{
		// �摜�T�C�Y�p�ϐ�
		float x = 0.0f;
		float y = 0.0f;

		// �摜�T�C�Y��m��ׂɓǂݍ���
		const int graphhandle = LoadGraph(path);

		// �摜�������̃������m��
		int* arrayHandle = new int[allGraphNum];

		// �摜�T�C�Y���󂯎��
		GetGraphSizeF(graphhandle, &x, &y);

		// �摜�𕪊�����
		LoadDivGraphF(
			path,
			allGraphNum,
			graphXNum, graphYNum,
			x / graphXNum, y / graphYNum,
			arrayHandle);

		// �摜���������n���h�������蓖�Ă�
		for (int i = 0; i < allGraphNum; i++)
		{
			handle[shotType].push_back(arrayHandle[i]);
		}

		// �������̉��
		delete[] arrayHandle;
		DeleteGraph(graphhandle);
	}
}
