#ifndef _ENEMY_STATE_DISCOVERY_H_
#define _ENEMY_STATE_DISCOVERY_H_
#include "../EnemyStateBase.h"

class EnemyStateDiscovery :public EnemyStateBase
{
public:
	EnemyStateDiscovery(float attackDistance = 15.0f, float maxSpeed = 0.4f);

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;


private:
	const float MAX_SPEED;
	const float ATTACK_DISTANCE;

	float m_MissTimer;

};


#endif // !_ENEMY_STATE_DISCOVERY_H_
