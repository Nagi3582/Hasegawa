#ifndef _ENEMY_STATE_ESCAPE_H_
#define _ENEMY_STATE_ESCAPE_H_
#include "../EnemyStateBase.h"

class EnemyStateEscape :public EnemyStateBase
{
public:
	EnemyStateEscape();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;

};


#endif // !_ENEMY_STATE_ESCAPE_H_
