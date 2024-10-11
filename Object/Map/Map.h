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
	// 背景画像ハンドル
	int m_hBg[BGType::MAX];

	// 背景画像サイズ
	Vec2 m_bgSize[BGType::MAX];

	// 画像位置の調整
	std::vector<Rect> m_graphPos[BGType::MAX];
	
};