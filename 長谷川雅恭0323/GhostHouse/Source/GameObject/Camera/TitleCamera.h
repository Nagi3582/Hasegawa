#ifndef _TITLE_CAMERA_H_
#define _TITLE_CAMERA_H_
#include "../../Actor/CollideActor.h"

class TitleCamera :public CollideActor
{
public:
	TitleCamera();


	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(bool is_shadow,Renderer& m_renderer)const override;

};



#endif // !_TITLE_CAMERA_H_
