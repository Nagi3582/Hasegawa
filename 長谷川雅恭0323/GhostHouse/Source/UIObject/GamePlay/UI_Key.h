#ifndef UI_KEY_H_
#define UI_KEY_H_

#include"../../UI/UITexture.h"
#include"../../GameObject/Item/ItemManager/ItemManager.h"
#include"../../GameObject/Light/LightColor.h"

struct SceneInfo;

class UI_Key :public UITexture
{
public:
	UI_Key(IWorld& world, const GSvector2& position, SceneInfo& info);

	void on_update(float deltaTime)override;
	void on_draw()const override;

private:
	SceneInfo& m_Info;
};

#endif // !UI_GAGE_H_
