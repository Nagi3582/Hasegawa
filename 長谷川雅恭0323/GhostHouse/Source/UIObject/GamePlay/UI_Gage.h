#ifndef UI_GAGE_H_
#define UI_GAGE_H_

#include"../../UI/UITexture.h"
#include"../../GameObject/Item/ItemManager/ItemManager.h"
#include"../../GameObject/Light/LightColor.h"

struct SceneInfo;

class UI_Gage :public UITexture
{
public:
	UI_Gage(IWorld& world, const GSvector2& position, SceneInfo& info, ItemManager&item, LightColor color);

	void on_update(float deltaTime)override;
	void on_draw()const override;

private:
	ItemManager * p_item;
	LightColor m_color;
	SceneInfo& m_Info;
	float m_color_R;
	float m_color_G;
};

#endif // !UI_GAGE_H_
