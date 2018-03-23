#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_
#include "SceneBase.h"
#include"../../GameObject/Field/Field.h"
#include"../../World/World.h"
#include"../../GameObject/Light/PlayerLight.h"
#include"../../GameObject/Light/TitleLight/TitleLight.h"
#include"../../GameObject/Light/TitleLight/TitleLightPtr.h"
#include<vector>

class TitleScene :public SceneBase
{
public:
	TitleScene(ItemManager& item, SceneInfo& info);

	virtual void OnInitialize()override;
	virtual void NormalUpdate(float deltaTime)override;
	virtual void PauseUpdate(float deltaTime)override;
	virtual void OnDraw()const override;
	virtual void Shutdown()override;

private:
	using WorldPtr = std::shared_ptr<World>;

private:
	WorldPtr m_World;
	ItemManager* p_ItemManager;
	std::vector<TitleLightPtr>m_doorlights;

	mutable Renderer m_renderer;
};


#endif // !_TITLE_SCENE_H_
