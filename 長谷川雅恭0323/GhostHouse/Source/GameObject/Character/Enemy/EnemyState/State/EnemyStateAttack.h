#ifndef _ENEMY_STATE_ATTACK_H_
#define _ENEMY_STATE_ATTACK_H_
#include "../EnemyStateBase.h"
#include "../../../../../Actor/CollideActorPtr.h"

enum class LightColor;

class EnemyStateAttack :public EnemyStateBase
{
public:
	EnemyStateAttack(float attackTime, bool redAttack = false);

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;



private:
	float m_AttackTime;
	bool m_RedAttack;
	CollideActorPtr p_Attack;

};


#endif // !_ENEMY_STATE_ATTACK_H_
