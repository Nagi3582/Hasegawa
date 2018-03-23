#ifndef _MINI_MAP_H_
#define _MINI_MAP_H_
#include "../../UI/UITexture.h"

class CollideActor;
struct SceneInfo;
enum class TextureName;

class MiniMap :public UITexture
{
public:
	MiniMap(IWorld& world, CollideActor& player, SceneInfo& info, int stage);

	void on_update(float deltaTime)override;
	void on_draw()const override;


private:
	void SetTexture(int stage);

private:
	CollideActor* p_Player;
	SceneInfo& m_Info;
	GSvector2 m_StageMapPosition;
	TextureName m_Texture;
	float m_PlayerAlpha;
	float m_PlayerAlphaPlus;

};


#endif // !_MINI_MAP_H_
