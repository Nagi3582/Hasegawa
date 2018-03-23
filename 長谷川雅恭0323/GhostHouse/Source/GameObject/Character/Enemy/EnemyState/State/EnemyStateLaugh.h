#ifndef _ENEMY_STATE_LAUGH_H_
#define _ENEMY_STATE_LAUGH_H_
#include "../EnemyStateBase.h"

class EnemyStateLaugh :public EnemyStateBase
{
public:
	EnemyStateLaugh();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;

};



#endif // !_ENEMY_STATE_LAUGH_H_
