#ifndef _UI_PLAY_H_
#define _UI_PLAY_H_
#include "../../UI/UITexture.h"
#include"../../GameObject/Item/ItemManager/ItemManager.h"

struct SceneInfo;

class UIPlay :public UITexture
{
public:
	UIPlay(IWorld&world,SceneInfo& info, ItemManager& itemManager);


	virtual void on_update(float deltaTime);
	virtual void on_draw()const;

private:
	void Window_Draw()const;
	void Battery_Draw()const;
	void Flashlight_Draw()const;

	void Number_Draw()const;
	void Kakeru_Draw()const;


private:
	SceneInfo& m_Info;

	ItemManager* p_item;
};


#endif // !_PAUSE_H_
