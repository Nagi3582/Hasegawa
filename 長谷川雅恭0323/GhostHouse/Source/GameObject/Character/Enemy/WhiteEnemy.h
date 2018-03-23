#ifndef _WHITE_ENEMY_H_
#define _WHITE_ENEMY_H_
#include "EnemyBase.h"

class WhiteEnemy :public EnemyBase
{
public:
	WhiteEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer);

	virtual void SetState(CollideActor& player)override;

};


#endif // !_WHITE_ENEMY_H_
