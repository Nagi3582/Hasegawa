#ifndef RESULT_CAMERA_H_
#define RESULT_CAMERA_H_

#include "../../Actor/CollideActor.h"

class ResultCamera :public CollideActor
{
public:
	ResultCamera();

	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(bool is_shadow,Renderer& m_renderer)const override;
};

#endif // !RESULT_CAMERA_H_