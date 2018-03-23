#include "Field.h"
#include "../../Collide/Ray.h"
#include "../../Collide/Line.h"
#include "../../Collide/BoundingSphere.h"
#include"../../Utility/Renderer/Renderer.h"
#include"../../Utility/Renderer/ShaderName/ShaderName.h"

Field::Field(FieldName field)
	: m_Enable{ true }
	, m_CurrentField{ (GSuint)field }
	, m_NextField{ (GSuint)FieldName::None }
	, m_Floor{ (GSuint)field + 1 }
	, m_CollideField{ (GSuint)field + 2 }
	, m_CollideWall{ (GSuint)field + 3 }
	, m_Texture{ (GSuint)field + 4 }
	, m_Shader{ ShaderName::Standerd }
{
}

Field::Field(FieldName field, ShaderName shader)
	: m_Enable{ true }
	, m_CurrentField{ (GSuint)field }
	, m_NextField{ (GSuint)FieldName::None }
	, m_Floor{ (GSuint)field + 1 }
	, m_CollideField{ (GSuint)field + 2 }
	, m_CollideWall{ (GSuint)field + 3 }
	, m_Texture{ (GSuint)field + 4 }
	, m_Shader{ shader }
{
}

bool Field::IsCollide(const Ray & ray, GSvector3 * intersect, GSplane * plane, bool hitObj)
{
	//壁との当たり判定
	if (gsOctreeCollisionRay(
		gsGetOctree(m_CollideWall),
		&ray.m_Start,
		&ray.m_Direction,
		intersect,
		plane
		))
		return true;

	//オブジェクトと当たり判定をしない場合ここで終了
	if (hitObj == false)return false;

	//オブジェクトとの当たり判定
	return gsOctreeCollisionRay(
		gsGetOctree(m_CollideField),
		&ray.m_Start,
		&ray.m_Direction,
		intersect,
		plane
		) == GS_TRUE;
}

bool Field::IsCollide(const Line & line, GSvector3 * intersect, GSplane * plane, bool hitObj)
{
	//壁との当たり判定
	if (gsOctreeCollisionLine(
		gsGetOctree(m_CollideWall),
		&line.m_Start,
		&line.m_End,
		intersect,
		plane
		))
		return true;

	//オブジェクトと当たり判定をしない場合ここで終了
	if (hitObj == false)return false;

	//オブジェクトとの当たり判定
	return gsOctreeCollisionLine(
		gsGetOctree(m_CollideField),
		&line.m_Start,
		&line.m_End,
		intersect,
		plane
		) == GS_TRUE;
}

bool Field::IsCollide(const BoundingSphere& sphere, GSvector3* intersect, bool hitObj)
{
	//壁との当たり判定
	if (gsOctreeCollisionSphere(
		gsGetOctree(m_CollideWall),
		&sphere.m_Center,
		sphere.m_Radius,
		intersect
		))
		return true;

	//オブジェクトと当たり判定をしない場合ここで終了
	if (hitObj == false)return false;

	//オブジェクトとの当たり判定
	return gsOctreeCollisionSphere(
		gsGetOctree(m_CollideField),
		&sphere.m_Center,
		sphere.m_Radius,
		intersect
		) == GS_TRUE;
}
void Field::Draw(bool is_shadow, Renderer&renderer) const
{
	if (m_Enable == false)
		return;

	DrawField(is_shadow,renderer);
}

void Field::OnEnable()
{
	m_Enable = false;
}

void Field::NotEnable()
{
	m_Enable = false;
}

void Field::SetNextField(FieldName field)
{
	m_CurrentField = (int)field;
	m_CollideField = (int)field + 2;
}

void Field::DrawField(bool is_shadow, Renderer&renderer) const
{
	{
		GSmatrix4 local_world;
		local_world.identity();
		renderer.set_world(local_world);
		renderer.draw_manager(is_shadow
			, m_Floor
			, (GSuint)ShaderName::Floor
			, (GSuint)ShaderName::Depth);
	}
	{
		GSmatrix4 local_world;
		local_world.identity();
		renderer.set_world(local_world);
		renderer.draw_manager(is_shadow,
			m_CurrentField
			, (GSuint)ShaderName::Textured
			, (GSuint)ShaderName::Depth);
	}
	{
		GSmatrix4 local_world;
		local_world.identity();
		renderer.set_world(local_world);
		renderer.draw_manager(is_shadow
			, m_Texture
			, (GSuint)ShaderName::Textured
			, (GSuint)ShaderName::Depth);
	}
}

void Field::DrawCollider(Renderer & m_renderer) const
{
}
