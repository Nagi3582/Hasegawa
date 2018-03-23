#ifndef _MODEL_BASE_H_
#define _MODEL_BASE_H_
#include "../../Actor/CollideActor.h"
#include "../../Utility/AnimationMesh/AnimationMesh.h"

enum class MeshName;

class ModelBase :public CollideActor
{
public:
	ModelBase(IWorld& world, std::string name, GSvector3 position, Shape* shape);
	~ModelBase() {}

	//描画
	virtual void OnDraw(bool is_shadow, Renderer& renderer)const override;

	//フィールドとの当たり判定
	bool HitField(bool isHit = true);


	//本体以外に何か描画したい時用
	virtual void SubDraw(bool is_shadow, Renderer& renderer)const {};



protected:
	void SetAnimation(Renderer& renderer, MeshName mesh, int motionID);


protected:
	GSvector3 m_Velocity;
	float m_Speed;
	MeshName m_Mesh;
	int m_AnmID;

};

#endif // !_MODEL_BASE_H_
