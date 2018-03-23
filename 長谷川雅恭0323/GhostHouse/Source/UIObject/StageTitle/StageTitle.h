#ifndef STAGE_TITLE_H_
#define STAGE_TITLE_H_

#include"../../UI/UITexture.h"

class StageTitle :public UITexture
{
private:
public:
	StageTitle(IWorld&world,GSuint TexID);
private:
	void on_update(float deltaTime)override;
	void on_draw()const override;
private:
	GSuint m_TexID;
	float m_timer;
	GSvector2 target_pos,base_pos;
};

#endif // !STAGE_TITLE_H_
