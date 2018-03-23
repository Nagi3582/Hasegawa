#ifndef _SHINING_LIGHT_H_
#define _SHINING_LIGHT_H_
#include "../../../Actor/CollideActor.h"
#include"../../Light/LightParam/LightParams.h"

class ItemManager;
enum class LightColor;
class LightParameter;
class Renderer;
class CollideLight;
class OperationManager;
enum class TextureName;

class ShiningLight :public CollideActor
{
public:
	ShiningLight(IWorld& world, GSvector3 position, int batterySize, LightColor color,
		ItemManager& item, CollideActor& player, Renderer& renderer, bool is_UseBattery = true);

	ShiningLight(IWorld& world, GSvector3 position, int batterySize, LightColor color,
		ItemManager& item, CollideActor& player, Renderer& renderer, OperationManager& operationManager, bool is_UseBattery = true);


	~ShiningLight();

	virtual void OnUpdate(float deltaTime)override;

	virtual void OnCollide(CollideActor& other)override;

	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;


private:
	void ShiningLight::SetMeshName();

	void set_light_param();

private:
	ItemManager* p_ItemManager;
	LightParameter* p_Light;
	int m_MeshID;
	LightColor m_Color;
	Renderer* p_Renderer;
	int m_LightID;
	GScolor m_LightColor;
	CollideLight* p_CollideLight;
	LightParams* p_param;
	TextureName m_Texture;
	bool m_TimeUp;
	bool m_IsUseBattery;
	OperationManager* p_OperationManager;
};


#endif // !_SHINING_LIGHT_H_