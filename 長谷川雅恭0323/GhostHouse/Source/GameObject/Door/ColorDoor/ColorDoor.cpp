#include "ColorDoor.h"
#include "../../../Collide/BoundingSphere.h"
#include "../../../Scene/SceneInfo/SceneInfo.h"
#include"../../../Scene/SceneType/SceneType.h"
#include"../../../Utility/Renderer/Renderer.h"
#include"../../../Utility/Asset/MeshName.h"
#include"../../../Utility/Renderer/ShaderName/ShaderName.h"
#include"../../Light/CollideLight/CollideLight.h"
#include"../../../UIObject/GimmickAssist/GimmickAssist.h"
#include "../../../UIObject/Operation/OperationManager.h"
#include "../../../Utility/Asset/SoundName.h"
#include "../../../UIObject/Operation/OperationManager.h"
#include<gslib.h>

const int COLOR_DOOR_LOCKTIME = 1;


ColorDoor::ColorDoor(IWorld & world
	, const GSvector3 & position
	, SceneInfo & info
	, SceneType type
	, GSuint mesh
	, int color_num
	, LightColor my_color1
	, LightColor my_color2)
	:DoorBase(world
		, "Door"
		, position
		, new BoundingSphere(GSvector3(0.0f, 0.0f, 2.5f), 5.0f)
		, mesh
		, info
		, type)
	, m_Type{ type }
{
	if (color_num > 2)color_num = 2;
	for (int i = 0; i < color_num; i++)
		m_is_hit_color.push_back(false);
	for (int i = 0; i < color_num; i++)
		m_color_timer.push_back(60.0f);
	m_my_color.push_back(my_color1);
	m_my_color.push_back(my_color2);

}

ColorDoor::ColorDoor(IWorld & world, const GSvector3 & position, SceneInfo & info, SceneType type,
	GSuint mesh, int color_num, OperationManager & operationManager, LightColor my_color1, LightColor my_color2)
	:DoorBase(world
		, "Door"
		, position
		, new BoundingSphere(GSvector3(0.0f, 0.0f, 2.5f), 5.0f)
		, mesh
		, info
		, type
		, operationManager)
	, m_Type{ type }
{
	if (color_num > 2)color_num = 2;
	for (int i = 0; i < color_num; i++)
		m_is_hit_color.push_back(false);
	for (int i = 0; i < color_num; i++)
		m_color_timer.push_back(0.0f);
	m_my_color.push_back(my_color1);
	m_my_color.push_back(my_color2);

}

void ColorDoor::DoorUpdate(float deltaTime)
{
	for (int i = 0; i < (int)m_my_color.size(); ++i)
	{
		if (m_color_timer[i] <= 0)
		{
			m_is_hit_color[i] = false;
		}
		m_color_timer[i] -= deltaTime;
	}

}

void ColorDoor::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player" && is_open == false)
	{
		if (p_OperationManager != nullptr)
		{
			p_OperationManager->ColorDoor();
		}
		set_UI();
	}

	if (other.GetName() == "Player"
		&& is_hit_color()
		&& is_open == false)
	{
		is_open = true;
		gsPlaySE((GSuint)SoundName::OpenDoorSE);
		if (m_my_color.size() >= 1)
			m_Info.m_MixColorDoor++;
		else
			m_Info.m_ColorDoor++;

		//チュートリアルの場合は次のチュートリアルに進む
		if (p_OperationManager != nullptr)
		{
			p_OperationManager->OpenColorDoor();
		}

	}
	if (other.GetName() == "Light" || other.GetName() == "ShiningLight")
	{
		checkLight(other, other.GetName());
	}


}
void ColorDoor::set_UI()
{

	if (is_hit_color())
	{
		//GimmickAssist::bind((GSuint)TextureName::GimmiccAssist_ButtomB);
		return;

	}
	if ((m_my_color[0] == LightColor::Red&&m_my_color[1] == LightColor::Blue)
		|| (m_my_color[0] == LightColor::Blue&&m_my_color[1] == LightColor::Red))
	{
		GimmickAssist::bind((GSuint)TextureName::GimmiccAssist_CulorPurple);
		return;
	}
	if ((m_my_color[0] == LightColor::Red&&m_my_color[1] == LightColor::Green)
		|| m_my_color[0] == LightColor::Green&&m_my_color[1] == LightColor::Red)
	{
		GimmickAssist::bind((GSuint)TextureName::GimmiccAssist_CulorYellow);
		return;
	}
	if ((m_my_color[0] == LightColor::Blue&&m_my_color[1] == LightColor::Green)
		|| m_my_color[0] == LightColor::Green&&m_my_color[1] == LightColor::Blue)
	{
		GimmickAssist::bind((GSuint)TextureName::GimmiccAssist_CulorLightblue);
		return;
	}
}
void ColorDoor::checkLight(CollideActor& light, std::string& otherName)
{
	int num = 0;
	for (const auto colors : m_my_color)
	{
		if (light.GetColor() == colors || colors == LightColor::White)
		{
			m_color_timer[num] = COLOR_DOOR_LOCKTIME;
			m_is_hit_color[num] = true;

			if (p_OperationManager != nullptr && light.GetColor() == LightColor::Red && otherName == "ShiningLight")
				p_OperationManager->PutLightColorDoor();
		}
		num++;
	}
}


bool ColorDoor::is_hit_color() const
{
	for (const auto bools : m_is_hit_color)
	{
		if (!bools)
			return false;
	}
	return true;
}

void ColorDoor::is_lock()
{
	int num = 0;
	for (const auto timers : m_color_timer)
	{
		if (timers <= 0)
		{
			m_color_timer[num] = COLOR_DOOR_LOCKTIME;
			m_is_hit_color[num] = true;
		}
		num++;
	}
}
