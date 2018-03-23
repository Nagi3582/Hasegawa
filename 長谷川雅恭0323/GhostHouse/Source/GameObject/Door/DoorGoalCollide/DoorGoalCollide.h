#ifndef _DOOR_GOAL_COLLIDE_H_
#define _DOOR_GOAL_COLLIDE_H_
#include "../../../Actor/CollideActor.h"

enum class SceneType;
struct SceneInfo;

class DoorGoalCollide :public CollideActor
{
public:
	DoorGoalCollide(IWorld& world, GSvector3 position, SceneInfo& info, SceneType& next);


	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;
	virtual void OnCollide(CollideActor& other)override;


private:
	SceneInfo& m_Info;
	SceneType m_NextScene;

};


#endif // !_DOOR_GOAL_COLLIDE_H_
