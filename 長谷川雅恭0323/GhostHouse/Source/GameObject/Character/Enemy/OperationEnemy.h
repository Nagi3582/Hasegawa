#ifndef _OPERATION_ENEMY_H_
#define _OPERATION_ENEMY_H_
#include "EnemyBase.h"

class OperationManager;

class OperationEnemy :public EnemyBase
{
public:
	OperationEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer, OperationManager& operationManager);

	virtual void SetState(CollideActor& player)override;

	virtual void OnCollide(CollideActor & other)override;

private:
	OperationManager* p_OperationManager;

};


#endif // !_OPERATION_ENEMY_H_
