#ifndef _GAME_PLAY_SCENE_H_
#define _GAME_PLAY_SCENE_H_
#include "SceneBase.h"
#include <memory>

#include "../../World/World.h"
#include "../../UIObject/GamePlay/PlaySceneUI.h"
#include "../../GameObject/Item/ItemManager/ItemManager.h"

class ItemManager;


class GamePlayScene :public SceneBase
{
public:
	GamePlayScene(ItemManager& item, SceneInfo& info);

	virtual void OnInitialize()override;
	virtual void OnUpdate(float deltaTime)override;
	virtual void NormalUpdate(float deltaTime)override;
	virtual void PauseUpdate(float deltaTime)override;
	virtual void OnDraw()const override;
	virtual void Shutdown()override;
	virtual void OnGameEnd()override;


private:
	void set_stage_name();

private:
	using WorldPtr = std::shared_ptr<World>;

private:
	WorldPtr p_World;
	mutable Renderer m_renderer;
	ItemManager* p_ItemManager;
	PlaySceneUI m_UI;
	int m_Stage;
	ItemManager m_PrevItem;
	std::unordered_map<int, TextureName>m_stageNames;

};


#endif // !_GAME_PLAY_SCENE_H_
