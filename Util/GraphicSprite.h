#pragma once

#include <vector>

namespace GraphicSprite
{
	// �摜�^�C�v���̔z��𐶐�
	void InitType(std::vector<std::vector<int>>& handle, int shotTypeNum);
	// �摜�n���h���ɓǂݍ���
	void InitGraphic(std::vector<std::vector<int>>& handle, int shotType, const char* path, int graphXNum, int graphYNum);
};

