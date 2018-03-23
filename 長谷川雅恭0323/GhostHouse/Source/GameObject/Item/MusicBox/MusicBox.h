#ifndef MUSICBOX_H_
#define MUSICBOX_H_
#include"../ItemBase/ItemBase.h"
#include"../../../Actor/CollideActor.h"

struct SceneInfo;

class MusicBox : public CollideActor
{
public:

	MusicBox(IWorld& world, GSvector3 position, SceneInfo& info);

	virtual void OnUpdate(float deltaTime)override;

	virtual void OnCollide(CollideActor& other)override;

	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;


private:
	SceneInfo& m_Info;

};




#endif // !MUSICBOX_H_
