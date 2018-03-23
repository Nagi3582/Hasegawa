#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

#include"UITexture.h"
#include"UIPtr.h"
#include<unordered_map>

enum class UIGroup;
class Renderer;

class UIManager
{
public:
	UIManager();

	void intialize();
	void update(float deltaTime);
	void draw()const;
	void add_ui(UIGroup grup, const UIPtr&ui);
	UIPtr find_UI(const std::string&name);


	//ÉRÉsÅ[ã÷é~
	UIManager(const UIManager& other) = delete;
	UIManager& operator=(const UIManager& other) = delete;

private:
	UITexture m_root;
	std::unordered_map<UIGroup, UIPtr>m_UIs;
};

#endif // !UI_MANAGER_H_