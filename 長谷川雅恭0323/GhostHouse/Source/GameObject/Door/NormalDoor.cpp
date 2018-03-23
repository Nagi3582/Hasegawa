#include "NormalDoor.h"
#include "../../Collide/BoundingSphere.h"
#include "../../Scene/SceneInfo/SceneInfo.h"
#include"../../Scene/SceneType/SceneType.h"
#include "../../Utility/Asset/SoundName.h"
#include "../../Utility/Asset/TextureName.h"
#include "../../UIObject/GimmickAssist/GimmickAssist.h"
#include "../../UIObject/Operation/OperationManager.h"

NormalDoor::NormalDoor(IWorld & world, const GSvector3 & position, GSuint meshName, SceneInfo & info, SceneType type)
	: DoorBase(world
		, "Door"
		, position
		, new BoundingSphere(GSvector3(0.0f, 0.0f, 2.5f), 5.0f)
		, meshName
		, info
		, type)
{
}

NormalDoor::NormalDoor(IWorld & world
	, const GSvector3& position
	, const GSuint meshName
	, SceneInfo & info
	, SceneType type
	, OperationManager& operationManager)
	: DoorBase(world
		, "Door"
		, position
		, new BoundingSphere(GSvector3(0.0f, 0.0f, 2.5f), 5.0f)
		, meshName
		, info
		, type
		, operationManager)
{
}

void NormalDoor::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player" && is_open == false)
	{
		is_open = true;
		gsPlaySE((GSuint)SoundName::OpenDoorSE);
		m_Info.m_Door++;
		//チュートリアルの場合は次のチュートリアルに進む
		if (p_OperationManager != nullptr)
		{
			p_OperationManager->NormalDoor();
		}

	}
}
