#ifndef RESULT_SCENE_H_
#define RESULT_SCENE_H_
#include"SceneBase.h"
#include"../../GameObject/Field/Field.h"
#include"../../World/World.h"
#include"../../Utility/Renderer/ShaderName/ShaderName.h"
#include"../../GameObject/Light/ResultLight/ResultLight.h"
#include"../../GameObject/ResultObject/Score/Score.h"


class ResultScene :public SceneBase
{
public:
	ResultScene(ItemManager& item, SceneInfo& info);
	virtual void OnInitialize()override;
	virtual void NormalUpdate(float deltaTime)override;
	virtual void OnDraw()const override;
	virtual void Shutdown()override;
	// SceneBase ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void PauseUpdate(float deltaTime) override;

private:
	using WorldPtr = std::shared_ptr<World>;

private:
	WorldPtr m_World;
	ItemManager* p_ItemManager;
	ResultLight m_light;
	Score m_score;
	mutable Renderer m_renderer;
	mutable int lightID;

};

#endif // !RESULT_SCENE_H_