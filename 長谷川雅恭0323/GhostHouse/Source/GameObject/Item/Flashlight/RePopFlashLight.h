#ifndef RE_POP_FLASH_LIGHT_H_
#define RE_POP_FLASH_LIGHT_H_

#include "../ItemBase/ItemBase.h"
#include"../../../Actor/CollideActor.h"

class ItemManager;
enum class LightColor;
enum class TextureName;

class RePopFlashLight :public CollideActor
{
public:
	RePopFlashLight(IWorld& world, GSvector3 position, LightColor color, ItemManager& item, int popTime = 60 * 30);

	virtual void OnUpdate(float deltaTime)override;

	virtual void OnCollide(CollideActor& other)override;

	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;

private:
	void SetMeshName();

private:
	ItemManager * p_Manager;
	int m_Counter;
	int m_Battery;
	bool m_is_get;
	float m_re_pop_timer;
	LightColor m_Color;
	int m_MeshID;
	TextureName m_Texture;
	int m_PopTime;

};


#endif // !RE_POP_FLASH_LIGHT_H_
