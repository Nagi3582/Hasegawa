#ifndef _TAKE_ITEM_H_
#define _TAKE_ITEM_H_
#include "../../UI/UITexture.h"

class TakeItem :public UITexture
{
public:
	TakeItem(IWorld& world, TextureName texture);

	void on_update(float deltaTime)override;
	void on_draw()const override;

	void AddTakeItem();


private:
	void Spring(const GSvector2& restPosition, float stiffness, float friction, float mass);


private:
	GSvector2 m_Velocity;
	float m_Timer;
	int m_TakeItemID;
	TextureName m_Name;


};


#endif // !_TAKE_ITEM_H_
