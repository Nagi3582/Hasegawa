#ifndef _DUMMY_KEY_H_
#define _DUMMY_KEY_H_
#include "../../../Actor/CollideActor.h"

class Camera;
struct SceneInfo;

class DummyKey :public CollideActor
{
public:
	DummyKey(IWorld& world, GSvector3 position, Camera& camera, SceneInfo& info);

	virtual void OnUpdate(float deltaTime)override;
	virtual void OnCollide(CollideActor& other)override;
	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;


private:
	Camera* p_Camera;
	SceneInfo& m_Info;


};



#endif // !_DUMMY_KEY_H_
