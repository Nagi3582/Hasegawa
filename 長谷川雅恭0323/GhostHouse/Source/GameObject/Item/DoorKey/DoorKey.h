#ifndef DOOR_KEY_H_
#define DOOR_KEY_H_
#include "../ItemBase/ItemBase.h"
#include"../../../Actor/CollideActor.h"
class ItemManager;
struct SceneInfo;

class DoorKey : public CollideActor
{
public:
	DoorKey(IWorld& world, GSvector3 position, ItemManager& manager, SceneInfo& info);

	virtual void OnCollide(CollideActor& other)override;

	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;

private:
	ItemManager* p_Manager;
	SceneInfo& m_Info;

};




#endif
