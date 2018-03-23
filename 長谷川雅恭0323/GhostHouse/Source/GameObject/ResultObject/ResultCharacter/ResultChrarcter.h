#ifndef RESULT_CHARACTER_H_
#define RESULT_CHARACTER_H_

#include"../../../Actor/Actor.h"
#include"../../../Actor/CollideActor.h"

class ResultCharacter :public CollideActor
{
public:
	ResultCharacter(IWorld& world,  GSvector3 position,Renderer&render);

	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(bool is_shadow,Renderer& m_renderer)const override;
private:
	Renderer* p_Renderer;
	GSmatrix4	m_Rotate{ GS_MATRIX4_IDENTITY };
};

#endif // !RESULT_CHARACTER_H_