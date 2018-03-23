#ifndef _GAME_OVER_UI_MANAGER_H_
#define _GAME_OVER_UI_MANAGER_H_
#include "UIManagerBase.h"

struct SceneInfo;

class GameOverUIManager :public UIManagerBase
{
public:
	GameOverUIManager(SceneInfo& info);

	virtual void Initialize(IWorld& world, Renderer& renderer)override;
	virtual void OnUpdate(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Decision()override;

};


#endif // !_GAME_MANAGER_UI_H_
