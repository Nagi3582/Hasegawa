#include "TakeItemManager.h"
#include "TakeItem.h"
#include <algorithm>

TakeItemManager::TakeItemManager(IWorld & world)
	: UITexture{ world,"TakeItemManager",GSvector2(0.0f,0.0f) }
{
}

void TakeItemManager::on_update(float deltaTime)
{
	std::for_each(m_ItemUIList.begin(), m_ItemUIList.end(), [&](TakeItemPtr& item)
	{item.get()->on_update(deltaTime); });

	m_ItemUIList.remove_if([&](TakeItemPtr& itemUI)
	{return is_delete(); });
}

void TakeItemManager::on_draw() const
{
	std::for_each(m_ItemUIList.begin(), m_ItemUIList.end(), [&](const TakeItemPtr& item)
	{item.get()->on_draw(); });
}

void TakeItemManager::AddTakeItem(TextureName texture)
{
	m_ItemUIList.push_front(std::make_shared<TakeItem>(*p_world, texture));
	std::for_each(m_ItemUIList.begin(), m_ItemUIList.end(), [&](TakeItemPtr& item)
	{item.get()->AddTakeItem(); });
}
