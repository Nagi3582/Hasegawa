#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "../ModelBase.h"
#include"../../Light/PlayerLight.h"
#include "PlayerManager.h"
#include "PlayerHandLight/PlayerHandLight.h"

class ItemManager;
struct SceneInfo;

class Player :public ModelBase
{
public:
	Player(IWorld & world, const GSvector3 position, Renderer&renderer, ItemManager& item, SceneInfo& info, bool is_operation = false);

	virtual void OnUpdate(float deltaTime)override;

	virtual void SubDraw(bool is_shadow, Renderer& renderer)const override;

	virtual void OnCollide(CollideActor& other)override;

	PlayerManager& get_manager();

protected:
	PlayerLight m_player_light;
	PlayerManager m_Manager;
	int m_AnmID;
	Renderer* p_Renderer;
	int m_MotionID;
	PlayerHandLight m_HandLight;

};

#endif // !_PLAYER_H_
