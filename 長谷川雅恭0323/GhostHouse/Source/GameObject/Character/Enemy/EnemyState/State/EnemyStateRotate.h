#ifndef _ENEMY_STATE_ROTATE_H_
#define _ENEMY_STATE_ROTATE_H_
#include <gslib.h>
#include "../EnemyStateBase.h"

class EnemyStateRotate :public EnemyStateBase
{
public:
	EnemyStateRotate(float distance, float rotateSpeed, float discovery = 30.0f);

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;


private:
	const float DISTANCE_MAX;			//離れる距離最大値
	const float DISCOVERY_DISTANCE;

	GSvector3 m_BasePosition;			//回転する中心位置
	float m_Angle;						//角度
	float m_Distance;					//中心から離れる距離
	float m_RotateSpeed;				//回転速度

	float m_SECounter;					//SEが鳴るまでの時間をカウント

};


#endif // !_ENEMY_STATE_ROTATE_H_
