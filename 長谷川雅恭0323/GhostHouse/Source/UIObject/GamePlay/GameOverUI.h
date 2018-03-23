#ifndef _GAME_OVER_UI_H_
#define _GAME_OVER_UI_H_
#include "../../UI/UITexture.h"

struct SceneInfo;

class GameOverUI :public UITexture
{
public:
	GameOverUI(IWorld&world,SceneInfo& info);


	virtual void on_update(float deltaTime);
	virtual void on_draw()const;


private:
	SceneInfo& m_Info;

};



#endif // !_GAME_OVER_UI_H_
