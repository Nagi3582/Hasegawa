#ifndef _SMOKE_H_
#define _SMOKE_H_
#include "../../../Actor/Actor.h"

struct SceneInfo;
class Camera;

class Smoke :public Actor
{
public:
	Smoke(IWorld& world, const GSvector3& position, Camera& camera, SceneInfo& info);

	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;


private:
	float m_Timer;
	SceneInfo& m_Info;
	Camera* p_Camera;

};


#endif // !_SMOKE_H_
