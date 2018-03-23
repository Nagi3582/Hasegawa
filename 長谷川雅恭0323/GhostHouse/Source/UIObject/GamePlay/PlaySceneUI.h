//PlayScene‚ÌUI‚ð‚Ü‚Æ‚ß‚½ƒNƒ‰ƒX
#ifndef _PLAY_SCENE_UI_H_
#define _PLAY_SCENE_UI_H_
#include "GameOverUIManager.h"
#include "PauseManager.h"
#include "UIPlayManager.h"

class ItemManager;

class PlaySceneUI
{
public:
	PlaySceneUI(SceneInfo& info, ItemManager& item);

	void Initialize(IWorld& world, Renderer& renderer);
	void NormalUpdate(float deltaTime);
	void PauseUpdate(float deltaTime);
	void Draw()const;


private:
	GameOverUIManager m_GameOver;
	PauseManager m_Pause;
	UIPlayManager m_UIPlayManager;
	SceneInfo& m_Info;

};


#endif // !_PLAY_SCENE_UI_H_

