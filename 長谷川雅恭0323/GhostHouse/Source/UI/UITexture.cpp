#include "UITexture.h"
#include <algorithm>

UITexture::UITexture(IWorld & world
	, std::string name
	, GSvector2 position
	, int width
	, int height)
	:p_world{ &world }
	, m_name{ name }
	, m_position{ position }
	, m_is_delete{ false }
	, m_is_draw{ true }
	, m_num{ width,height }
{
}

void UITexture::main_update(float deltaTime)
{
	on_update(deltaTime);
	each_children([&](UITexture&child)
	{child.main_update(deltaTime); });
}

void UITexture::main_draw() const
{
	if (m_is_draw == false)return;

	on_draw();
	each_children([&](const UITexture& child)
	{child.main_draw(); });
}

GSuint UITexture::get_param() const
{
	return m_UI_param;
}

std::string UITexture::get_name() const
{
	return m_name;
}

bool UITexture::is_delete() const
{
	return m_is_delete;
}

void UITexture::delete_UI()
{
	m_is_delete = true;
}

void UITexture::hide_On()
{
	m_is_draw = false;
}

void UITexture::hide_Off()
{
	m_is_draw = true;
}

bool UITexture::is_Hide() const
{
	return m_is_draw;
}

void UITexture::each_children(std::function<void(UITexture&)> fn)
{
	for (const auto&ui : m_children)
	{
		fn(*ui);
	}
	//std::for_each(m_children.begin(), m_children.end(),
	//	[&](const UIPtr& child)
	//{
	//	fn(*child);
	//});
}

void UITexture::each_children(std::function<void(const UITexture&)> fn) const
{
	for (const auto&ui : m_children)
	{
		fn(*ui);
	}

}

UIPtr UITexture::find_children(const std::string & name)
{
	return find_children(
		[&](const UITexture&ui)
	{return ui.get_name() == name; });
}

UIPtr UITexture::find_children(std::function<bool(const UITexture&)> fn)
{
	const std::forward_list<UIPtr>::iterator& i =
		std::find_if(m_children.begin(), m_children.end(),
			[&](const UIPtr& child)
	{ return fn(*child); });

	if (i != m_children.end())
	{
		return *i;
	}
	for (const UIPtr& child : m_children)
	{
		const UIPtr actor = child->find_children(fn);
		if (actor != nullptr)
		{
			return actor;
		}
	}
	return nullptr;
}

void UITexture::add_child(const UIPtr & child)
{
	m_children.push_front(child);
}

void UITexture::remove_children(std::function<bool(UITexture&other)> fn)
{
	m_children.remove_if(
		[&](const UIPtr& child)
	{return fn(*child); });
}

void UITexture::remove_children()
{
	remove_children([](UITexture& child)
	{ return child.is_delete(); });
	each_children(
		[](UITexture& child)
	{child.remove_children(); });
}

void UITexture::clear_children()
{
	m_children.clear();
}
