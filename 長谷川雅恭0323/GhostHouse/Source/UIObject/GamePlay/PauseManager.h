#ifndef _PAUSE_MANAGER_H__
#define _PAUSE_MANAGER_H_
#include "UIManagerBase.h"

class IWorld;
class Renderer;
struct SceneInfo;

class PauseManager :public UIManagerBase
{
public:
	PauseManager(SceneInfo& info);

	virtual void Decision()override;
	virtual void Initialize(IWorld& world, Renderer& renderer)override;
	virtual void OnUpdate(float deltaTime)override;
	virtual void Draw()const override;

};

#endif // !_PAUSE_MANAGER_H_

