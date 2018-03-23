//敵が巡回させるクラス
#ifndef _ENEMY_STATE_IDLE_H_
#define _ENEMY_STATE_IDLE_H_
#include <gslib.h>
#include "../EnemyStateBase.h"

class EnemyStateIdle :public EnemyStateBase
{
public:
	EnemyStateIdle(float speedMax = 0.05f);

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;


private:
	GSvector3 m_Direction;
	const float MAX_SPEED;
	float m_SECounter;	//SEが鳴るまでの時間をカウント

};


#endif // !_ENEMY_STATE_IDLE_H_
