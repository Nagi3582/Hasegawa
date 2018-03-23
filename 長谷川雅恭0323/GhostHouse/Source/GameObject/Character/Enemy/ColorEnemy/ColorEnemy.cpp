#include "ColorEnemy.h"
#include "../../../../Collide/BoundingSphere.h"
#include "../../../../Actor/CollideActor.h"
#include "../../../../Utility/Asset/MeshName.h"
#include"../../../../Utility/Renderer/Renderer.h"
#include"../../../../Utility/Renderer/ShaderName/ShaderName.h"
#include"../../../Light/LightColor.h"

ColorEnemy::ColorEnemy(IWorld & world
	, CollideActor & player
	, GSuint mesh
	, int color_num
	, LightColor my_color1
	, LightColor my_color2)
	: ModelBase(world, "Enemy", GSvector3(0.0f, 0.0f, 20.0f), new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f), 2.0f))
	, p_Player(&player)
	, m_State(EnemyStateName::Idle)
	, m_Hp(100)
	, m_mesh{ mesh }
{
	if (color_num > 2)color_num = 2;
	for (int i = 0; i < color_num; i++)
		m_is_hit_color.push_back(false);
	for (int i = 0; i < color_num; i++)
		m_color_timer.push_back(60.0f);
	m_my_color.push_back(my_color1);
	m_my_color.push_back(my_color2);
	m_Position.y += 3.0f;
}

void ColorEnemy::OnUpdate(float deltaTime)
{
	if (m_State == EnemyStateName::Idle)
	{
		m_Velocity = p_Player->GetPosition() - m_Position;
		m_Velocity.normalize();

		const GSvector3 l_Front = m_Velocity;
		const GSvector3 l_Up = m_Rotate.getAxisY().getNormalized();
		const GSvector3 l_Left = l_Up.cross(l_Front);

		m_Rotate.setAxisX(l_Left);
		m_Rotate.setAxisY(l_Up);
		m_Rotate.setAxisZ(l_Front);

		m_Position += m_Velocity * 0.1f * deltaTime;
	}

	if (is_hit_color())
		m_State = EnemyStateName::Stop;

	move_re_start();

	if (m_Hp <= 0)
	{
		Dead();
	}

	int num = 0;
	for (const auto timers : m_color_timer)
	{
		m_color_timer[num] -= deltaTime;
		num++;
	}

}

void ColorEnemy::SubDraw(bool is_shadow, Renderer & m_renderer) const
{
	m_renderer.set_world(GetPose());
	m_renderer.draw_manager(is_shadow
		, m_mesh
		, (GSuint)ShaderName::Standerd
		, (GSuint)ShaderName::Depth);
}

void ColorEnemy::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Light")
	{
		CollideLight* light = static_cast<CollideLight*>(&other);
		checkLight(*light);
	}
}

void ColorEnemy::checkLight(CollideLight light)
{
	int num = 0;
	for (const auto colors : m_my_color)
	{
		if (light.get_color() == colors || colors == LightColor::White)
		{
			m_color_timer[num] = 60;
			m_is_hit_color[num] = true;
		}
		num++;
	}
}

bool ColorEnemy::is_hit_color() const
{
	for (const auto bools : m_is_hit_color)
	{
		if (!bools)
			return false;
	}
	return true;
}

void ColorEnemy::move_re_start()
{
	int num = 0;
	for (const auto timers : m_color_timer)
	{
		if (timers <= 0)
		{
			m_State = EnemyStateName::Idle;
			m_color_timer[num] = 60;
			m_is_hit_color[num] = false;
		}
		num++;
	}
}
