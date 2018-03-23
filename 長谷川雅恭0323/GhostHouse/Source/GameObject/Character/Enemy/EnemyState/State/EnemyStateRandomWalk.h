#ifndef _ENEMY_STATE_RANDOM_WALK_H_
#define _ENEMY_STATE_RANDOM_WALK_H_
#include "../EnemyStateBase.h"
#include <gslib.h>

class Renderer;

class EnemyStateRandomWalk :public EnemyStateBase
{
public:
	EnemyStateRandomWalk(Renderer& renderer);

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Collide(CollideActor& other)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;


private:
	void SetPoint();

	void AddEnemy();

private:
	GSvector3 m_CurrentPoint;
	GSvector3 m_NextPoint;
	bool m_HaveMusicBox;
	Renderer* p_Renderer;
	float m_SECounter;

};



#endif // !_ENEMY_STATE_RANDOM_WALK_H_
