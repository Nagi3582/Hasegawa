#ifndef UI_PLAY_MANAGER_H_
#define UI_PLAY_MANAGER_H_

class IWorld;
class Renderer;
struct SceneInfo;

class ItemManager;

class UIPlayManager
{
public:
	UIPlayManager(SceneInfo& info ,ItemManager& ItemMana);

	void Initialize(IWorld& world, Renderer& renderer);
	void Update(float deltaTime);
	void Draw()const;

private:
	void Cursor_Draw()const;

private:
	int m_Cursor;
	SceneInfo& m_Info;
	bool m_StickReset;

	ItemManager& m_ItemMana;
};


#endif // !PLAY_MANAGER_H_
