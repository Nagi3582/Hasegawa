#include "TitleCamera.h"
#include "../../Utility/Renderer/Renderer.h"
#include "../../Base/Screen.h"

TitleCamera::TitleCamera()
	: CollideActor{}
{
}

void TitleCamera::OnUpdate(float deltaTime)
{
	m_Rotate.identity();

	m_Position = GSvector3(0.0f, 0.0f, 0.0f);

	const GSvector3 l_Back = GSvector3(0.0f, 0.0f, -20.0f);
	const GSvector3 l_Up = GSvector3(0.0f, 25.0f, 0.0f);

	m_Position += l_Back + l_Up;


	m_Rotate.rotateX(15.0f);

}

void TitleCamera::OnDraw(bool is_shadow,Renderer & renderer) const
{
	if (is_shadow)
		return;
	const float angle = 60.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, WIDTH / HEIGHT, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	GSmatrix4 l_Pose = GSmatrix4(GetRotate().setPosition(m_Position));
	glLoadMatrixf(l_Pose.convertViewRH());

	GSmatrix4 local_view;
	GSvector3 flont_vec = GetRotate().getAxisZ() + m_Position;
	local_view.setLookAtRH(m_Position, flont_vec, GSvector3{ 0.0f,1.0f,0.0f });
	renderer.set_view(local_view);
	renderer.set_camera_position(m_Position);
	GSmatrix4 projection;
	projection.setPerspectiveRH(angle, WIDTH / HEIGHT, 0.5f, 500.0f);
	renderer.set_projection(projection);
}
