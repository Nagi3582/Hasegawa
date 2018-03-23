#ifndef _EXCLAMATION_MARK_3D_H_
#define _EXCLAMATION_MARK_3D_H_
#include "../../Actor/Actor.h"

class CollideActor;

class ExclamationMark3D :public Actor
{
public:
	ExclamationMark3D(IWorld& world, CollideActor& enemy);

	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;


private:
	CollideActor* p_Enemy;

};


#endif // !_EXCLAMATION_MARK_3D_H_
