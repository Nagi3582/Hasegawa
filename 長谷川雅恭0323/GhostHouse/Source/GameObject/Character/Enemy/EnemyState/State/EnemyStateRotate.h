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
	const float DISTANCE_MAX;			//����鋗���ő�l
	const float DISCOVERY_DISTANCE;

	GSvector3 m_BasePosition;			//��]���钆�S�ʒu
	float m_Angle;						//�p�x
	float m_Distance;					//���S���痣��鋗��
	float m_RotateSpeed;				//��]���x

	float m_SECounter;					//SE����܂ł̎��Ԃ��J�E���g

};


#endif // !_ENEMY_STATE_ROTATE_H_
