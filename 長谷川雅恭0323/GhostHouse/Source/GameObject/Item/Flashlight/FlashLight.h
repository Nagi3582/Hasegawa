#ifndef _FLASH_LIGHT_H_
#define _FLASH_LIGHT_H_
#include "../ItemBase/ItemBase.h"
#include"../../../Actor/CollideActor.h"

class ItemManager;
enum class LightColor;
enum class TextureName;
class LightParameter;


class Flashlight :public CollideActor
{
public:
	Flashlight(IWorld& world, GSvector3 position, LightColor color, ItemManager& item, int batterySize = 100);

	virtual void OnUpdate(float deltaTime)override;

	virtual void OnCollide(CollideActor& other)override;

	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;



private:
	void SetMeshName();

private:
	ItemManager* p_Manager;
	int m_Counter;
	int m_Battery;

	LightColor m_Color;
	int m_MeshID;
	TextureName m_Texture;
	LightParameter* p_Light;



};


#endif // !_FLASH_LIGHT_H_
