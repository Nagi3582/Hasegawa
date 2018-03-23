#ifndef _BLUE_ENEMY_H_
#define _BLUE_ENEMY_H_
#include "EnemyBase.h"

class BlueEnemy :public EnemyBase
{
public:
	BlueEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer);

	virtual void SetState(CollideActor& player)override;


};


#endif // !_BLUE_ENEMY_H_
