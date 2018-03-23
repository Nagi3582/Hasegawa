//敵がライトに当てられて動けなくなるクラス
#ifndef _ENEMY_STATE_STOP_H_
#define _ENEMY_STATE_STOP_H_
#include "../EnemyStateBase.h"

class EnemyStateStop :public EnemyStateBase
{
public:
	EnemyStateStop();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;

};



#endif // !_ENEMY_STATE_STOP_H_
