#include "UIManager.h"
#include"UIGroup.h"

UIManager::UIManager()
{
	intialize();
}

void UIManager::intialize()
{
	m_UIs[UIGroup::main] = new_UI<UITexture>();
	m_root.clear_children();
	m_root.add_child(m_UIs[UIGroup::main]);
}

void UIManager::update(float deltaTime)
{
	m_root.main_update(deltaTime);
	m_root.remove_children();
}

void UIManager::draw() const
{
	m_root.main_draw();
}

void UIManager::add_ui(UIGroup group, const UIPtr & ui)
{
	m_UIs[group]->add_child(ui);
}

UIPtr UIManager::find_UI(const std::string & name)
{
	return m_root.find_children(name);
}
