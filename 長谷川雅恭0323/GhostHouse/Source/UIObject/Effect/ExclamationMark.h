#ifndef _EXCLAMATION_MARK_H_
#define _EXCLAMATION_MARK_H_
#include "../../UI/UITexture.h"

class CollideActor;

class ExclamationMark :public UITexture
{
public:
	ExclamationMark(IWorld&world, CollideActor& player, CollideActor& enemy);

	virtual void on_update(float deltaTime)override;
	virtual void on_draw()const override;


private:
	CollideActor* p_Player;
	CollideActor* p_Enemy;
	GSvector2 m_RedPosition;

};


#endif // !_EXCLAMATION_MARK_H_
