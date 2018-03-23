#ifndef _ENEMY_STATE_MISS_H_
#define _ENEMY_STATE_MISS_H_
#include "../EnemyStateBase.h"

class EnemyStateMiss :public EnemyStateBase
{
public:
	EnemyStateMiss();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;

};


#endif // !_ENEMY_STATE_MISS_H_
