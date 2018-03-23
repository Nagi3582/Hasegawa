#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "../../UI/UITexture.h"

struct SceneInfo;

class Pause :public UITexture
{
public:
	Pause(IWorld&world, SceneInfo& info);


	virtual void on_update(float deltaTime);
	virtual void on_draw()const;


private:
	SceneInfo& m_Info;

};


#endif // !_PAUSE_H_
