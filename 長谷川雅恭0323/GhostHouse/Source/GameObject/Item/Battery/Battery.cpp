#include "Battery.h"
#include "../../../Utility/Renderer/Renderer.h"
#include"../../../Collide/BoundingSphere.h"
#include "../../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../ItemManager/ItemManager.h"
#include "../../../Utility/Asset/SoundName.h"
#include "../../../Utility/Asset/TextureName.h"
#include "../../../UIObject/Operation/OperationManager.h"

Battery::Battery(IWorld & world, GSvector3 position, ItemManager& item, OperationManager* operationManager)
	:CollideActor{ world, "Item", position, new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f), 2.0f) }
	, p_ItemManager{ &item }
	, p_OperationManager{ operationManager }
{
	m_Position.y += 0.6f;
}

void Battery::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player")
	{
		p_ItemManager->TakeBattery();
		p_ItemManager->TakeItem(TextureName::ItemTakeBattery);
		Dead();
		gsPlaySE((GSuint)SoundName::GetItemSE);
		if (p_OperationManager != nullptr)
		{
			p_OperationManager->TakeBattery();
		}
	}
}

void Battery::OnDraw(bool is_shadow, Renderer & renderer) const
{
	renderer.set_world(GetPose());
	renderer.draw_manager(is_shadow
		, (GSuint)MeshName::Battery
		, (GSuint)ShaderName::Standerd
		, (GSuint)ShaderName::Depth);
}
