#include "../../Util/Vec2.h"
#include "../../Util/Rect.h"

#include <vector>

class Map final
{
private:
	enum BGType
	{
		ALL,
		SIDELEFT,
		SIDERIGHT,
		MID,

		MAX
	};
public:
	Map();
	~Map();

	void Update();
	void Draw();
private:
	void Init();
	void Scroll(BGType type , float speed);
private:
	// �w�i�摜�n���h��
	int m_hBg[BGType::MAX];

	// �w�i�摜�T�C�Y
	Vec2 m_bgSize[BGType::MAX];

	// �摜�ʒu�̒���
	std::vector<Rect> m_graphPos[BGType::MAX];
	
};