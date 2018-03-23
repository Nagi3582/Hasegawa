//ìGÇ…åpè≥Ç∑ÇÈÉNÉâÉX
#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_
#include "../ModelBase.h"
#include "EnemyState/EnemyStateManager.h"

enum class LightColor;

class EnemyBase :public ModelBase
{
public:
	EnemyBase(IWorld & world, MeshName mesh, LightColor color, GSvector3 position, CollideActor& player, Renderer& renderer);

	virtual void OnUpdate(float deltaTime)override;
	virtual void SubDraw(bool is_shadow,Renderer& m_renderer)const override;
	virtual void OnCollide(CollideActor& other)override;

protected:
	virtual void SetState(CollideActor& player) {};

protected:
	EnemyStateManager m_Manager;
	LightColor m_Color;

private:
	MeshName m_Mesh;
	Renderer* p_Renderer;


};


#endif // !_ENEMY_BASE_H_
