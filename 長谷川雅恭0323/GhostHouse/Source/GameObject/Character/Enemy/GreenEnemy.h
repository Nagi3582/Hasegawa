#ifndef _GREEN_ENEMY_H_
#define _GREEN_ENEMY_H_
#include "EnemyBase.h"

class GreenEnemy :public EnemyBase
{
public:
	GreenEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer);

	virtual void SetState(CollideActor& player)override;

};



#endif // !_GREEN_ENEMY_H_
