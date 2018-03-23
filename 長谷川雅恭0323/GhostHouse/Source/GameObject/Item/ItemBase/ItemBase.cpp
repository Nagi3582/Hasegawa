#include "ItemBase.h"
#include "../../../Collide/BoundingSphere.h"
//#include "../../../../Utility/Renderer/ShaderName/ShaderName.h"
#include"../../../Utility/Renderer/Renderer.h"

ItemBase::ItemBase(IWorld& world, std::string name, GSvector3 position,Shape* shape)
	: CollideActor{ world, name, position, new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f),2.0f) }
	, m_Mesh{ MeshName::None }
{
}

void ItemBase::SetUp(MeshName name)
{
	m_Mesh = name;
}
