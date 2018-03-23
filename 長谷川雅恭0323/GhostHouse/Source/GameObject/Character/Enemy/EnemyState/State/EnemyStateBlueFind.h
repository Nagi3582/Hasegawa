#ifndef _ENEMY_STATE_BLUE_FIND_H_
#define _ENEMY_STATE_BLUE_FIND_H_
#include <gslib.h>
#include "../EnemyStateBase.h"

enum BlueFindState
{
	Idle,
	Move,
};

class EnemyStateBlueFind :public EnemyStateBase
{
public:
	EnemyStateBlueFind();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;

private:
	void Think();


private:
	int m_Rand;
	int m_Direction;
	int m_NextStateTime;
	BlueFindState m_State;
	float m_MissTimer;

};


#endif // !_ENEMY_STATE_BLUE_FIND_H_
