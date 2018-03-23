#ifndef _TAKE_ITEM_MANAGER_H_
#define _TAKE_ITEM_MANAGER_H_
#include "../../UI/UITexture.h"
#include <list>

#include "TakeItemPtr.h"

class TakeItemManager :public UITexture
{
public:
	TakeItemManager(IWorld& world);

	void on_update(float deltaTime)override;
	void on_draw()const override;

	void AddTakeItem(TextureName texture);

private:
	using UIList = std::forward_list<TakeItemPtr>;
	UIList m_ItemUIList;

};



#endif // !_TAKE_ITEM_MANAGER_H_
