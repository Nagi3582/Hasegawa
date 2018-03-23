#ifndef COLLIDE_LIGHT_H_
#define COLLIDE_LIGHT_H_

#include"../../../Actor/CollideActor.h"
#include"../PlayerLight.h"

enum class LightColor;

class CollideLight :public CollideActor
{
public:
	CollideLight() = default;
	CollideLight(IWorld& world, PlayerLight&light, LightColor color, ItemManager& item, std::string name = "Light");
	CollideLight(IWorld& world, GSmatrix4 rotate, LightColor color, ItemManager& item, std::string name = "Light");

	~CollideLight();

	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(bool is_shadow, Renderer& m_renderer)const override;

	virtual void OnCollide(CollideActor& other)override;

	LightColor get_color()const;
	void set_color(LightColor color);
private:
	PlayerLight *p_test_light;
	ItemManager* p_ItemManager;
	bool m_With;
};

#endif // !COLLIDE_LIGHT_H_