#ifndef _RED_ENEMY_H_
#define _RED_ENEMY_H_
#include "EnemyBase.h"

class RedEnemy :public EnemyBase
{
public:
	RedEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer);

	virtual void SetState(CollideActor& player)override;

};


#endif // !_RED_ENEMY_H_
