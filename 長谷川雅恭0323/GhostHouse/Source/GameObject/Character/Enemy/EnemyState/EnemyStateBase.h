#ifndef _ENEMY_STATE_BASE_H_
#define _ENEMY_STATE_BASE_H_
#include "EnemyStateName.h"

class CollideActor;
class ModelBase;
class EnemyStateManager;

class EnemyStateBase
{
public:
	EnemyStateBase();

	void SetUp(CollideActor& player, ModelBase& me, EnemyStateManager& manager);

	virtual void Initialize() {};
	virtual void Update(float deltaTime) {};
	virtual void Collide(CollideActor & other);

	virtual void Draw()const {};
	virtual void Shutdown() {};


protected:


protected:
	ModelBase* p_Me;
	CollideActor* p_Player;
	EnemyStateManager* p_Manager;



};

#endif // !_ENEMY_STATE_BASE_H_
