#ifndef _PLAYER_STATE_BASE_H_
#define _PLAYER_STATE_BASE_H_
#include <gslib.h>
#include "PlayerState.h"

class CollideActor;

class PlayerManager;
class ItemManager;
class IWorld;
class Renderer;
class OperationManager;
struct SceneInfo;

class PlayerStateBase
{
public:
	PlayerStateBase();
	PlayerStateBase(Renderer& renderer);

	virtual ~PlayerStateBase() {}

	void SetUp(IWorld& world, PlayerManager& manager, ItemManager& item, SceneInfo& info);
	virtual void Initialize() {};
	virtual void Update(float deltaTime) {};
	void Collide(CollideActor& other);

	virtual void Draw()const {};

	void Shutdown();


protected:
	virtual void OnCollide(CollideActor& other) {};
	virtual void OnShutdown() {};

private:
	void HitEnemy();

protected:
	IWorld* p_World;
	PlayerManager* p_Manager;
	ItemManager* p_ItemManager;
	SceneInfo* p_Info;

	Renderer* p_renderer;
	bool m_IsHitEnemyAttack;


};

#endif // !_PLAYER_STATE_BASE_H_