#ifndef BATTERY_H_
#define BATTERY_H_
#include"../ItemBase/ItemBase.h"
#include"../../../Actor/CollideActor.h"

class ItemManager;
class OperationManager;

class Battery : public CollideActor
{
public:
	Battery(IWorld& world, GSvector3 position, ItemManager& item, OperationManager* operationManager = nullptr);

	virtual void OnCollide(CollideActor& other)override;

	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;


private:
	ItemManager* p_ItemManager;
	OperationManager* p_OperationManager;

};





#endif // !BATTERY_H_
