#ifndef _ENEMY_STATE_GREEN_FIND_H_
#define _ENEMY_STATE_GREEN_FIND_H_
#include "../EnemyStateBase.h"

enum class GreenEnemyState
{
	Idle,
	Dive,
};

class EnemyStateGreenFind :public EnemyStateBase
{
public:
	EnemyStateGreenFind();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;


private:
	GreenEnemyState m_State;
	float m_MissTimer;


};


#endif // !_ENEMY_STATE_GREEN_FIND_H_
