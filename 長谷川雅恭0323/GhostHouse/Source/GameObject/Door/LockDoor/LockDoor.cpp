#include "LockDoor.h"
#include "../../../Collide/BoundingSphere.h"
#include "../../../Scene/SceneInfo/SceneInfo.h"
#include"../../../Scene/SceneType/SceneType.h"
#include"../../Character/Player/Player.h"
#include"../../Character/Player/PlayerManager.h"
#include"../../Item/ItemManager/ItemManager.h"
#include "../../Character/OperationPlayer/OperationPlayer.h"
#include "../../../UIObject/Operation/OperationManager.h"
#include "../../../Utility/Asset/SoundName.h"

LockDoor::LockDoor(IWorld & world, const GSvector3 & position, GSuint meshName, SceneInfo & info, SceneType type)
	:DoorBase(world
		, "Door"
		, position
		, new BoundingSphere(GSvector3(0.0f, 0.0f, 2.5f), 5.0f)
		, meshName
		, info
		, type)
{
}

LockDoor::LockDoor(IWorld & world
	, const GSvector3 & position
	, GSuint meshName
	, SceneInfo & info
	, SceneType type
	, OperationManager& operationManager)
	:DoorBase(world
		, "Door"
		, position
		, new BoundingSphere(GSvector3(0.0f, 0.0f, 2.5f), 5.0f)
		, meshName
		, info
		, type
		, operationManager)
{
}

void LockDoor::OnCollide(CollideActor & other)
{
	if (is_open == false)
	{
		if (other.GetName() == "Player")
		{
			Player*player = static_cast<Player*>(&other);
			un_lock(*player);
			m_Info.m_Door++;

			//チュートリアルの場合は次のチュートリアルに進む
			if (p_OperationManager != nullptr)
			{
				p_OperationManager->LockDoor();
			}
		}
	}
}

void LockDoor::un_lock(Player & player)
{
	if (player.get_manager().get_item().get_is_lock())
	{
		is_open = true;
		gsPlaySE((GSuint)SoundName::OpenDoorSE);
	}
}

void LockDoor::un_lock(OperationPlayer & player)
{
	if (player.get_manager().get_item().get_is_lock())
	{
		is_open = true;
		gsPlaySE((GSuint)SoundName::OpenDoorSE);
	}
}
