#ifndef _OPERATION_SCENE_H_
#define _OPERATION_SCENE_H_
#include "SceneBase.h"
#include "../../GameObject/Field/Field.h"
#include "../../World/World.h"

#include "../../UIObject/GamePlay/PlaySceneUI.h"
#include "../../UIObject/Operation/OperationUI.h"
#include "../../UIObject/Operation/OperationManager.h"

#include <memory>

class OperationScene :public SceneBase
{
public:
	OperationScene(ItemManager& item, SceneInfo& info);

	virtual void OnInitialize()override;
	virtual void OnUpdate(float deltaTime)override;
	virtual void NormalUpdate(float deltaTime)override;
	virtual void PauseUpdate(float deltaTime)override;
	virtual void OnDraw()const override;
	virtual void Shutdown()override;

private:
	using WorldPtr = std::shared_ptr<World>;

private:
	WorldPtr p_World;
	mutable Renderer m_renderer;
	ItemManager* p_ItemManager;
	PlaySceneUI m_UI;
	OperationManager m_OperationManager;
	OperationUI m_Operation;
};

#endif // !_TEST_PLAY_SCENE_H_