#ifndef _ENEMY_ATTACK_H_
#define _ENEMY_ATTACK_H_
#include "../../../../Actor/CollideActor.h"

class ModelBase;

class EnemyAttack :public CollideActor
{
public:
	EnemyAttack(IWorld& world, ModelBase& enemy, float deadTime, bool isFront, float radius = 3.0f, const std::string& name = "EnemyAttack");

	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;
	virtual void OnCollide(CollideActor& other)override;

	bool IsHit()const;


private:
	ModelBase* p_Enemy;
	float m_DeadTime;
	float m_Counter;
	bool m_IsFront;
	bool m_IsHit;

};


#endif // !_ENEMY_ATTACK_H_
