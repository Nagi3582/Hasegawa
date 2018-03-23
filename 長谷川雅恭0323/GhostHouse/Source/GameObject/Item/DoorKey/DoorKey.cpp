#include "DoorKey.h"
#include "../../../Utility/Renderer/Renderer.h"
#include"../../../Collide/BoundingSphere.h"
#include "../../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../ItemManager/ItemManager.h"
#include "../../../Utility/Asset/SoundName.h"
#include "../../../Scene/SceneInfo/SceneInfo.h"
#include"../../../World/World.h"
#include"../../../UI/UIGroup.h"
#include"../../../UIObject/GamePlay/UI_Key.h"
#include "../../../Utility/Asset/TextureName.h"


DoorKey::DoorKey(IWorld & world, GSvector3 position, ItemManager& manager, SceneInfo& info)
	:CollideActor(world, "Item", position, new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f), 2.0f))
	, p_Manager{ &manager }
	, m_Info{ info }
{
	m_Rotate.rotateX(90);
	info.m_GetKey = false;
	manager.SetUnLock(false);
	world.AddUI(UIGroup::main, std::make_shared<UI_Key>(world, GSvector2{ 100.0f,500.0f }, m_Info));

}

void DoorKey::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player")
	{
		p_Manager->DoorUnLock();
		p_Manager->TakeItem(TextureName::ItemTakeKey);
		Dead();
		gsPlaySE((GSuint)SoundName::GetItemSE);
		m_Info.m_GetKey = true;
	}
}

void DoorKey::OnDraw(bool is_shadow, Renderer & renderer) const
{
	renderer.set_world(GetPose());
	renderer.draw_manager(is_shadow
		, (GSuint)MeshName::DoorKey
		, (GSuint)ShaderName::Standerd
		, (GSuint)ShaderName::Depth);
}
